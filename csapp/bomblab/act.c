/* ecercise code for using gdb
 */
#include <stdio.h>
int main(int argc, char** argv) {
  int ret = printf("%s\n", argv[argc-1]);
  return ret; // number of characters printed
}
