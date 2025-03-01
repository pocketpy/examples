#include "pocketpy.h"
#include <math.h>

#define INPUT ""

typedef struct {
  float x;
  float y;
} Vector2;

static bool Vector2__new__(int argc, py_Ref argv) {
  py_Type cls = py_totype(argv);
  py_newobject(py_retval(), cls, 0, sizeof(Vector2));
  return true;
}

static bool Vector2__init__(int argc, py_Ref argv) {
  PY_CHECK_ARGC(3);
  Vector2 *self = py_touserdata(py_arg(0));
  if (!py_castfloat32(py_arg(1), &self->x)) {
    return false;
  }
  if (!py_castfloat32(py_arg(2), &self->y)) {
    return false;
  }
  py_newnone(py_retval());
  return true;
}

static bool Vector2_get_x(int argc, py_Ref argv) {
  PY_CHECK_ARGC(1);
  Vector2 *self = py_touserdata(py_arg(0));
  py_newfloat(py_retval(), self->x);
  return true;
}

static bool Vector2_get_y(int argc, py_Ref argv) {
  PY_CHECK_ARGC(1);
  Vector2 *self = py_touserdata(py_arg(0));
  py_newfloat(py_retval(), self->y);
  return true;
}

static bool Vector2_set_x(int argc, py_Ref argv) {
  PY_CHECK_ARGC(2);
  Vector2 *self = py_touserdata(py_arg(0));
  if (!py_castfloat32(py_arg(1), &self->x)) {
    return false;
  }
  py_newnone(py_retval());
  return true;
}

static bool Vector2_set_y(int argc, py_Ref argv) {
  PY_CHECK_ARGC(2);
  Vector2 *self = py_touserdata(py_arg(0));
  if (!py_castfloat32(py_arg(1), &self->y)) {
    return false;
  }
  py_newnone(py_retval());
  return true;
}

static bool Vector2_length(int argc, py_Ref argv) {
  PY_CHECK_ARGC(1);
  Vector2 *self = py_touserdata(py_arg(0));
  py_newfloat(py_retval(), sqrtf(self->x * self->x + self->y * self->y));
  return true;
}

int main() {
  py_initialize();

  py_GlobalRef test = py_newmodule("test");
  py_Type type = py_newtype("Vector2", tp_object, test, NULL);

  py_bindmethod(type, "__new__", Vector2__new__);
  py_bindmethod(type, "__init__", Vector2__init__);
  py_bindproperty(type, "x", Vector2_get_x, Vector2_set_x);
  py_bindproperty(type, "y", Vector2_get_y, Vector2_set_y);
  py_bindmethod(type, "length", Vector2_length);

  if (!py_exec(INPUT, "main.py", EXEC_MODE, NULL)) {
    py_printexc();
    goto finalize;
  }

finalize:
  py_finalize();
  return 0;
}