#include "pocketpy.h"

using namespace pkpy;

int main(){
    // Create a virtual machine
    VM* vm = new VM();

    PyObject* str_obj = VAR("hello world");
    // Cast PyObject* to Str type
    Str& str_var = CAST(Str&, str_obj);
    std::cout << "str: " << str_var << std::endl;

    PyObject* int_obj = VAR(10);
    // Cast PyObject* to Int type
    int int_var = CAST(int, int_obj);
    std::cout << "int: " << int_var << std::endl;

    PyObject* float_obj = VAR(10.5);
    // Cast PyObject* to float type
    float float_var = CAST(float, float_obj);
    std::cout << "float: " << float_var << std::endl;

    // Create a tuple
    Tuple tuple_var(3);
    tuple_var[0] = str_obj;
    tuple_var[1] = int_obj;
    tuple_var[2] = float_obj;
    PyObject* tuple_obj = VAR(std::move(tuple_var));
    PyObject* tuple_repr = vm->py_repr(tuple_obj);
    std::cout << "tuple: " << CAST(Str&, tuple_repr) << std::endl;

    // Create a list
    List list_var;
    list_var.push_back(str_obj);
    list_var.push_back(int_obj);
    list_var.push_back(float_obj);
    PyObject* list_obj = VAR(std::move(list_var));
    PyObject* list_repr = vm->py_repr(list_obj);
    std::cout << "list: " << CAST(Str&, list_repr) << std::endl;

    // Create a dict
    Dict dict_var(vm);
    dict_var.set(VAR("str"), str_obj);
    dict_var.set(VAR("int"), int_obj);
    dict_var.set(VAR("float"), float_obj);
    PyObject* dict_obj = VAR(std::move(dict_var));
    PyObject* dict_repr = vm->py_repr(dict_obj);
    std::cout << "dict: " << CAST(Str&, dict_repr) << std::endl;

    // Dispose the virtual machine
    delete vm;
    return 0;
}