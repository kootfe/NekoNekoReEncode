#ifndef CONF_H
#define CONF_H

#include <leif/leif.h>
#include "app.h"

extern App appM;

typedef enum EncoderE {
    libx265,
    libx264,
} EncoderE;

typedef struct RenderSetting {
    EncoderE encoder;
    int vbitrate;
    int audiobitrate;
    int cfr;
} RenderSetting;
                        
#endif
