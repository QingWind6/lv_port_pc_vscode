#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>


#ifdef __cplusplus
extern "C" {
#endif

/************************************************
 * View Data Defines
*************************************************/
#define VIEW_EVENT_BASE 1
#define CTRL_EVENT_BASE 2


/**
 * To better understand the event name, every event name need a suffix "_CHANGED".
 * Mostly, when a data struct changes, there will be an event indicating that some data CHANGED,
 * the UI should render again if it's sensitive to that data.
*/
enum {

    VIEW_EVENT_SCREEN_START = 0,  // uint8_t, enum start_screen, which screen when start
    VIEW_EVENT_PNG_LOADING,

    VIEW_EVENT_INFO_OBTAIN,
    VIEW_EVENT_SCREEN_TRIGGER,
    VIEW_EVENT_BATTERY_ST,
    VIEW_EVENT_TASK_FLOW_ERROR,
    VIEW_EVENT_VI_PLAY_FINISH,

    VIEW_EVENT_ALL,
};

#ifdef __cplusplus
}
#endif
