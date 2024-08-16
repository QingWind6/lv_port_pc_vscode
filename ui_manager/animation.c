#include "animation.h"
#include "ui/ui.h"
// #include "esp_log.h"
#include <inttypes.h>

static const char *TAG = "animation_event";

uint32_t startup_animation_time = NULL;

static lv_anim_timeline_t * anim_timeline = NULL;

static void anim_bar_cb(void * var, int32_t v)
{
    lv_bar_set_value(var, v, LV_ANIM_ON);
}

static void anim_fade_off_cb(void * var, int32_t v)
{
    lv_obj_set_style_text_opa(var, v, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void anim_opa_bg_cb(void * var, int32_t v)
{
    lv_obj_set_style_bg_opa(var, v, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(var, v, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void anim_opa_cb(void * var, int32_t v)
{
    lv_obj_set_style_text_opa(var, v, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void startup_animation(void)
{
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, ui_startuplogo);
    lv_anim_set_time(&a1, 2000);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in);

    lv_anim_set_exec_cb(&a1, anim_opa_cb);
    lv_anim_set_values(&a1, 0, 255);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, ui_startupline);
    lv_anim_set_time(&a2, 2000);
    lv_anim_set_early_apply(&a2, false);
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_in_out);

    lv_anim_set_exec_cb(&a2, anim_bar_cb);
    lv_anim_set_values(&a2, 0, 100);

    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, ui_startuplogo);
    lv_anim_set_time(&a3, 1000);
    lv_anim_set_early_apply(&a3, false);
    lv_anim_set_path_cb(&a3, lv_anim_path_ease_in);

    lv_anim_set_exec_cb(&a3, anim_fade_off_cb);
    lv_anim_set_values(&a3, 255, 0);

    lv_anim_t a4;
    lv_anim_init(&a4);
    lv_anim_set_var(&a4, ui_startupline);
    lv_anim_set_time(&a4, 1000);
    lv_anim_set_path_cb(&a4, lv_anim_path_ease_in_out);

    lv_anim_set_exec_cb(&a4, anim_opa_bg_cb);
    lv_anim_set_values(&a4, 255, 0);
    lv_anim_set_early_apply(&a4, false);
    anim_timeline = lv_anim_timeline_create();
    lv_anim_timeline_add(anim_timeline, 500, &a1);
    lv_anim_timeline_add(anim_timeline, 500, &a2);
    lv_anim_timeline_add(anim_timeline, 3000, &a3);
    lv_anim_timeline_add(anim_timeline, 3000, &a4);

    lv_anim_timeline_start(anim_timeline);
    startup_animation_time = lv_anim_timeline_get_playtime(anim_timeline);
}