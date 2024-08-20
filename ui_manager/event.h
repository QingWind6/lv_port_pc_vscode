#ifndef EVENT_H
#define EVENT_H

#include "ui/ui.h"

void ui_tileview_event(lv_event_t * e);

void ui_event_Select(lv_event_t * e);
void ui_event_SelectDel(lv_event_t * e);
void ui_event_SelectEdit(lv_event_t * e);


#endif