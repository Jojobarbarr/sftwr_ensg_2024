#include <HelloProjConfig.h>
#include <HelloProjHardwareInfo.h>
#include <basic/message.h>
#include <iostream>

void hello_world()
{
    std::cout << "Hello World!\n";
}

void print_version()
{
    std::cout << "Project version is " << HelloProj_VERSION_MAJOR << "."
              << HelloProj_VERSION_MINOR << "\n";
}

void print_hardware_info()
{
    std::cout << "Hardware Info: \n";
    std::cout << "  Architecture: " << HelloProj_HARDWARE_ARCHITECTURE << "\n";
    std::cout << "  CPU Cores: " << HelloProj_CPU_CORES << "\n";
    std::cout << "  RAM: " << HelloProj_RAM_MB << " MB\n";
    std::cout << "  GPU: " << HelloProj_GPU_INFO << "\n";
}