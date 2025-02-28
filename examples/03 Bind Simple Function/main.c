#include "pocketpy.h"
#include <iostream>

using namespace pkpy;

Str read_stdin(){
    SStream ss; char ch;
    while(std::cin.get(ch)) ss << ch;
    return ss.str();
}

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    // Bind a function named "add" to the main module
    vm->bind(vm->_main, "add(a: int, b: int)", [](VM* vm, ArgsView args){
        int a = CAST(int, args[0]);
        int b = CAST(int, args[1]);
        return VAR(a + b);
    });

    // Run code
    vm->exec(read_stdin());

    // Dispose the virtual machine
    delete vm;
    return 0;
}