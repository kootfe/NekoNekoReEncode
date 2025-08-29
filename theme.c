#include <leif/leif.h>
#include <stdio.h>
#include "headers/theme.h"
#include "headers/fonts.h"

// Define the globals
LfUIElementProps cyan_button;
LfUIElementProps btn_gray_inactive;
LfUIElementProps btn_gray_active;
LfUIElementProps dropdownStyle;
LfUIElementProps cfrButton;

LfFont *titlefont;
LfFont *btnfont;

void init_theme()
{
    // Initialize cyan button
    cyan_button = lf_get_theme().button_props;
    cyan_button.margin_left = 0.0f;
    cyan_button.margin_right = 0.0f;
    cyan_button.color = (LfColor){65, 167, 205, 255};
    cyan_button.border_width = 0;
    cyan_button.corner_radius = 4.0f;

    // Initialize gray inactive button
    btn_gray_inactive = lf_get_theme().button_props;
    btn_gray_inactive.margin_left = 0.0f;
    btn_gray_inactive.margin_right = 0.0f;
    btn_gray_inactive.color = LF_NO_COLOR;
    btn_gray_inactive.border_width = 0;
    btn_gray_inactive.text_color = LF_WHITE;
    btn_gray_inactive.corner_radius = 4.0f;

    btn_gray_active = lf_get_theme().button_props;
    btn_gray_active.margin_left = 0.0f;
    btn_gray_active.margin_right = 0.0f;
    btn_gray_active.color = (LfColor){104, 104, 104, 255};
    btn_gray_active.border_width = 0;
    btn_gray_active.text_color = LF_WHITE;
    btn_gray_active.corner_radius = 4.0f;
    
    dropdownStyle = lf_get_theme().button_props;
    dropdownStyle.color = LF_NO_COLOR;       // don't paint the background
    dropdownStyle.border_width = 1;
    dropdownStyle.corner_radius = 5.0f;
    dropdownStyle.text_color = LF_WHITE;     // text color

    cfrButton = lf_get_theme().button_props;
    cfrButton.margin_right = 0.0f;
    cfrButton.corner_radius = 7.0f;
    cfrButton.border_width = 0;
    cfrButton.color = (LfColor){52,52,52,255};
    cfrButton.text_color = LF_WHITE;

    init_font(&titlefont, JET_BOLD, 30);
    init_font(&btnfont, JET_MONO, 20);
}

