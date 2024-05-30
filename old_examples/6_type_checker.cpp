
/**
 * This example demonstrates how to create different types of objects and
 * how to check their types.
*/

#include "pocketpy.h"

using namespace pkpy;


int main(){
    // Create a virtual machine
    VM* vm = new VM();

    // Create a module
    PyVar type_checker = vm->new_module("type_checker");

    // Bind a function named "get_type" to the module
    vm->bind(type_checker, "get_type(obj: object) -> str",
        "Returns type of a python object",  // docstring
        [](VM* vm, ArgsView args){
            PyVar obj = args[0];
            if(is_type(obj, vm->tp_int)){
                return py_var(vm, "int");
            }
            else if(is_type(obj, vm->tp_str)){
                return py_var(vm, "str");
            }
            else if(is_type(obj, vm->tp_float)){
                return py_var(vm, "float");
            }
            else if(is_type(obj, vm->tp_bool)){
                return py_var(vm, "bool");
            }
            else if(is_type(obj, vm->tp_dict)){
                return py_var(vm, "dict");
            }
            else if(is_type(obj, vm->tp_list)){
                return py_var(vm, "list");
            }
            else if(is_type(obj, vm->tp_tuple)){
                return py_var(vm, "tuple");
            }
            else{
                return py_var(vm, "unknown");
            }
        });
    
    // Get the "get_type" function
    PyVar f_get_type = type_checker->attr("get_type");

    // Create a dictionary
    Dict d(vm);
    d.set(py_var(vm, "key"), py_var(vm, "value"));

    // Create a list
    List l;
    l.push_back(py_var(vm, "list_element"));

    // Declare a two-element tuple
    Tuple t(2);
    t[0] = py_var(vm, "tuple_element_0");
    t[1] = py_var(vm, "tuple_element_1");

    // Create different types of objects
    PyVar int_obj = py_var(vm, 1);
    PyVar str_obj = py_var(vm, "hello");
    PyVar float_obj = py_var(vm, 1.0);
    PyVar bool_obj = py_var(vm, true);
    PyVar dict_obj = py_var(vm, std::move(d));
    PyVar list_obj = py_var(vm, std::move(l));
    PyVar tuple_obj = py_var(vm, std::move(t));

    // Call the "get_type" function and print type of different objects
    std::cout << "Type of 1: " << CAST(Str&, vm->call(f_get_type, int_obj)) << std::endl;
    std::cout << "Type of \"hello\": " << CAST(Str&, vm->call(f_get_type, str_obj)) << std::endl;
    std::cout << "Type of 1.0: " << CAST(Str&, vm->call(f_get_type, float_obj)) << std::endl;
    std::cout << "Type of true: " << CAST(Str&, vm->call(f_get_type, bool_obj)) << std::endl;
    std::cout << "Type of {\"key\": \"value\" }: " << CAST(Str&, vm->call(f_get_type, dict_obj)) << std::endl;
    std::cout << "Type of [\"list_element\"]: " << CAST(Str&, vm->call(f_get_type, list_obj)) << std::endl;
    std::cout << "Type of (\"tuple_element_0\", \"tuple_element_1\"): " << CAST(Str&, vm->call(f_get_type, tuple_obj)) << std::endl;

    // Dispose the virtual machine
    delete vm;
    return 0;
}
