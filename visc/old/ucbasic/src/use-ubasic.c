

#include "ubasic.h"

static const char program[] =
"\
5  print \"Hello!\"  \n\
10 for i = 1 to 10  \n\
20 print i \n\
25 print i/3\n\
30 next i \n\
";

int main(void)
{
  ubasic_init(program);

  do {
    ubasic_run();
  } while(!ubasic_finished());

  return 0;
}