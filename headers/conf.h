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
    FASTEST,
    FAST,
    NORMAL,
    SLOW,
    SLOWER,
    VERY_SLOW,
    IM_MASHOISTIC //placebo
} SpeedE;

typedef struct RenderSetting {
    Parset parset;
    EncoderE encoder;
    int vbitrate;
    int audiobitrate;
    int cfr;
    SpeedE speed;
} RenderSetting;
                        
extern RenderSetting rSet;
#endif
