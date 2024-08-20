#include "view.h"
#include "view_pages.h"
#include "ui/ui_helpers.h"


#include "ui_manager/pm.h"
#include "ui_manager/animation.h"
#include "ui_manager/event.h"
#include "data_defs.h"

#include <stdio.h>
#include <stdarg.h>

static const char *TAG = "view";

void ESP_LOGI(const char *tag, const char *fmt, ...)
{
    printf("%s: ", tag);

    // 处理可变参数
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}

void esp_event_post_to(int base, int32_t id, void* event_data, size_t event_data_size)
{
    if(base == VIEW_EVENT_BASE){
        switch (id)
        {
            case VIEW_EVENT_TIME:{
                ESP_LOGI(TAG, "VIEW_EVENT_TIME");
                struct tm *timeinfo = (struct tm *)event_data;
                char time_buff1[16];
                char time_buff2[16];
                lv_snprintf(time_buff1, sizeof(time_buff1), "%02d",timeinfo->tm_hour);
                lv_snprintf(time_buff2, sizeof(time_buff2), "%02d",timeinfo->tm_min);
                lv_label_set_text(ui_desktophour, time_buff1);
                lv_label_set_text(ui_desktopmin1, time_buff2);

                break;
            }
            case VIEW_EVENT_BATTERY:{
                ESP_LOGI(TAG, "VIEW_EVENT_BATTERY");
                uint8_t battery_st = *(uint8_t *)event_data;
                // struct view_data_device_status * bat_st = (struct view_data_device_status *)event_data;
                // ESP_LOGI(TAG, "battery_percentage: %d", bat_st->battery_per);
                static char load_per[5];
                sprintf(load_per, "%d", battery_st);
                lv_label_set_text(ui_BatteryPer2, load_per);
                lv_bar_set_value(ui_BatteryBar, battery_st, LV_ANIM_ON);

                break;
            }

            default:
                break;
        }
    }
}

int view_init(void)
{
    ui_init();
    lv_pm_init();
    view_pages_init();

    // esp_event_post_to(app_event_loop_handle, VIEW_EVENT_BASE, VIEW_EVENT_SCREEN_START, NULL, 0, pdMS_TO_TICKS(10000));
                    

    return 0;
}

// void view_render_black(void)
// {
//     lvgl_port_lock(0);
//     view_image_black_flush();
//     lvgl_port_unlock();
// }
