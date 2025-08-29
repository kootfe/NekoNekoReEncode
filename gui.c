#include <cglm/ease.h>
#include <leif/leif.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "headers/gui.h"
#include "headers/conf.h"
#include "headers/theme.h"
#include "headers/app.h"
#include "headers/utils.h"

#define MARGIN 10.0f
//this is general margin btw... not some special its magic number lol.
//This is top left right and bottom margin....
//body: {
//   margin: 10px;
//}
//like

void render_btn_clicked(App *app)
{
    printf("Encoder(INT): %d\nCFR: %d\nParset(INT)%d\n", rSet.encoder, rSet.cfr, rSet.parset);
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
    lf_dropdown_menu(encoder, "Encoder", 2, 215, 80, &val, &open);
    lf_pop_style_props();
    rSet.encoder = (EncoderE)val;
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

void work_leif(App *app)
{
    lf_div_begin(v2s(MARGIN, MARGIN),v2s(app->width - MARGIN * 2.0f, app->height - MARGIN * 2.0f), 1);
    render_top(app);
    lf_next_line();
    render_menu(app);
    lf_next_line();
    render_settings(app);

    encoderSelector(app);
    lf_next_line();
    cfrSelector(app);
    lf_div_end();
}
