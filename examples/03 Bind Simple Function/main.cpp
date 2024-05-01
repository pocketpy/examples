#include "pocketpy.h"

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
        int a = py_cast<int>(vm, args[0]);
        int b = py_cast<int>(vm, args[1]);
        return py_var(vm, a + b);
    });

    // Run code
    vm->exec(read_stdin());

    // Dispose the virtual machine
    delete vm;
    return 0;
}