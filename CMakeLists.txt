cmake_minimum_required(VERSION 3.10)

# set the project name
project(HelloProj VERSION 1.0)

# specify the C++ standard
# use the CMAKE_CXX_STANDARD variable
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

################# Hardware info #################
# Detect the processor architecture
if(CMAKE_SYSTEM_PROCESSOR)
    set(HARDWARE_ARCH ${CMAKE_SYSTEM_PROCESSOR})
else()
    set(HARDWARE_ARCH "Unknown")
endif()

# Detect the number of CPU cores (This is platform-specific)
if(WIN32)
    set(CPU_CORES $ENV{NUMBER_OF_PROCESSORS})
elseif(UNIX)
    find_package(Threads)
    set(CPU_CORES ${CMAKE_THREAD_LIBS_INIT})
    execute_process(COMMAND nproc OUTPUT_VARIABLE CPU_CORES OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
    set(CPU_CORES "Unknown")
endif()

# Detect the amount of RAM (platform-specific)
if(WIN32)
    # Use PowerShell to get the total physical memory (in KB) on Windows
    execute_process(
        COMMAND powershell -Command "(Get-WmiObject Win32_ComputerSystem).TotalPhysicalMemory"
        OUTPUT_VARIABLE MEM_INFO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    # Convert from bytes to megabytes
    math(EXPR RAM_MB "${MEM_INFO} / 1024 / 1024")
elseif(UNIX)
    # Get total memory from /proc/meminfo (Linux/Unix)
    execute_process(
        COMMAND grep MemTotal /proc/meminfo
        OUTPUT_VARIABLE MEM_INFO
    )
    string(REGEX REPLACE "([^0-9]*)" "" MEM_INFO ${MEM_INFO})
    math(EXPR RAM_MB "${MEM_INFO} / 1024")
else()
    set(RAM_MB "Unknown")
endif()

# Detect the GPU (platform-specific)
if(WIN32)
    # Use PowerShell to get the GPU name(s) on Windows and join multiple lines with commas
    execute_process(
        COMMAND powershell -Command "(Get-WmiObject Win32_VideoController | Select-Object -ExpandProperty Name) -join ', '"
        OUTPUT_VARIABLE GPU_INFO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
elseif(UNIX)
    # Try to detect GPU using lspci for Linux
    execute_process(
        COMMAND lspci | grep VGA
        OUTPUT_VARIABLE GPU_INFO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if("${GPU_INFO}" STREQUAL "")
        # If lspci doesn't work, fallback to nvidia-smi for NVIDIA GPUs
        execute_process(
            COMMAND nvidia-smi --query-gpu=name --format=csv,noheader
            OUTPUT_VARIABLE GPU_INFO
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    endif()

    if("${GPU_INFO}" STREQUAL "")
        set(GPU_INFO "Unknown")
    endif()
else()
    set(GPU_INFO "Unknown")
endif()


# export configuration to source code
configure_file(cmake/HelloProjConfig.h.in HelloProjConfig.h)
configure_file(cmake/HelloProjHardwareInfo.h.in HelloProjHardwareInfo.h)

#add libraries
add_subdirectory(src/basic)

#add executable
option(HELLOWORLD_WITH_EXECUTABLES "Compile mains" ON)

if(HELLOWORLD_WITH_EXECUTABLES)
	message(STATUS "Configuring Hello World with executables")
	add_subdirectory(mains)
endif()

#add tests
option(HELLOWORD_WITH_TESTS "Compile tests" ON)

if(HELLOWORD_WITH_TESTS)
	enable_testing()
	message(STATUS "Configuring Hello World with tests")
	add_subdirectory(tests)
endif()