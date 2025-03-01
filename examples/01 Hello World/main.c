#include "pocketpy.h"

int main() {
  // Initialize python environment
  // Call this function before using any other function from `pocketpy.h`
  py_initialize();

  // Hello world!
  bool ok = py_exec("print('Hello world!')", "<string>", EXEC_MODE, NULL);
  if (!ok) {
    // In case of error, print the exception message
    py_printexc();
  }

  // Finalize python environment
  // Call this function in the end of the program
  // After this call, you should not use any function from `pocketpy.h`
  py_finalize();
  return 0;
}
