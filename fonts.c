#include "headers/fonts.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts/jetbold.h"
#include "headers/conf.h"

#if defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif


const char *dftt()
{
#if defined(__linux__)
    const char *path = "/tmp/myfont.ttf";
    FILE *f = fopen(path, "wb");
    if (!f) return NULL;

    fwrite(JetBrainsMonoExtraBold_ttf, 1, JetBrainsMonoExtraBold_ttf_len, f);
    fclose(f);
    return path;

#elif defined(_WIN32) || defined(_WIN64)
    static char path[MAX_PATH];
    DWORD ret = GetTempPathA(MAX_PATH, path);
    if (ret == 0 || ret >= MAX_PATH)
        return NULL;

    // Use snprintf to safely append the filename
    if (path[ret - 1] == '\\' || path[ret - 1] == '/')
        snprintf(path + ret, MAX_PATH - ret, "myfont.ttf");
    else
        snprintf(path + ret, MAX_PATH - ret, "\\myfont.ttf");

    FILE *f = fopen(path, "wb");
    if (!f) return NULL;

    fwrite(JetBrainsMonoExtraBold_ttf, 1, JetBrainsMonoExtraBold_ttf_len, f);
    fclose(f);

    return path;
#endif
}

void init_font()
{
    titlefont = malloc(sizeof(LfFont));
    const char *fntpath = dftt();
    if (!fntpath) {
        fprintf(stderr, "Failed to write font to tmp file\n");
        exit(-1);
    }

    *titlefont = lf_load_font(fntpath, 30);
    remove(fntpath); 
}
