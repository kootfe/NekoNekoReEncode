#include <cglm/ease.h>
#include <leif/leif.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "headers/gui.h"
#include "headers/cli.h"
#include "headers/conf.h"
#include "headers/theme.h"
#include "headers/app.h"
#include "headers/input.h"
#include "headers/utils.h"
#include <tinyfiledialogs.h>

#define MARGIN 10.0f
//this is general margin btw... not some special its magic number lol.
//This is top left right and bottom margin....
//body: {
//   margin: 10px;
//}
//like

void render_btn_clicked(App *app)
{
    executeTheThing();
}

vec2s v2s(float x, float y)
{
    vec2s res;
    res.x = x;
    res.y = y;
    return res;
}

void render_top(App *app)
{
    lf_push_font(titlefont);
#if defined(__linux__)
    lf_text("NekoNeko ReEncode");
#elif defined(_WIN32) || defined(_WIN64)
    lf_text("NekoNeko ReEncode - Switch To Linux");
#endif
    lf_pop_font();

    {
        const float btnw = 160.0f;
        lf_set_ptr_x_absolute(app->width - btnw - 20 - MARGIN * 2.0f);
        lf_set_line_should_overflow(0);
        lf_push_style_props(cyan_button);
        if (lf_button_fixed("Render", btnw, -1) == LF_CLICKED) render_btn_clicked(app);
        lf_set_line_should_overflow(1);
        lf_pop_style_props();
    }
}


void render_menu(App *app)
{
    lf_push_font(btnfont);
    const char* types[] = {"Anime", "Video", "Custom"};
    for (uint32_t i = 0; i < 3; ++i) {
        app->parset == (Parset)i ? lf_push_style_props(btn_gray_active) : lf_push_style_props(btn_gray_inactive);
        if (lf_button(types[i]) == LF_CLICKED) {
            app->parset = (Parset)i;
            rSet.parset = (Parset)i;
        }

        lf_pop_style_props();
    }
    lf_pop_font();
}

void render_settings(App *app)
{
    char parset[20] = "";
    switch (app->parset) {
        case ANIME: stack_strcpy(parset, sizeof(parset), "Anime"); break;
        case VIDEO: stack_strcpy(parset, sizeof(parset), "Video"); break;
        case CUSTOM: stack_strcpy(parset, sizeof(parset), "Custom"); break;
    }
}

void encoderSelector(App *app)
{
    lf_text("Encoder:");
    static const char *encoder[] = { "libx265(recomended)", "libx264"};
    static bool open = false;
    static int val = 0;
    lf_push_style_props(dropdownStyle);
    lf_dropdown_menu(encoder, "Encoder", 2, 215, 60, &val, &open);
    lf_pop_style_props();
    rSet.encoder = (EncoderE)val;
}

void render_audio_bitrate_selector(App *app)
{
    lf_text("Audio Bitrate");
    static const char *bitrates[] = { "65kbps", "96kbps", "128kbps", "160kbps", "192kbps", "256kbps" };
    static bool open = false;
    static int val = 2; //def 128
    lf_push_style_props(dropdownStyle);
    lf_dropdown_menu(bitrates, "Bitrate", 6, 215, 180, &val, &open);
    lf_pop_style_props();
    rSet.audiobitrate = (AudoBitE)val;
}

void render_video_bitrate_sel(App *app)
{
    lf_text("Video Bitrate");
    static const char *bitrates[] = { "4MBPS", "8Mpbs", "12MPBS", "16Mpbs", "20Mpbs", "24Mpbs" };
    static bool open = false;
    static int val = 2; //def 8
    lf_push_style_props(dropdownStyle);
    lf_dropdown_menu(bitrates, "Bitrate", 6, 215, 180, &val, &open);
    lf_pop_style_props();
    rSet.videorate = (VideRate)val;
}


void cfrSelector(App *app)
{
    static int val = 0;
    lf_text("CFR:");
    lf_push_style_props(cfrButton);
    if (lf_button("-") == LF_CLICKED) val > 0 ? val-- : val;
    char buff[5] = "";
    sprintf(buff, "%d  ", val);
    lf_text(buff);
    if (lf_button("+") == LF_CLICKED) val < 30 ? val++ : val;
    lf_pop_style_props();
    rSet.cfr = val;
}

void speedSelector(App *app)
{
    lf_text("Speed: ");
    static int val = 0;
    static const char *speed[] = {
        "Very Fast", "Faster", "Fast",
        "Normal",
        "Slow", "Slower", "Very Slow",
        "Placebo"
    };
    static bool op = 0;
    lf_push_style_props(dropdownStyle);
    lf_dropdown_menu(speed, "Speed", 8, 215, 200, &val, &op);
    lf_pop_style_props();
    rSet.speed = (SpeedE)val;
}

void render_file_selc(App *app)
{
    lf_input_text(&pathInput);
    if (lf_button("Pick") == LF_CLICKED) {
        app->wantfile = 1;
    }
}


void work_leif(App *app)
{
    lf_div_begin(v2s(MARGIN, MARGIN),v2s(app->width - MARGIN * 2.0f, app->height - MARGIN * 2.0f), 1);
    render_top(app);
    lf_next_line();
    render_menu(app);
    lf_next_line();
    render_file_selc(app);
    lf_next_line();
    encoderSelector(app);
    render_video_bitrate_sel(app);
    lf_next_line();
    render_audio_bitrate_selector(app);
    lf_next_line();
    cfrSelector(app);
    speedSelector(app);
    lf_div_end();
}
