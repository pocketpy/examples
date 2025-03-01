#include "pocketpy.h"
#include <stdio.h>

static bool add_int(int argc, py_Ref argv) {
  PY_CHECK_ARGC(2);
  PY_CHECK_ARG_TYPE(0, tp_int);
  PY_CHECK_ARG_TYPE(1, tp_int);
  int a = py_toint(py_arg(0));
  int b = py_toint(py_arg(1));
  py_newint(py_retval(), a + b);
  return true;
}

// this magic macro is used to get the input string
#define INPUT ""

int main() {
  py_initialize();

  py_GlobalRef __main__ = py_getmodule("__main__");

  // Bind a function named "add" to the main module
  py_bindfunc(__main__, "add", add_int);

  if (!py_exec(INPUT, "main.py", EXEC_MODE, NULL)) {
    py_printexc();
    goto finalize;
  }

finalize:
  py_finalize();
  return 0;
}