
/**
 * This example demonstrates the type casting feature of PocketPy.
 * It creates a virtual machine and cast PyVar to different types.
*/

#include "pocketpy.h"

using namespace pkpy;


int main(){
    // Create a virtual machine
    VM* vm = new VM();

    PyVar str_obj = py_var(vm, "hello world");
    // Cast PyVar to Str type
    Str& str = py_cast<Str&>(vm, str_obj); 
    std::cout << "string: " << str.c_str() << std::endl; // hello world


    PyVar int_obj = py_var(vm, 10);
    // Cast PyVar to Int type
    int int_var = py_cast<int>(vm, int_obj);
    std::cout << "int: " << int_var << std::endl; // 10

    PyVar float_obj = py_var(vm, 10.5);
    // Cast PyVar to double type
    double float_var = py_cast<double>(vm, float_obj);
    std::cout << "float: " << float_var << std::endl; // 10.5

    // Dispose the virtual machine
    delete vm;
    return 0;
}
