#include "view.h"

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
            case VIEW_EVENT_SCREEN_START: {

                break;
            }

            case VIEW_EVENT_PNG_LOADING:{

                break;
            }

            case VIEW_EVENT_INFO_OBTAIN:{
                ESP_LOGI(TAG, "event: VIEW_EVENT_INFO_OBTAIN");

                break;
            }

            case VIEW_EVENT_SCREEN_TRIGGER:{
                ESP_LOGI(TAG, "event: VIEW_EVENT_SCREEN_TRIGGER");
                lv_disp_trig_activity(NULL);
                break;
            }

            case VIEW_EVENT_BATTERY_ST:{
                ESP_LOGI(TAG, "event: VIEW_EVENT_BATTERY_ST");

                break;
            }

            case VIEW_EVENT_TASK_FLOW_ERROR:{
                ESP_LOGI(TAG, "event: VIEW_EVENT_TASK_FLOW_ERROR");

                break;
            }

            case VIEW_EVENT_VI_PLAY_FINISH:{
                ESP_LOGI(TAG, "event: VIEW_EVENT_VI_PLAY_FINISH");

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

    // esp_event_post_to(app_event_loop_handle, VIEW_EVENT_BASE, VIEW_EVENT_SCREEN_START, NULL, 0, pdMS_TO_TICKS(10000));
                    

    return 0;
}

// void view_render_black(void)
// {
//     lvgl_port_lock(0);
//     view_image_black_flush();
//     lvgl_port_unlock();
// }
