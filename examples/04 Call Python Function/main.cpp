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
    PyObject* result1 = vm->call(f_multiply, py_var(vm, x), py_var(vm, y));

    PyObject* Multiplier = vm->_main->attr("Multiplier");
    PyObject* multiplier = vm->call(Multiplier, py_var(vm, x));
    PyObject* result2 = vm->call_method(multiplier, "multiply", py_var(vm, y));

    std::cout << "multiply(10, 3): " << py_cast<int>(vm, result1) << std::endl;
    std::cout << "Multiplier(10).multiply(3): " << py_cast<int>(vm, result2) << std::endl;

    // Dispose the virtual machine
    delete vm;
    return 0;
}