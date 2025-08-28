#ifndef APP_H
#define APP_H

typedef enum Parset {
    ANIME, VIDEO, CUSTOM,
} Parset;

typedef struct App {
    int width;
    int height;
    Parset parset;
} App;

#endif
