#include "headers/fonts.h"
#include <leif/leif.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonts/jetbold.h"
#include "fonts/jetmono.h"
#include "fonts/spacemono.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define PATH_MAX_LEN MAX_PATH
#else
#include <limits.h>
#define PATH_MAX_LEN 512
#endif

int fontlenlist = 0;
int *fontlistlen = &fontlenlist;
LfFont **fontlist = NULL;

int dmpfonttolist(LfFont *var)
{
    (*fontlistlen)++; // increment font count

    if (*fontlistlen == 1) {
        fontlist = malloc(sizeof(LfFont*) * (*fontlistlen));
    } else {
        fontlist = realloc(fontlist, sizeof(LfFont*) * (*fontlistlen));
    }

    if (!fontlist) return -1; // always check malloc/realloc

    fontlist[*fontlistlen - 1] = var; // add the new font

    return 0;
}

void freefonts()
{
    for (int i = 0; i < *fontlistlen; ++i) {
        lf_free_font(fontlist[i]);
        free(fontlist[i]);
    }
    free(fontlist);
}

char *dftt(FontList font)
{
    static char path[PATH_MAX_LEN]; // works for both Linux and Windows
    FILE *f;

#if defined(__linux__)
    switch (font) {
        case JET_BOLD:
            snprintf(path, PATH_MAX_LEN, "/tmp/jetbold_nekoneko.ttf");
            f = fopen(path, "wb");
            if (!f) return NULL;
            fwrite(JetBrainsMonoExtraBold_ttf, 1, JetBrainsMonoExtraBold_ttf_len, f);
            fclose(f);
            return path;
        case JET_MONO:
            snprintf(path, PATH_MAX_LEN, "/tmp/jetmono_nekoneko.ttf");
            f = fopen(path, "wb");
            if (!f) return NULL;
            fwrite(jetmonofont, 1, jetmonofontlen, f); // <- use correct font
            fclose(f);
            return path;
        case SPACE_MONO:
            snprintf(path, PATH_MAX_LEN, "/tmp/spacemono_nekoneko.ttf");
            f = fopen(path, "wb");
            if (!f) return NULL;
            fwrite(spacemono_d, 1, spacemono_d_len, f);
            fclose(f);
            return path;
        default:
            return NULL;
    }
#elif defined(_WIN32) || defined(_WIN64)
    DWORD ret = GetTempPathA(PATH_MAX_LEN, path);
    if (ret == 0 || ret >= PATH_MAX_LEN)
        return NULL;

    const char *filename = (font == JET_BOLD) ? "jetbold_nekoneko.ttf" : (font == SPACE_MONO) ? "spacemono_nekoneko.ttf" : "jetmono_nekoneko.ttf";
    

    if (path[ret - 1] != '\\' && path[ret - 1] != '/')
        strncat(path, "\\", PATH_MAX_LEN - strlen(path) - 1);
    strncat(path, filename, PATH_MAX_LEN - strlen(path) - 1);

    f = fopen(path, "wb");
    if (!f) return NULL;

    if (font == JET_BOLD)
        fwrite(JetBrainsMonoExtraBold_ttf, 1, JetBrainsMonoExtraBold_ttf_len, f);
    else if (font == SPACE_MONO)
        fwrite(spacemono_d,1,spacemono_d_len,f);
    else
        fwrite(jetmonofont, 1, jetmonofontlen, f); // <- correct font

    fclose(f);
    return path;
#endif
}

void init_font(LfFont **fontvar, FontList font, int fontsize)
{
    *fontvar = malloc(sizeof(LfFont));
    if (!fontvar) {
        fprintf(stderr, "Failed to allocate font\n");
        exit(-1);
    }

    const char *fntpath = dftt(font);
    if (!fntpath) {
        fprintf(stderr, "Failed to write font to tmp file\n");
        exit(-1);
    }

    *(*fontvar) = lf_load_font(fntpath, fontsize);
    dmpfonttolist(*fontvar);
    remove(fntpath);
}

