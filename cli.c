#include "headers/cli.h"
#include "headers/conf.h"
#include "headers/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void execute_cmd(const char *lnx, const char *win)
{
#if defined(__WIN32) || defined(__WIN64)
    system(win);
#elif defined(__linux__)
    system(lnx);
#endif
}

int getFrameAndRune(char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("FUCK ME");
        return -1;
    }

    char line[1024];
    int frame;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "frame=%d", &frame) == 1 || sscanf(line, "frame= %d", &frame) == 1) {
            printf("Progress: %d\n", frame);
        }
    }
    pclose(fp);
    return 0;
}

int getFrames(char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("I GIVE UP");
        return -1;
    }
    char line[512];
    int frame;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "nb_frames=%d", &frame) == 1) {
            printf("Frames: %d", frame);
            return frame;
        }
    }
    return -1;
}

typedef struct Name {
    char *cmd;
    int *x;
} ThreadArgs;

void *wraperune(void *args) {
    char *cmd = (char*)args;
    getFrameAndRune(cmd);
    free(cmd);
    return NULL;
}

void *ffprovewrap(void *args) {
    ThreadArgs *targs = (ThreadArgs*)args;
    *(targs->x) = getFrames(targs->cmd);
    free(targs->cmd);
    free(targs);
    return NULL;
}

void executeTheThing()
{
    char *encoder_strs[] = { "libx265", "libx264" };
    char *speed_strs[] = { "veryfast", "faster", "fast", "normal", "slow", "slower", "veryslow", "placebo" };
    char *audio_strs[] = { "65k", "96k", "128k", "160k", "192k", "256k" };
    char *video_strs[] = { "4M", "8M", "12M", "16M", "20M", "24M" };

    char *encoder = encoder_strs[rSet.encoder];
    char *speed   = speed_strs[rSet.speed];
    char *audorate = audio_strs[rSet.audiobitrate];
    char *vidrate  = video_strs[rSet.videorate];

    char cmd[2048];
    char ffprobecmd[1070]; //acording to gcc thats max it can get from text + pathBuf
    snprintf(cmd, sizeof(cmd),
            "ffmpeg -i '%s' -c:v %s -preset %s -crf %d -c:a libopus -b:a %s -b:v %s -progress pipe:1 tt.mp4 2>&1",
            pathBuf, encoder, speed, rSet.cfr, audorate, vidrate);

    snprintf(ffprobecmd, sizeof(ffprobecmd),
            "ffprobe -v error -show_format -show_streams '%s'",
            pathBuf);
    char *ccmd = strdup(cmd);
    int totalframes = 0;
    ThreadArgs *targs = malloc(sizeof(ThreadArgs));
    targs->cmd = strdup(ffprobecmd);
    targs->x = &totalframes;
    pthread_t tid2;
    pthread_create(&tid2, NULL, ffprovewrap, targs);
    pthread_detach(tid2);
    pthread_t tid;
    pthread_create(&tid, NULL, wraperune, ccmd);
    pthread_detach(tid);
}

