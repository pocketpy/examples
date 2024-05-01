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

    // Run code first
    vm->exec(read_stdin());

    int x = 10;
    int y = 3;

    PyObject* f_multiply = vm->_main->attr("multiply");
    PyObject* result1 = vm->call(f_multiply, VAR(x), VAR(y));
    std::cout << "multiply(10, 3): " << CAST(int, result1) << std::endl;

    PyObject* Multiplier = vm->_main->attr("Multiplier");
    PyObject* multiplier = vm->call(Multiplier, VAR(x));
    PyObject* result2 = vm->call_method(multiplier, "multiply", VAR(y));
    std::cout << "Multiplier(10).multiply(3): " << CAST(int, result2) << std::endl;

    // Dispose the virtual machine
    delete vm;
    return 0;
}