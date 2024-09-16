#include <iostream>
#include <HelloProjConfig.h>

void hello_world()
{
    std::cout << "Hello world!\n";
}

void print_version()
{
    std::cout << "HelloProj version: " << HelloProj_VERSION_MAJOR << "."
              << HelloProj_VERSION_MINOR << "\n";
}

int main()
{
    hello_world();
    print_version();
    return 0;
}