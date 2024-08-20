#include "view_pages.h"
#include "ui_manager/event.h"
#include "ui_manager/pm.h"
#include "math.h"
// #include "esp_log.h"

static lv_obj_t *meter;
static lv_meter_indicator_t *focus_arc;
static lv_meter_indicator_t *rest_arc;

lv_obj_t * ui_Page_TimeSelect;
lv_obj_t * ui_SelectPanel;

lv_obj_t * ui_Selectbtn1;
lv_obj_t * ui_Selectbtn1text;
lv_obj_t * ui_Selectbtn1del;
lv_obj_t * ui_Selectbtn1edit;

lv_obj_t * ui_Selectbtn2;
lv_obj_t * ui_Selectbtn2text;
lv_obj_t * ui_Selectbtn2del;
lv_obj_t * ui_Selectbtn2edit;

lv_obj_t * ui_Selectbtn3;
lv_obj_t * ui_Selectbtn3text;
lv_obj_t * ui_Selectbtn3del;
lv_obj_t * ui_Selectbtn3edit;

lv_obj_t * ui_Selectbtn4;
lv_obj_t * ui_Selectbtn4text;
lv_obj_t * ui_Selectbtn4del;
lv_obj_t * ui_Selectbtn4edit;

lv_obj_t * ui_Selectbtn5;
lv_obj_t * ui_Selectbtn5text;
lv_obj_t * ui_Selectbtn5del;
lv_obj_t * ui_Selectbtn5edit;

lv_obj_t * ui_Selectbtn6;
lv_obj_t * ui_Selectbtn6text;
lv_obj_t * ui_Selectbtn6del;
lv_obj_t * ui_Selectbtn6edit;

lv_obj_t * ui_Selectbtn7;
lv_obj_t * ui_Selectbtn7text;
lv_obj_t * ui_Selectbtn7del;
lv_obj_t * ui_Selectbtn7edit;

lv_obj_t * ui_Selectbtn8;
lv_obj_t * ui_Selectbtn8text;
lv_obj_t * ui_Selectbtn8del;
lv_obj_t * ui_Selectbtn8edit;

lv_obj_t * ui_Selectbtn9;
lv_obj_t * ui_Selectbtn9text;
lv_obj_t * ui_Selectbtn9del;
lv_obj_t * ui_Selectbtn9edit;

lv_obj_t * ui_Selectbtn10;
lv_obj_t * ui_Selectbtn10text;
lv_obj_t * ui_Selectbtn10del;
lv_obj_t * ui_Selectbtn10edit;

void ui_Page_TimeSelect_screen_init();

void view_pages_init()
{
    ui_Page_TimeSelect_screen_init();
}

void init_pie_chart(lv_obj_t *parent) {
    meter = lv_meter_create(parent);

    /*Remove the background and the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_MAIN);
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    lv_obj_set_size(meter, 100, 100);
    lv_obj_center(meter);

    /*Add a scale first with no ticks.*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 0, 0, 0, lv_color_black());
    lv_meter_set_scale_range(meter, scale, 0, 100, 360, 0);

    /*Add a three arc indicator*/
    lv_coord_t indic_w = 100;
    lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, indic_w,lv_palette_main(LV_PALETTE_ORANGE), 0);
    lv_meter_set_indicator_start_value(meter, indic1, 0);
    lv_meter_set_indicator_end_value(meter, indic1, 40);

    lv_meter_indicator_t * indic2 = lv_meter_add_arc(meter, scale, indic_w, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(meter, indic2, 40);  /*Start from the previous*/
    lv_meter_set_indicator_end_value(meter, indic2, 100);

}


void update_pie_chart(int focus_time, int rest_time) {
    if (meter == NULL || focus_arc == NULL || rest_arc == NULL) {
        // ESP_LOGE("Pie Chart", "Meter or indicators are not initialized. Call init_pie_chart first.");
        return;
    }

    int total_time = focus_time + rest_time;
    int focus_percentage = (focus_time * 100) / total_time;
    int rest_percentage = 100 - focus_percentage;  // 剩余的百分比就是休息时间的百分比

    // 更新专注时长的弧形显示
    lv_meter_set_indicator_start_value(meter, focus_arc, 0);
    lv_meter_set_indicator_end_value(meter, focus_arc, focus_percentage);

    // 更新休息时长的弧形显示
    lv_meter_set_indicator_start_value(meter, rest_arc, focus_percentage);
    lv_meter_set_indicator_end_value(meter, rest_arc, 100);
}

void ui_Page_TimeSelect_screen_init(void)
{
    ui_Page_TimeSelect = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Page_TimeSelect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SelectPanel = lv_obj_create(ui_Page_TimeSelect);
    lv_obj_set_width(ui_SelectPanel, 280);
    lv_obj_set_height(ui_SelectPanel, 240);
    lv_obj_set_align(ui_SelectPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_SelectPanel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_SelectPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scrollbar_mode(ui_SelectPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_SelectPanel, LV_DIR_VER);
    lv_obj_set_style_radius(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SelectPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SelectPanel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SelectPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SelectPanel, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_SelectPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn1 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn1, 280);
    lv_obj_set_height(ui_Selectbtn1, 60);
    lv_obj_set_align(ui_Selectbtn1, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn1, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Selectbtn1, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Selectbtn1text = lv_label_create(ui_Selectbtn1);
    lv_obj_set_width(ui_Selectbtn1text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn1text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn1text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn1text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn1text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn1del = lv_btn_create(ui_Selectbtn1);
    lv_obj_set_width(ui_Selectbtn1del, 45);
    lv_obj_set_height(ui_Selectbtn1del, 40);
    lv_obj_set_align(ui_Selectbtn1del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn1del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn1del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn1del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn1del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn1del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn1del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn1del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn1edit = lv_btn_create(ui_Selectbtn1);
    lv_obj_set_width(ui_Selectbtn1edit, 45);
    lv_obj_set_height(ui_Selectbtn1edit, 40);
    lv_obj_set_x(ui_Selectbtn1edit, -60);
    lv_obj_set_y(ui_Selectbtn1edit, 0);
    lv_obj_set_align(ui_Selectbtn1edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn1edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn1edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn1edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn1edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn1edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn1edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn1edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn2 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn2, 280);
    lv_obj_set_height(ui_Selectbtn2, 60);
    lv_obj_set_x(ui_Selectbtn2, 2);
    lv_obj_set_y(ui_Selectbtn2, 38);
    lv_obj_set_align(ui_Selectbtn2, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn2, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn2, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Selectbtn2, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Selectbtn2text = lv_label_create(ui_Selectbtn2);
    lv_obj_set_width(ui_Selectbtn2text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn2text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn2text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn2text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn2text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn2del = lv_btn_create(ui_Selectbtn2);
    lv_obj_set_width(ui_Selectbtn2del, 45);
    lv_obj_set_height(ui_Selectbtn2del, 40);
    lv_obj_set_align(ui_Selectbtn2del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn2del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn2del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn2del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn2del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn2del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn2del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn2del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn2edit = lv_btn_create(ui_Selectbtn2);
    lv_obj_set_width(ui_Selectbtn2edit, 45);
    lv_obj_set_height(ui_Selectbtn2edit, 40);
    lv_obj_set_x(ui_Selectbtn2edit, -60);
    lv_obj_set_y(ui_Selectbtn2edit, 0);
    lv_obj_set_align(ui_Selectbtn2edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn2edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn2edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn2edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn2edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn2edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn2edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn2edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn3 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn3, 280);
    lv_obj_set_height(ui_Selectbtn3, 60);
    lv_obj_set_align(ui_Selectbtn3, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn3, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Selectbtn3, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Selectbtn3text = lv_label_create(ui_Selectbtn3);
    lv_obj_set_width(ui_Selectbtn3text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn3text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn3text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn3text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn3text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn3del = lv_btn_create(ui_Selectbtn3);
    lv_obj_set_width(ui_Selectbtn3del, 45);
    lv_obj_set_height(ui_Selectbtn3del, 40);
    lv_obj_set_align(ui_Selectbtn3del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn3del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn3del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn3del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn3del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn3del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn3del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn3del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn3edit = lv_btn_create(ui_Selectbtn3);
    lv_obj_set_width(ui_Selectbtn3edit, 45);
    lv_obj_set_height(ui_Selectbtn3edit, 40);
    lv_obj_set_x(ui_Selectbtn3edit, -60);
    lv_obj_set_y(ui_Selectbtn3edit, 0);
    lv_obj_set_align(ui_Selectbtn3edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn3edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn3edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn3edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn3edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn3edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn3edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn3edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn4 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn4, 280);
    lv_obj_set_height(ui_Selectbtn4, 60);
    lv_obj_set_align(ui_Selectbtn4, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn4, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn4, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Selectbtn4, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Selectbtn4text = lv_label_create(ui_Selectbtn4);
    lv_obj_set_width(ui_Selectbtn4text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn4text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn4text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn4text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn4text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn4del = lv_btn_create(ui_Selectbtn4);
    lv_obj_set_width(ui_Selectbtn4del, 45);
    lv_obj_set_height(ui_Selectbtn4del, 40);
    lv_obj_set_align(ui_Selectbtn4del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn4del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn4del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn4del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn4del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn4del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn4del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn4del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn4edit = lv_btn_create(ui_Selectbtn4);
    lv_obj_set_width(ui_Selectbtn4edit, 45);
    lv_obj_set_height(ui_Selectbtn4edit, 40);
    lv_obj_set_x(ui_Selectbtn4edit, -60);
    lv_obj_set_y(ui_Selectbtn4edit, 0);
    lv_obj_set_align(ui_Selectbtn4edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn4edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn4edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn4edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn4edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn4edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn4edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn4edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn5 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn5, 280);
    lv_obj_set_height(ui_Selectbtn5, 60);
    lv_obj_set_align(ui_Selectbtn5, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn5, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn5, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Selectbtn5, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Selectbtn5text = lv_label_create(ui_Selectbtn5);
    lv_obj_set_width(ui_Selectbtn5text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn5text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn5text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn5text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn5text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn5del = lv_btn_create(ui_Selectbtn5);
    lv_obj_set_width(ui_Selectbtn5del, 45);
    lv_obj_set_height(ui_Selectbtn5del, 40);
    lv_obj_set_align(ui_Selectbtn5del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn5del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn5del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn5del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn5del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn5del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn5del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn5del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn5edit = lv_btn_create(ui_Selectbtn5);
    lv_obj_set_width(ui_Selectbtn5edit, 45);
    lv_obj_set_height(ui_Selectbtn5edit, 40);
    lv_obj_set_x(ui_Selectbtn5edit, -60);
    lv_obj_set_y(ui_Selectbtn5edit, 0);
    lv_obj_set_align(ui_Selectbtn5edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn5edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn5edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn5edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn5edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn5edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn5edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn5edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn6 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn6, 280);
    lv_obj_set_height(ui_Selectbtn6, 60);
    lv_obj_set_align(ui_Selectbtn6, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn6, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn6, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn6text = lv_label_create(ui_Selectbtn6);
    lv_obj_set_width(ui_Selectbtn6text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn6text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn6text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn6text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn6text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn6del = lv_btn_create(ui_Selectbtn6);
    lv_obj_set_width(ui_Selectbtn6del, 45);
    lv_obj_set_height(ui_Selectbtn6del, 40);
    lv_obj_set_align(ui_Selectbtn6del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn6del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn6del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn6del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn6del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn6del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn6del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn6del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn6edit = lv_btn_create(ui_Selectbtn6);
    lv_obj_set_width(ui_Selectbtn6edit, 45);
    lv_obj_set_height(ui_Selectbtn6edit, 40);
    lv_obj_set_x(ui_Selectbtn6edit, -60);
    lv_obj_set_y(ui_Selectbtn6edit, 0);
    lv_obj_set_align(ui_Selectbtn6edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn6edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn6edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn6edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn6edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn6edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn6edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn6edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn7 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn7, 280);
    lv_obj_set_height(ui_Selectbtn7, 60);
    lv_obj_set_align(ui_Selectbtn7, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn7, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn7, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn7, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn7text = lv_label_create(ui_Selectbtn7);
    lv_obj_set_width(ui_Selectbtn7text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn7text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn7text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn7text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn7text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn7del = lv_btn_create(ui_Selectbtn7);
    lv_obj_set_width(ui_Selectbtn7del, 45);
    lv_obj_set_height(ui_Selectbtn7del, 40);
    lv_obj_set_align(ui_Selectbtn7del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn7del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn7del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn7del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn7del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn7del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn7del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn7del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn7edit = lv_btn_create(ui_Selectbtn7);
    lv_obj_set_width(ui_Selectbtn7edit, 45);
    lv_obj_set_height(ui_Selectbtn7edit, 40);
    lv_obj_set_x(ui_Selectbtn7edit, -60);
    lv_obj_set_y(ui_Selectbtn7edit, 0);
    lv_obj_set_align(ui_Selectbtn7edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn7edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn7edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn7edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn7edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn7edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn7edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn7edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn8 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn8, 280);
    lv_obj_set_height(ui_Selectbtn8, 60);
    lv_obj_set_align(ui_Selectbtn8, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn8, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn8, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn8, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn8text = lv_label_create(ui_Selectbtn8);
    lv_obj_set_width(ui_Selectbtn8text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn8text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn8text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn8text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn8text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn8del = lv_btn_create(ui_Selectbtn8);
    lv_obj_set_width(ui_Selectbtn8del, 45);
    lv_obj_set_height(ui_Selectbtn8del, 40);
    lv_obj_set_align(ui_Selectbtn8del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn8del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn8del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn8del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn8del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn8del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn8del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn8del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn8edit = lv_btn_create(ui_Selectbtn8);
    lv_obj_set_width(ui_Selectbtn8edit, 45);
    lv_obj_set_height(ui_Selectbtn8edit, 40);
    lv_obj_set_x(ui_Selectbtn8edit, -60);
    lv_obj_set_y(ui_Selectbtn8edit, 0);
    lv_obj_set_align(ui_Selectbtn8edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn8edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn8edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn8edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn8edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn8edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn8edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn8edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn9 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn9, 280);
    lv_obj_set_height(ui_Selectbtn9, 60);
    lv_obj_set_align(ui_Selectbtn9, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn9, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn9, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn9, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn9text = lv_label_create(ui_Selectbtn9);
    lv_obj_set_width(ui_Selectbtn9text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn9text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn9text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn9text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn9text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn9del = lv_btn_create(ui_Selectbtn9);
    lv_obj_set_width(ui_Selectbtn9del, 45);
    lv_obj_set_height(ui_Selectbtn9del, 40);
    lv_obj_set_align(ui_Selectbtn9del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn9del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn9del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn9del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn9del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn9del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn9del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn9del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn9edit = lv_btn_create(ui_Selectbtn9);
    lv_obj_set_width(ui_Selectbtn9edit, 45);
    lv_obj_set_height(ui_Selectbtn9edit, 40);
    lv_obj_set_x(ui_Selectbtn9edit, -60);
    lv_obj_set_y(ui_Selectbtn9edit, 0);
    lv_obj_set_align(ui_Selectbtn9edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn9edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn9edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn9edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn9edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn9edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn9edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn9edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn10 = lv_btn_create(ui_SelectPanel);
    lv_obj_set_width(ui_Selectbtn10, 280);
    lv_obj_set_height(ui_Selectbtn10, 60);
    lv_obj_set_align(ui_Selectbtn10, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Selectbtn10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Selectbtn10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Selectbtn10, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Selectbtn10, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Selectbtn10, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Selectbtn10, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn10text = lv_label_create(ui_Selectbtn10);
    lv_obj_set_width(ui_Selectbtn10text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Selectbtn10text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Selectbtn10text, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Selectbtn10text, "00 : 00");
    lv_obj_set_style_text_font(ui_Selectbtn10text, &ui_font_semibold36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn10del = lv_btn_create(ui_Selectbtn10);
    lv_obj_set_width(ui_Selectbtn10del, 45);
    lv_obj_set_height(ui_Selectbtn10del, 40);
    lv_obj_set_align(ui_Selectbtn10del, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn10del, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn10del, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn10del, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn10del, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn10del, &ui_img_tomato_close_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn10del, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn10del, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Selectbtn10edit = lv_btn_create(ui_Selectbtn10);
    lv_obj_set_width(ui_Selectbtn10edit, 45);
    lv_obj_set_height(ui_Selectbtn10edit, 40);
    lv_obj_set_x(ui_Selectbtn10edit, -60);
    lv_obj_set_y(ui_Selectbtn10edit, 0);
    lv_obj_set_align(ui_Selectbtn10edit, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Selectbtn10edit, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Selectbtn10edit, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Selectbtn10edit, lv_color_hex(0xF37C25), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Selectbtn10edit, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Selectbtn10edit, &ui_img_tomato_reset_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Selectbtn10edit, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Selectbtn10edit, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Selectbtn1, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn2, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn3, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn4, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn5, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn6, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn7, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn8, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn9, ui_event_Select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn10, ui_event_Select, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_Selectbtn1del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn2del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn3del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn4del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn5del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn6del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn7del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn8del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn9del, ui_event_SelectDel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn10del, ui_event_SelectDel, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_Selectbtn1edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL); 
    lv_obj_add_event_cb(ui_Selectbtn2edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn3edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn4edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn5edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn6edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn7edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn8edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn9edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Selectbtn10edit, ui_event_SelectEdit, LV_EVENT_ALL, NULL);
}