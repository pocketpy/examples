#include "pocketpy.h"
#include <iostream>

using namespace pkpy;

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    PyVar str_obj = VAR("hello world");
    // Cast PyVar to Str type
    Str& str_var = CAST(Str&, str_obj);
    std::cout << "str: " << str_var << std::endl;

    PyVar int_obj = VAR(10);
    // Cast PyVar to Int type
    int int_var = CAST(int, int_obj);
    std::cout << "int: " << int_var << std::endl;

    PyVar float_obj = VAR(10.5);
    // Cast PyVar to float type
    float float_var = CAST(float, float_obj);
    std::cout << "float: " << float_var << std::endl;

    // Create a tuple
    Tuple tuple_var(3);
    tuple_var[0] = str_obj;
    tuple_var[1] = int_obj;
    tuple_var[2] = float_obj;
    PyVar tuple_obj = VAR(std::move(tuple_var));
    std::cout << "tuple: " <<  vm->py_repr(tuple_obj) << std::endl;

    // Create a list
    List list_var;
    list_var.push_back(str_obj);
    list_var.push_back(int_obj);
    list_var.push_back(float_obj);
    PyVar list_obj = VAR(std::move(list_var));
    std::cout << "list: " << vm->py_repr(list_obj) << std::endl;

    // Create a dict
    Dict dict_var;
    dict_var.set(vm, VAR("str"), str_obj);
    dict_var.set(vm, VAR("int"), int_obj);
    dict_var.set(vm, VAR("float"), float_obj);
    PyVar dict_obj = VAR(std::move(dict_var));
    std::cout << "dict: " << vm->py_repr(dict_obj) << std::endl;

    // Dispose the virtual machine
    delete vm;
    return 0;
}