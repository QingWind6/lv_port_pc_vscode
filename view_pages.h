#ifndef VIEW_PAGES_H
#define VIEW_PAGES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "ui/ui.h"

extern lv_obj_t * ui_Page_TimeSelect;
extern lv_obj_t * ui_SelectPanel;

extern lv_obj_t * ui_Selectbtn1;
extern lv_obj_t * ui_Selectbtn1text;
extern lv_obj_t * ui_Selectbtn1del;
extern lv_obj_t * ui_Selectbtn1edit;

extern lv_obj_t * ui_Selectbtn2;
extern lv_obj_t * ui_Selectbtn2text;
extern lv_obj_t * ui_Selectbtn2del;
extern lv_obj_t * ui_Selectbtn2edit;

extern lv_obj_t * ui_Selectbtn3;
extern lv_obj_t * ui_Selectbtn3text;
extern lv_obj_t * ui_Selectbtn3del;
extern lv_obj_t * ui_Selectbtn3edit;

extern lv_obj_t * ui_Selectbtn4;
extern lv_obj_t * ui_Selectbtn4text;
extern lv_obj_t * ui_Selectbtn4del;
extern lv_obj_t * ui_Selectbtn4edit;

extern lv_obj_t * ui_Selectbtn5;
extern lv_obj_t * ui_Selectbtn5text;
extern lv_obj_t * ui_Selectbtn5del;
extern lv_obj_t * ui_Selectbtn5edit;

extern lv_obj_t * ui_Selectbtn6;
extern lv_obj_t * ui_Selectbtn6text;
extern lv_obj_t * ui_Selectbtn6del;
extern lv_obj_t * ui_Selectbtn6edit;

extern lv_obj_t * ui_Selectbtn7;
extern lv_obj_t * ui_Selectbtn7text;
extern lv_obj_t * ui_Selectbtn7del;
extern lv_obj_t * ui_Selectbtn7edit;

extern lv_obj_t * ui_Selectbtn8;
extern lv_obj_t * ui_Selectbtn8text;
extern lv_obj_t * ui_Selectbtn8del;
extern lv_obj_t * ui_Selectbtn8edit;

extern lv_obj_t * ui_Selectbtn9;
extern lv_obj_t * ui_Selectbtn9text;
extern lv_obj_t * ui_Selectbtn9del;
extern lv_obj_t * ui_Selectbtn9edit;

extern lv_obj_t * ui_Selectbtn10;
extern lv_obj_t * ui_Selectbtn10text;
extern lv_obj_t * ui_Selectbtn10del;
extern lv_obj_t * ui_Selectbtn10edit;

typedef struct _objects_t {
    lv_obj_t *page_data_viewer;
    lv_obj_t *page_setting;
    lv_obj_t *page_startup;
    lv_obj_t *dataviewerback;
    lv_obj_t *view_day_select;
    lv_obj_t *view_mon_select;
    lv_obj_t *view_year_select;
    lv_obj_t *viewfocussym;
    lv_obj_t *viewfocustitle;
    lv_obj_t *viewfocusvalue;
    lv_obj_t *viewrestsym;
    lv_obj_t *viewresttitle;
    lv_obj_t *viewrestvalue;

    lv_obj_t *settingbtn1;
    lv_obj_t *settingbtn2;
    lv_obj_t *settingbtn3;
    lv_obj_t *settingbtn4;
    lv_obj_t *settingbtn5;
} objects_t;
extern objects_t objects;

void view_pages_init();

void update_pie_chart(int focus_time, int rest_time);


#ifdef __cplusplus
}
#endif


#endif