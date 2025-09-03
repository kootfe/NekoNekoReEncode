#ifndef CONF_H
#define CONF_H

#include <leif/leif.h>
#include "app.h"

extern App appM;

typedef enum EncoderE {
    libx265,
    libx264,
} EncoderE;

typedef enum SpeedE { //E stands for Encoder so it dont mess up other things
    VERY_FAST,
    FASTER,
    FAST,
    NORMAL,
    SLOW,
    SLOWER,
    VERY_SLOW,
    IM_MASHOISTIC //placebo
} SpeedE;

typedef enum AudoBitE {
    KBPS65,
    KBPS96,
    KBPS128,
    KBPS160,
    KBPS192,
    KBPS256
} AudoBitE;

typedef enum VideRate {
    MBPS4,
    MBPS8,
    MBPS12,
    MBPS16,
    MBPS20,
    MBPS24
} VideRate;

typedef struct RenderSetting {
    Parset parset;
    EncoderE encoder;
    int vbitrate;
    AudoBitE audiobitrate;
    VideRate videorate;
    int cfr;
    SpeedE speed;
} RenderSetting;
                        
extern RenderSetting rSet;

#endif
