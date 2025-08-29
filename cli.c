#include "headers/cli.h"
#include <stdlib.h>

void execute_cmd(const char *lnx, const char *win)
{
#if defined(__WIN32) || defined(__WIN64)
    system(win);
#elif defined(__linux__)
    system(lnx);
#endif
}
