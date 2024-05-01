#include "pocketpy.h"

using namespace pkpy;

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    // Hello world!
    vm->exec("print('Hello world!')");

    // Create a list
    vm->exec("a = [1, 2, 3]");

    // Eval the sum of the list
    PyObject* result = vm->eval("sum(a)");
    std::cout << "Sum of the list: "<< py_cast<int>(vm, result) << std::endl;   // 6

    // Bindings
    vm->bind(vm->_main, "add(a: int, b: int)",
      [](VM* vm, ArgsView args){
        int a = py_cast<int>(vm, args[0]);
        int b = py_cast<int>(vm, args[1]);
        return py_var(vm, a + b);
      });

    // Call the function
    PyObject* f_add = vm->_main->attr("add");
    result = vm->call(f_add, py_var(vm, 3), py_var(vm, 7));
    std::cout << "Sum of 2 variables: "<< py_cast<int>(vm, result) << std::endl;   // 10

    // Dispose the virtual machine
    delete vm;
    return 0;
}