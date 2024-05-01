#include "pocketpy.h"

using namespace pkpy;

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    // Hello world!
    vm->exec("print('Hello world!')");

    // Dispose the virtual machine
    delete vm;
    return 0;
}