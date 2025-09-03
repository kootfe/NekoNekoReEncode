#include <tinyfiledialogs.h>
#include "headers/app.h"
#include "headers/input.h"
#include "headers/filework.h"
#include <stdio.h>

#ifndef CRN_OS
#if defined(__WIN32) || defined(__WIN64)
#define CRN_OS 0 
#elif defined(__linux__)
#define CRN_OS 1 
#else
#error "Unsported OS"
#endif
#endif

void* filedialogth(void *arg)
{
    App *app = (App*)arg;
    char *default_dir = CRN_OS ? "/" : "C:\\";
    const char *filters[] = {"*.mp4", "*.mkv"};

    const char *path = tinyfd_openFileDialog(
        "Select file",
        default_dir,
        2,
        filters,
        NULL,
        0
    );

    if (path) {
        snprintf(pathBuf, sizeof(pathBuf), "%s", path);
    }
    app->wantfile = 0; // mark done
    return NULL;
}
