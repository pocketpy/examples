#include "pocketpy.h"
#include <stdio.h>

#define INPUT ""

static bool testadd(int argc, py_Ref argv) {
  PY_CHECK_ARGC(2);
  return py_binaryadd(&argv[0], &argv[1]);
}

int main() {
  py_initialize();

  py_compiletime_bind("testadd(__a, __b)", testadd);

  if (!py_exec(INPUT, "main.py", EXEC_MODE, NULL)) {
    py_printexc();
  }

  py_finalize();
  return 0;
}