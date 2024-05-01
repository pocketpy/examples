#include "pocketpy.h"

using namespace pkpy;

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    PyObject* str_obj = VAR("hello world");
    // Cast PyObject* to Str type
    Str& str = CAST(Str&, str_obj);
    std::cout << "string: " << str.c_str() << std::endl; // hello world

    PyObject* int_obj = VAR(10);
    // Cast PyObject* to Int type
    int int_var = CAST(int, int_obj);
    std::cout << "int: " << int_var << std::endl; // 10

    PyObject* float_obj = VAR(10.5);
    // Cast PyObject* to double type
    double float_var = CAST(double, float_obj);
    std::cout << "float: " << float_var << std::endl; // 10.5

    // Dispose the virtual machine
    delete vm;
    return 0;
}