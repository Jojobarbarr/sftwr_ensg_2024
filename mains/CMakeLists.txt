# add the executable target named HelloWorld
add_executable(HelloWorld hello.cpp)
target_link_libraries(HelloWorld PRIVATE basic)

#install target lib
install(TARGETS HelloWorld DESTINATION mains)

# add binary tree to the list of paths to search for include
# target_include_directories(HelloWorld PUBLIC "${PROJECT_BINARY_DIR}")