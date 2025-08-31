#include <leif/leif.h>
#include <string.h>
#include "headers/input.h"

LfInputField pathInput;
char pathBuf[1024] = "";

void load_inputs()
{
    memset(pathBuf, 0, sizeof(pathBuf));
    pathInput = (LfInputField) {
        .width = 500,
        .buf = pathBuf,
        .buf_size = sizeof(pathBuf),
        .placeholder = (char*)"Path To File",
    };
}
