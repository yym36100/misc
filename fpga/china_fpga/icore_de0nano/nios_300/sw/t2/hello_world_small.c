
#include "sys/alt_stdio.h"

int main()
{ 
	// terminal codes here: http://www.termsys.demon.co.uk/vtansi.htm
	char buffer[] = "\033c\033[32;40;1m>Start \033[37m [Done]\n";

  alt_putstr(buffer);

  /* Event loop never exits. */
  while (1);

  return 0;
}
