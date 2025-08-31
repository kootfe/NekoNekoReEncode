#ifndef FONTS_H
#define FONTS_H

#include <leif/leif.h>
typedef enum FontList {
    JET_BOLD, JET_MONO,
    SPACE_MONO
} FontList;

char *dftt(FontList font);
void init_font(LfFont **fontvar, FontList font, int fontsize);
void freefonts();

extern LfFont **fontlist;
extern int *fontlistlen;
#endif
