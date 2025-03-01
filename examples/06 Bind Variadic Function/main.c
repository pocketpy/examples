#include "pocketpy.h"
#include <stdio.h>

#define INPUT ""

static bool my_print(int argc, py_Ref argv) {
  PY_CHECK_ARGC(2);
  PY_CHECK_ARG_TYPE(0, tp_tuple);
  PY_CHECK_ARG_TYPE(1, tp_str);

  int length = py_tuple_len(py_arg(0));
  const char *sep = py_tostr(py_arg(1));

  for (int i = 0; i < length; i++) {
    py_Ref item = py_tuple_getitem(py_arg(0), i);
    if (!py_str(item)) {
      return false;
    }
    printf("%s", py_tostr(py_retval()));
    if (i < length - 1)
      printf("%s", sep);
  }
  printf("\n");
  py_newnone(py_retval());
  return true;
}

int main() {
  py_initialize();

  py_GlobalRef __main__ = py_getmodule("__main__");
  py_bind(__main__, "my_print(*args, sep=', ')", my_print);

  if (!py_exec(INPUT, "main.py", EXEC_MODE, NULL)) {
    py_printexc();
  }

  py_finalize();
  return 0;
}