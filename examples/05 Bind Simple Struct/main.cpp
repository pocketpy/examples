#include "pocketpy.h"

using namespace pkpy;

Str read_stdin(){
    SStream ss; char ch;
    while(std::cin.get(ch)) ss << ch;
    return ss.str();
}

struct Point{
    int x;
    int y;

    float distance(){
        return std::sqrt(x*x + y*y);
    }
}

struct wrapped__Point{
    // special macro for wrapper class
    PY_CLASS(wrapped__Point, builtins, Point)
    //       ^T              ^module   ^name

    // wrapped value
    Point value;

    // special method _ returns a pointer of the wrapped value
    Point* _() { return &value; }

    // define default constructors
    wrapped__Point() = default;
    wrapped__Point(const wrapped__Point&) = default;

    // define wrapped constructor
    wrapped__Point(Point value){
        this->value = value;
    }

    static void _register(VM* vm, PyObject* mod, PyObject* type){
        // enable default constructor and struct-like methods
        // if you don't use this, you must bind a `__new__` method as constructor
        PY_STRUCT_LIKE(wrapped__Point)

        // wrap field x
        PY_FIELD(wrapped__Point, "x", _, x)
        // wrap field y
        PY_FIELD(wrapped__Point, "y", _, y)

        // __init__ method
        vm->bind(type, "__init__(self, x, y)", [](VM* vm, ArgsView args){
            wrapped__Point& self = _py_cast<wrapped__Point&>(vm, args[0]);
            self.value.x = py_cast<int>(vm, args[1]);
            self.value.y = py_cast<int>(vm, args[2]);
            return vm->None;
        });

        vm->bind(type, "distance(self)", [](VM* vm, ArgsView args){
            wrapped__Point& self = _py_cast<wrapped__Point&>(vm, args[0]);
            return VAR(self.value.distance());
        });
    }
}