#include <cglm/ease.h>
#include <leif/leif.h>
#include <stdint.h>
#include <stdio.h>
#include "headers/conf.h"
#include "headers/gui.h"
#include "headers/theme.h"
#include "headers/app.h"

#define MARGIN 10.0f
//this is general margin btw... not some special its magic number lol.
//This is top left right and bottom margin....
//body: {
//   margin: 10px;
//}
//like

void render_btn_clicked(App *app)
{
    printf("Current Parset: %s\n", app->parset < 2 ? (app->parset == 1 ? "Video" : "Anime") : "Custom");
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
    const char* types[] = {"Anime", "Video", "Custom"};
    for (uint32_t i = 0; i < 3; ++i) {
        app->parset == (Parset)i ? lf_push_style_props(btn_gray_active) : lf_push_style_props(btn_gray_inactive);
        if (lf_button(types[i]) == LF_CLICKED) {
            app->parset = (Parset)i;
        }

        lf_pop_style_props();
    }
    btn_gray_inactive.margin_top = 0.0f;
    btn_gray_inactive.margin_right = 0.0f;
}

void work_leif(App *app)
{
    lf_div_begin(v2s(MARGIN, MARGIN),v2s(app->width - MARGIN * 2.0f, app->height - MARGIN * 2.0f), 1);
    render_top(app);
    lf_next_line();
    render_menu(app);
    lf_div_end();
}
