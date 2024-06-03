#include "pocketpy.h"
#include <iostream>

using namespace pkpy;

Str read_stdin(){
    SStream ss; char ch;
    while(std::cin.get(ch)) ss << ch;
    return ss.str();
}

struct Point{
    int x;
    int y;

    void __init__(int x, int y){
        this->x = x;
        this->y = y;
    }

    float distance(){
        return std::sqrt(x*x + y*y);
    }
};


int main(){
    VM* vm = new VM();
    // Create a new module named "test"
    PyObject* mod = vm->new_module("test");
    // Register the Point class to the module
    vm->register_user_class<Point>(mod, "Point",
    [](VM* vm, PyObject* mod, PyObject* type){
        vm->bind_field(type, "x", &Point::x);
        vm->bind_field(type, "y", &Point::y);

        vm->bind(type, "__init__(self, x, y)", &Point::__init__);
        vm->bind(type, "distance(self)", &Point::distance);
    }, VM::tp_object, true);
    // Run code
    vm->exec(read_stdin());
    delete vm;
    return 0;
}