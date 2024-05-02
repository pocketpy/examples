#include "pocketpy.h"

using namespace pkpy;

Str read_stdin(){
    SStream ss; char ch;
    while(std::cin.get(ch)) ss << ch;
    return ss.str();
}

struct Point{
    PY_CLASS(Point, test, Point)

    int x;
    int y;

    void __init__(int x, int y){
        this->x = x;
        this->y = y;
    }

    Point* _() {
        return this;
    }

    float distance(){
        return std::sqrt(x*x + y*y);
    }

    static void _register(VM* vm, PyObject* mod, PyObject* type){
        PY_FIELD(Point, "x", _, x)
        PY_FIELD(Point, "y", _, y)

        _bind(vm, type, "__init__(self, x, y)", &Point::__init__);
        _bind(vm, type, "distance(self)", &Point::distance);
    }
};


int main(){
    VM* vm = new VM();
    PyObject* mod = vm->new_module("test");
    Point::register_class(vm, mod);
    vm->exec(read_stdin());
    delete vm;
    return 0;
}