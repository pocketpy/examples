#include "pocketpy.h"
#include <stdio.h>

int main() {
  py_initialize();

  int x = 10;
  int y = 3;

  py_GlobalRef __main__ = py_getmodule("__main__");
  if (!py_getattr(__main__, py_name("multiply"))) {
    py_printexc();
    goto finalize;
  }

  py_push(py_retval());
  py_pushnil();
  py_newint(py_pushtmp(), x);
  py_newint(py_pushtmp(), y);

  if (!py_vectorcall(2, 0)) {
    py_printexc();
    goto finalize;
  }

  if (py_isint(py_retval())) {
    int res = py_toint(py_retval());
    printf("multiply(10, 3): %d\n", res);
  }

  if (!py_getattr(__main__, py_name("Multiplier"))) {
    py_printexc();
    goto finalize;
  }
  py_push(py_retval());
  py_pushnil();
  py_newint(py_pushtmp(), x);

  if (!py_vectorcall(1, 0)) {
    py_printexc();
    goto finalize;
  }

  py_push(py_retval());
  if (!py_pushmethod(py_name("multiply"))) {
    py_printexc();
    goto finalize;
  }
  py_newint(py_pushtmp(), y);

  if (!py_vectorcall(1, 0)) {
    py_printexc();
    goto finalize;
  }

  if (py_isint(py_retval())) {
    int res = py_toint(py_retval());
    printf("Multiplier(10).multiply(3): %d\n", res);
  }

finalize:
  py_finalize();
  return 0;
}