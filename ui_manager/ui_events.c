#include "ui/ui.h"
#include "ui_manager/animation.h"
#include "ui_manager/pm.h"
#include "view.h"
#include "view_pages.h"

#include "data_defs.h"
// #include "app_time.h"
// #include "app_data.h"

#include "time.h"

extern uint32_t startup_animation_time;

const char * TAG = "ui_events";

char buf1[3];
char buf2[3];
lv_timer_t *g_timer = NULL;
static uint8_t tomato_seconds;
static uint8_t tomato_minutes;
static uint8_t _tomato_seconds;
static uint8_t _tomato_minutes;
static bool tomato_running = 0;
static uint8_t pomodoro_mode = TOMATO_NORMAL;

static struct tm set_timeinfo;

// Menu
static lv_obj_t * list1;
static lv_obj_t * add_btn;
static lv_obj_t * edit_btn;
static lv_obj_t * delete_btn;
static lv_obj_t * edit_page;
static lv_obj_t * exit_btn;

// tomato
typedef struct {
    int minutes;   // 番茄钟的分钟数
    int seconds;   // 番茄钟的秒数
} custom_pomodoro_t;

typedef struct {
    custom_pomodoro_t pomodoros[10];
} custom_pomodoro_array_t;

custom_pomodoro_array_t pomodoro_array;


void updateTimedata();

void my_timer(lv_timer_t *timer)
{
	if(pomodoro_mode == TOMATO_NORMAL)
	{
		if(_tomato_seconds == 0)
		{
			if(_tomato_minutes == 0)
			{
				lv_label_set_text(ui_TimerMin, "00");
				lv_label_set_text(ui_TimerSec, "00");
				lv_arc_set_value(ui_TimerArc, 0);
				return;
			}
			else
			{
				_tomato_minutes--;
				_tomato_seconds = 59;
			}
		}
		else
		{
			_tomato_seconds--;
		}
	}else{
		_tomato_seconds ++;
		if(_tomato_seconds == 60){
			_tomato_minutes ++;
			_tomato_seconds = 0;
		}
	}
	lv_snprintf(buf1, sizeof(buf1), "%02d", _tomato_minutes);
	lv_snprintf(buf2, sizeof(buf2), "%02d", _tomato_seconds);

	lv_label_set_text(ui_TimerMin, buf1);
	lv_label_set_text(ui_TimerSec, buf2);
	lv_arc_set_value(ui_TimerArc, _tomato_minutes * 60 + _tomato_seconds);
}

void create_timer(uint8_t timer_type)
{
	if (g_timer != NULL)
	{
		lv_timer_del(g_timer);
		g_timer = NULL;
	}
	if(timer_type)g_timer = lv_timer_create(my_timer, 1000, NULL);
}

void startup_cb(lv_event_t *e)
{
	startup_animation();

	// _ui_screen_change(&ui_Page_Desktop, LV_SCR_LOAD_ANIM_FADE_ON, 0, startup_animation_time, &ui_Page_Desktop_screen_init);
}

void homeloaded_cb(lv_event_t *e)
{
	ESP_LOGI(TAG, "homeloaded_cb");
	// lv_group_remove_all_objs(g_main);
	// lv_group_add_obj(g_main, ui_menudesktop);
	// lv_group_add_obj(g_main, ui_menutomato);
	// lv_group_add_obj(g_main, ui_menudataviewer);
	// lv_group_add_obj(g_main, ui_menusetting);
	
	pomodoro_array.pomodoros[0].minutes = 30;
	pomodoro_array.pomodoros[0].seconds = 0;

	pomodoro_array.pomodoros[1].minutes = 8;
	pomodoro_array.pomodoros[1].seconds = 24;

	pomodoro_array.pomodoros[2].minutes = 5;
	pomodoro_array.pomodoros[2].seconds = 45;

	pomodoro_array.pomodoros[3].minutes = 17;
	pomodoro_array.pomodoros[3].seconds = 9;

	pomodoro_array.pomodoros[4].minutes = 2;
	pomodoro_array.pomodoros[4].seconds = 36;

	pomodoro_array.pomodoros[5].minutes = 12;
	pomodoro_array.pomodoros[5].seconds = 58;

	pomodoro_array.pomodoros[6].minutes = 7;
	pomodoro_array.pomodoros[6].seconds = 31;

	pomodoro_array.pomodoros[7].minutes = 22;
	pomodoro_array.pomodoros[7].seconds = 48;

	pomodoro_array.pomodoros[8].minutes = 9;
	pomodoro_array.pomodoros[8].seconds = 3;

	pomodoro_array.pomodoros[9].minutes = 14;
	pomodoro_array.pomodoros[9].seconds = 27;
	// save_custom_pomodoros(&pomodoro_array);

	// load_custom_pomodoros(&pomodoro_array);

	char buf[16];

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[0].minutes, pomodoro_array.pomodoros[0].seconds);
	lv_label_set_text(ui_Selectbtn1text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[1].minutes, pomodoro_array.pomodoros[1].seconds);
	lv_label_set_text(ui_Selectbtn2text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[2].minutes, pomodoro_array.pomodoros[2].seconds);
	lv_label_set_text(ui_Selectbtn3text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[3].minutes, pomodoro_array.pomodoros[3].seconds);
	lv_label_set_text(ui_Selectbtn4text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[4].minutes, pomodoro_array.pomodoros[4].seconds);
	lv_label_set_text(ui_Selectbtn5text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[5].minutes, pomodoro_array.pomodoros[5].seconds);
	lv_label_set_text(ui_Selectbtn6text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[6].minutes, pomodoro_array.pomodoros[6].seconds);
	lv_label_set_text(ui_Selectbtn7text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[7].minutes, pomodoro_array.pomodoros[7].seconds);
	lv_label_set_text(ui_Selectbtn8text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[8].minutes, pomodoro_array.pomodoros[8].seconds);
	lv_label_set_text(ui_Selectbtn9text, buf);

	lv_snprintf(buf, sizeof(buf), " %02d : %02d", pomodoro_array.pomodoros[9].minutes, pomodoro_array.pomodoros[9].seconds);
	lv_label_set_text(ui_Selectbtn10text, buf);

}

void desktop_cb(lv_event_t * e)
{
	_ui_screen_change(&ui_Page_Home, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_Page_Home_screen_init);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_menudesktop);
	lv_group_add_obj(g_main, ui_menutomato);
	lv_group_add_obj(g_main, ui_menudataviewer);
	lv_group_add_obj(g_main, ui_menusetting);
}

void desktoploaded_cb(lv_event_t * e)
{
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_Page_Desktop);
}
/***************************************** Menu ***************************************/
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
	int index = (int)(intptr_t)lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED) {
		// LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(list1, obj));
		ESP_LOGI(TAG, "obj idx is : %d", index);
		if(obj == add_btn)
		{
			ESP_LOGI(TAG, "test");
			lv_obj_clear_flag(edit_page, LV_OBJ_FLAG_HIDDEN);
			lv_obj_move_foreground(edit_page);
		}
		if(obj == exit_btn)
		{
			lv_obj_add_flag(edit_page, LV_OBJ_FLAG_HIDDEN);
		}
    }
}

void test_example(void)
{
    lv_obj_t * list_page = lv_obj_create(ui_Page_TomatoSelect);
	lv_obj_set_size(list_page, 280, 240);
	lv_obj_center(list_page);
	lv_obj_set_scrollbar_mode(list_page, LV_SCROLLBAR_MODE_OFF);

	edit_page = lv_obj_create(list_page);
	lv_obj_set_size(edit_page, 250, 200);
	lv_obj_center(edit_page);
	lv_obj_t * edit_select = lv_obj_create(edit_page);
	lv_obj_set_size(edit_select, 250, 150);
	lv_obj_align(edit_select, LV_ALIGN_CENTER, 0, -25);
	lv_obj_set_scrollbar_mode(edit_select, LV_SCROLLBAR_MODE_OFF);

	lv_obj_add_flag(edit_page, LV_OBJ_FLAG_HIDDEN);

    list1 = lv_list_create(list_page);
    lv_obj_set_size(list1, 280, 240);
    lv_obj_align(list1, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_flex_flow(list1, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(list1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scrollbar_mode(list1, LV_SCROLLBAR_MODE_OFF);


	lv_list_add_text(list1, "倒计时");

    add_btn = lv_list_add_btn(list1, NULL, NULL);
	
	lv_obj_set_size(add_btn, 280, 50);
	lv_obj_align(add_btn, LV_ALIGN_CENTER, 0, 0);
	lv_group_add_obj(g_main, add_btn);
	lv_obj_set_flex_flow(add_btn, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(add_btn, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);;

    lv_obj_add_event_cb(add_btn, event_handler, LV_EVENT_CLICKED, NULL);

	lv_obj_t * brightness_btn_text = lv_label_create(add_btn);
	lv_obj_align(brightness_btn_text, LV_ALIGN_CENTER, 50, 0);
	lv_label_set_text(brightness_btn_text, "Brightness");

	edit_btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit");
	lv_group_add_obj(g_main, edit_btn);
    lv_obj_add_event_cb(edit_btn, event_handler, LV_EVENT_CLICKED, NULL);

	delete_btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete");
	lv_group_add_obj(g_main, delete_btn);
    lv_obj_add_event_cb(delete_btn, event_handler, LV_EVENT_CLICKED, NULL);

	exit_btn = lv_btn_create(edit_page);
    lv_obj_set_size(exit_btn, 80, 30);
    lv_obj_align(exit_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
	lv_obj_add_event_cb(exit_btn, event_handler, LV_EVENT_CLICKED, NULL);
}

void menutomato_cb(lv_event_t * e)
{
	ESP_LOGI(TAG, "menutomato_cb");
	if(tomato_running == 0)
	{
		_ui_screen_change(&ui_Page_Select, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_Page_Select_screen_init);
		lv_group_remove_all_objs(g_main);
		lv_group_add_obj(g_main, ui_Selectbackward);
		lv_group_add_obj(g_main, ui_Selectforward);
		lv_group_add_obj(g_main, ui_Selectback);
	}else{
		_ui_screen_change(&ui_Page_Counter, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_Page_Counter_screen_init);
		lv_group_remove_all_objs(g_main);
		lv_group_add_obj(g_main, ui_TimerStartStop);
		lv_group_add_obj(g_main, ui_TimerAdd);
		lv_group_add_obj(g_main, ui_TimerReset);
		lv_group_add_obj(g_main, ui_TimerBackHome);
	}
}
void menutomatof_cb(lv_event_t * e)
{
	// lv_label_set_text(ui_Menutitle, "Pomodoro");
	lv_label_set_text(ui_Menutitle, "番茄钟");
}
void menudesktop_cb(lv_event_t * e)
{
	_ui_screen_change(&ui_Page_Desktop, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_Page_Desktop_screen_init);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_Page_Desktop);
}
void menudesktopf_cb(lv_event_t * e)
{
	// lv_label_set_text(ui_Menutitle, "Desktop");
	lv_label_set_text(ui_Menutitle, "桌面");
}
void menudataviewer_cb(lv_event_t * e)
{
	ESP_LOGI(TAG, "menudataviewer_cb");

	lv_disp_load_scr(objects.page_data_viewer);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, objects.dataviewerback);
	lv_group_add_obj(g_main, objects.view_year_select);
	lv_group_add_obj(g_main, objects.view_mon_select);
	lv_group_add_obj(g_main, objects.view_day_select);
	
	
	
	update_pie_chart(150, 50);

	// set_timeinfo.tm_year = 124;
	// set_timeinfo.tm_mon = 7;
	// set_timeinfo.tm_wday = 0;
	// set_timeinfo.tm_mday = 18;
	// set_timeinfo.tm_hour = 13;
	// set_timeinfo.tm_min = 59;
	// set_timeinfo.tm_sec = 0;

	// if (app_time_set(&set_timeinfo) != ESP_OK) {
    //     ESP_LOGE("APP_MAIN", "Failed to set time");
    //     return;
    // }

	// pomodoro_array.pomodoros[0].minutes = 30;
	// pomodoro_array.pomodoros[0].seconds = 00;

	// pomodoro_array.pomodoros[2].minutes = 0;
	// pomodoro_array.pomodoros[2].seconds = 0;

	// save_custom_pomodoros(&pomodoro_array);

}
void menudataviewerf_cb(lv_event_t * e)
{
	// lv_label_set_text(ui_Menutitle, "DataViewer");
	lv_label_set_text(ui_Menutitle, "数据");
}
void menusetting_cb(lv_event_t * e)
{
	lv_group_remove_all_objs(g_main);
	lv_disp_load_scr(objects.page_setting);
	lv_group_add_obj(g_main, objects.settingbtn5);
	lv_group_add_obj(g_main, objects.settingbtn3);
	lv_group_add_obj(g_main, objects.settingbtn1);
	lv_group_add_obj(g_main, objects.settingbtn2);
	lv_group_add_obj(g_main, objects.settingbtn4);
}
void menusettingf_cb(lv_event_t * e)
{
	// lv_label_set_text(ui_Menutitle, "Setting");
	lv_label_set_text(ui_Menutitle, "设置");
}
/***************************************** Tomato ***************************************/
void tomoatoarc_cb(lv_event_t * e)
{
	ESP_LOGI(TAG, "tomoatoarc_cb");
}
void tomatobegin_cb(lv_event_t * e)
{
	ESP_LOGI(TAG, "tomatobegin_cb");
	if(!tomato_running)
	{
		tomato_running = 1;
		create_timer(1);
		lv_obj_set_style_bg_img_src(ui_TimerStartStop, &ui_img_tomato_stop_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	}else
	{
		tomato_running = 0;
		create_timer(0);
		lv_obj_set_style_bg_img_src(ui_TimerStartStop, &ui_img_tomato_begin_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	}
}
void tomatoadd_cb(lv_event_t * e)
{
	ESP_LOGI(TAG, "tomatoreset_cb");

}
void tomatoreset_cb(lv_event_t * e)
{
	ESP_LOGI("ui_event", "tomatoreset_cb");
	updateTimedata();
}
void tomatoend_cb(lv_event_t * e)
{
	ESP_LOGI("ui_event", "tomatoend_cb");
	_ui_screen_change(&ui_Page_Home, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_Page_Home_screen_init);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_menudesktop);
	lv_group_add_obj(g_main, ui_menutomato);
	lv_group_add_obj(g_main, ui_menudataviewer);
	lv_group_add_obj(g_main, ui_menusetting);
}

/***************************************** Tomato Selector ***************************************/
void Selectforward_cb(lv_event_t * e)
{
	pomodoro_mode = TOMATO_COUNT;
	tomato_minutes = 0;
	tomato_seconds = 0;
	updateTimedata();
	_ui_screen_change(&ui_Page_Counter, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_Page_Counter_screen_init);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_TimerStartStop);
	lv_obj_clear_flag(ui_TimerAdd, LV_OBJ_FLAG_HIDDEN);
	lv_group_add_obj(g_main, ui_TimerAdd);
	lv_group_add_obj(g_main, ui_TimerReset);
	lv_group_add_obj(g_main, ui_TimerBackHome);
}
void Selectbackward_cb(lv_event_t * e)
{
	pomodoro_mode = TOMATO_NORMAL;
	lv_scr_load(ui_Page_TimeSelect);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_Selectbtn1);
	lv_group_add_obj(g_main, ui_Selectbtn2);
	lv_group_add_obj(g_main, ui_Selectbtn3);
	lv_group_add_obj(g_main, ui_Selectbtn4);
	lv_group_add_obj(g_main, ui_Selectbtn5);
	lv_group_add_obj(g_main, ui_Selectbtn6);
	lv_group_add_obj(g_main, ui_Selectbtn7);
	lv_group_add_obj(g_main, ui_Selectbtn8);
	lv_group_add_obj(g_main, ui_Selectbtn9);
	lv_group_add_obj(g_main, ui_Selectbtn10);
}

void Selectback_cb(lv_event_t * e)
{
	_ui_screen_change(&ui_Page_Home, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_Page_Home_screen_init);
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_menudesktop);
	lv_group_add_obj(g_main, ui_menutomato);
	lv_group_add_obj(g_main, ui_menudataviewer);
	lv_group_add_obj(g_main, ui_menusetting);
	lv_group_focus_obj(ui_menutomato);
}
/***************************************** DataViewer ***************************************/
void dataviewer_select_event(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
	uint16_t get_day, get_mon, get_year;
	char focus_buff[5], rest_buff[5];

	if (event == LV_EVENT_CLICKED) {
		if(target == objects.dataviewerback)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
			_ui_screen_change(&ui_Page_Home, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_Page_Home_screen_init);
			lv_group_remove_all_objs(g_main);
			lv_group_add_obj(g_main, ui_menudesktop);
			lv_group_add_obj(g_main, ui_menutomato);
			lv_group_add_obj(g_main, ui_menudataviewer);
			lv_group_add_obj(g_main, ui_menusetting);
			lv_group_focus_obj(ui_menudataviewer);
		}
	}
	
    if (event == LV_EVENT_VALUE_CHANGED) {
		get_day = lv_dropdown_get_selected(objects.view_day_select);
		ESP_LOGI(TAG, "view_day_select: %d", get_day);
		get_mon = lv_dropdown_get_selected(objects.view_mon_select);
		ESP_LOGI(TAG, "view_mon_select: %d", get_mon);
		get_year = lv_dropdown_get_selected(objects.view_year_select);
		ESP_LOGI(TAG, "view_year_select: %d", get_year);
		// load_daily_pomodoro_data(get_year, get_mon, get_day, daily_pomodoro_data_t *data);
		// data.focus_duration
		sprintf(focus_buff, "%d", 100);
		// data.rest_duration
		sprintf(rest_buff, "%d", 20);
		lv_label_set_text(objects.viewfocusvalue, focus_buff);
		lv_label_set_text(objects.viewrestvalue, rest_buff);
		update_pie_chart(100, 20);
    }
}



/***************************************** Setting ***************************************/
void setting_select_event(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
	if(event == LV_EVENT_FOCUSED)
	{
		if(target == objects.settingbtn1)
		{
			ESP_LOGI(TAG, "LV_EVENT_FOCUSED");
			lv_obj_set_pos(objects.settingbtn1, -55, -60);
			lv_obj_set_pos(objects.settingbtn2, 55, -70);
			lv_obj_set_pos(objects.settingbtn3, -70, 0);
			lv_obj_set_pos(objects.settingbtn4, 70, 0);
			lv_obj_set_pos(objects.settingbtn5, 0, 95);
		}
		if(target == objects.settingbtn2)
		{
			lv_obj_set_pos(objects.settingbtn2, 55, -60);
			lv_obj_set_pos(objects.settingbtn1, -55, -70);
			lv_obj_set_pos(objects.settingbtn3, -70, 0);
			lv_obj_set_pos(objects.settingbtn4, 70, 0);
			lv_obj_set_pos(objects.settingbtn5, 0, 95);
		}
		if(target == objects.settingbtn3)
		{
			lv_obj_set_pos(objects.settingbtn3, -60, 0);
			lv_obj_set_pos(objects.settingbtn1, -55, -70);
			lv_obj_set_pos(objects.settingbtn2, 55, -70);
			lv_obj_set_pos(objects.settingbtn4, 70, 0);
			lv_obj_set_pos(objects.settingbtn5, 0, 95);
		}
		if(target == objects.settingbtn4)
		{
			lv_obj_set_pos(objects.settingbtn4, 60, 0);
			lv_obj_set_pos(objects.settingbtn1, -55, -70);
			lv_obj_set_pos(objects.settingbtn2, 55, -70);
			lv_obj_set_pos(objects.settingbtn3, -70, 0);
			lv_obj_set_pos(objects.settingbtn5, 0, 95);

		}
		if(target == objects.settingbtn5)
		{
			lv_obj_set_pos(objects.settingbtn5, 0, 85);
			lv_obj_set_pos(objects.settingbtn1, -55, -70);
			lv_obj_set_pos(objects.settingbtn2, 55, -70);
			lv_obj_set_pos(objects.settingbtn3, -70, 0);
			lv_obj_set_pos(objects.settingbtn4, 70, 0);
		}
	}

	if(event == LV_EVENT_CLICKED)
	{
		if(target == objects.settingbtn1)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
		}
		if(target == objects.settingbtn2)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
		}
		if(target == objects.settingbtn3)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
		}
		if(target == objects.settingbtn4)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
		}
		if(target == objects.settingbtn5)
		{
			ESP_LOGI(TAG, "LV_EVENT_CLICKED");
		}
	}
}


/****************************************** Time Select *******************************************/
uint8_t timeselect_edit = 0;
static lv_obj_t * TimeSelect_record = NULL;
void AddTimeSelectToGroup()
{
	lv_group_remove_all_objs(g_main);
	lv_group_add_obj(g_main, ui_Selectbtn1);
	lv_group_add_obj(g_main, ui_Selectbtn2);
	lv_group_add_obj(g_main, ui_Selectbtn3);
	lv_group_add_obj(g_main, ui_Selectbtn4);
	lv_group_add_obj(g_main, ui_Selectbtn5);
	lv_group_add_obj(g_main, ui_Selectbtn6);
	lv_group_add_obj(g_main, ui_Selectbtn7);
	lv_group_add_obj(g_main, ui_Selectbtn8);
	lv_group_add_obj(g_main, ui_Selectbtn9);
	lv_group_add_obj(g_main, ui_Selectbtn10);
}

void HideTimeSelectObj()
{
	lv_obj_add_flag(ui_Selectbtn1del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn1edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn2del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn2edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn3del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn3edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn4del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn4edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn5del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn5edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn6del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn6edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn7del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn7edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn8del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn8edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn9del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn9edit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn10del, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_Selectbtn10edit, LV_OBJ_FLAG_HIDDEN);
}

void updateTimedata()
{
	if(pomodoro_mode == TOMATO_NORMAL)
	{
		_tomato_seconds = tomato_seconds;
		_tomato_minutes = tomato_minutes;
		lv_snprintf(buf1, sizeof(buf1), "%02d", _tomato_minutes);
		lv_snprintf(buf2, sizeof(buf2), "%02d", _tomato_seconds);
		lv_label_set_text(ui_TimerMin, buf1);
		lv_label_set_text(ui_TimerSec, buf2);
		lv_arc_set_range(ui_TimerArc, 0, _tomato_minutes * 60 + _tomato_seconds);
		lv_arc_set_value(ui_TimerArc, _tomato_minutes * 60 + _tomato_seconds);
	}else{
		_tomato_seconds = 0;
		_tomato_minutes = 0;
		lv_label_set_text(ui_TimerMin, "00");
		lv_label_set_text(ui_TimerSec, "00");
		lv_arc_set_range(ui_TimerArc, 0, 60);
		lv_arc_set_value(ui_TimerArc, 0);
	}
}

void ui_event_Select(lv_event_t * e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
	if(event_code == LV_EVENT_SHORT_CLICKED)
	{
		if(target == ui_Selectbtn1)
		{
			tomato_minutes = pomodoro_array.pomodoros[0].minutes;
			tomato_seconds = pomodoro_array.pomodoros[0].seconds;
		}
		if(target == ui_Selectbtn2)
		{
			tomato_minutes = pomodoro_array.pomodoros[1].minutes;
			tomato_seconds = pomodoro_array.pomodoros[1].seconds;
		}
		if(target == ui_Selectbtn3)
		{
			tomato_minutes = pomodoro_array.pomodoros[2].minutes;
			tomato_seconds = pomodoro_array.pomodoros[2].seconds;
		}
		if(target == ui_Selectbtn4)
		{
			tomato_minutes = pomodoro_array.pomodoros[3].minutes;
			tomato_seconds = pomodoro_array.pomodoros[3].seconds;
		}
		if(target == ui_Selectbtn5)
		{
			tomato_minutes = pomodoro_array.pomodoros[4].minutes;
			tomato_seconds = pomodoro_array.pomodoros[4].seconds;
		}
		if(target == ui_Selectbtn6)
		{
			tomato_minutes = pomodoro_array.pomodoros[5].minutes;
			tomato_seconds = pomodoro_array.pomodoros[5].seconds;
		}
		if(target == ui_Selectbtn7)
		{
			tomato_minutes = pomodoro_array.pomodoros[6].minutes;
			tomato_seconds = pomodoro_array.pomodoros[6].seconds;
		}
		if(target == ui_Selectbtn8)
		{
			tomato_minutes = pomodoro_array.pomodoros[7].minutes;
			tomato_seconds = pomodoro_array.pomodoros[7].seconds;
		}
		if(target == ui_Selectbtn9)
		{
			tomato_minutes = pomodoro_array.pomodoros[8].minutes;
			tomato_seconds = pomodoro_array.pomodoros[8].seconds;
		}
		if(target == ui_Selectbtn10)
		{
			tomato_minutes = pomodoro_array.pomodoros[9].minutes;
			tomato_seconds = pomodoro_array.pomodoros[9].seconds;
		}
		updateTimedata();
		_ui_screen_change(&ui_Page_Counter, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_Page_Counter_screen_init);
		lv_group_remove_all_objs(g_main);
		lv_group_add_obj(g_main, ui_TimerStartStop);
		lv_obj_add_flag(ui_TimerAdd, LV_OBJ_FLAG_HIDDEN);
		lv_group_add_obj(g_main, ui_TimerReset);
		lv_group_add_obj(g_main, ui_TimerBackHome);
		ESP_LOGI("ui_event_Select", "LV_EVENT_SHORT_CLICKED");
	}
    if(event_code == LV_EVENT_LONG_PRESSED) {
		ESP_LOGI(TAG, "LV_EVENT_LONG_PRESSED");
		if (!timeselect_edit) {
			lv_group_remove_all_objs(g_main);
			TimeSelect_record = target;
			if (target == ui_Selectbtn1) {
				lv_obj_clear_flag(ui_Selectbtn1del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn1edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn2) {
				lv_obj_clear_flag(ui_Selectbtn2del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn2edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn3) {
				lv_obj_clear_flag(ui_Selectbtn3del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn3edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn4) {
				lv_obj_clear_flag(ui_Selectbtn4del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn4edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn5) {
				lv_obj_clear_flag(ui_Selectbtn5del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn5edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn6) {
				lv_obj_clear_flag(ui_Selectbtn6del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn6edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn7) {
				lv_obj_clear_flag(ui_Selectbtn7del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn7edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn8) {
				lv_obj_clear_flag(ui_Selectbtn8del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn8edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn9) {
				lv_obj_clear_flag(ui_Selectbtn9del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn9edit, LV_OBJ_FLAG_HIDDEN);
			} else if (target == ui_Selectbtn10) {
				lv_obj_clear_flag(ui_Selectbtn10del, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(ui_Selectbtn10edit, LV_OBJ_FLAG_HIDDEN);
			}
			timeselect_edit = 1;
			lv_group_add_obj(g_main, TimeSelect_record);
		}
    }
	if(event_code == LV_EVENT_RELEASED)
	{
		if(timeselect_edit == 1)
		{
			ESP_LOGI(TAG, "LV_EVENT_RELEASED");
			lv_group_remove_all_objs(g_main);
			if (target == ui_Selectbtn1) {
				lv_group_add_obj(g_main, ui_Selectbtn1edit);
				lv_group_add_obj(g_main, ui_Selectbtn1del);
			} else if (target == ui_Selectbtn2) {
				lv_group_add_obj(g_main, ui_Selectbtn2edit);
				lv_group_add_obj(g_main, ui_Selectbtn2del);
			} else if (target == ui_Selectbtn3) {
				lv_group_add_obj(g_main, ui_Selectbtn3edit);
				lv_group_add_obj(g_main, ui_Selectbtn3del);
			} else if (target == ui_Selectbtn4) {
				lv_group_add_obj(g_main, ui_Selectbtn4edit);
				lv_group_add_obj(g_main, ui_Selectbtn4del);
			} else if (target == ui_Selectbtn5) {
				lv_group_add_obj(g_main, ui_Selectbtn5edit);
				lv_group_add_obj(g_main, ui_Selectbtn5del);
			} else if (target == ui_Selectbtn6) {
				lv_group_add_obj(g_main, ui_Selectbtn6edit);
				lv_group_add_obj(g_main, ui_Selectbtn6del);
			} else if (target == ui_Selectbtn7) {
				lv_group_add_obj(g_main, ui_Selectbtn7edit);
				lv_group_add_obj(g_main, ui_Selectbtn7del);
			} else if (target == ui_Selectbtn8) {
				lv_group_add_obj(g_main, ui_Selectbtn8edit);
				lv_group_add_obj(g_main, ui_Selectbtn8del);
			} else if (target == ui_Selectbtn9) {
				lv_group_add_obj(g_main, ui_Selectbtn9edit);
				lv_group_add_obj(g_main, ui_Selectbtn9del);
			} else if (target == ui_Selectbtn10) {
				lv_group_add_obj(g_main, ui_Selectbtn10edit);
				lv_group_add_obj(g_main, ui_Selectbtn10del);
			}
			timeselect_edit = 2;
		}
	}
}

void ui_event_SelectEdit(lv_event_t * e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
	if(event_code == LV_EVENT_CLICKED)
	{
		if(timeselect_edit != 2)return;
		ESP_LOGI("ui_event_Select", "ui_event_SelectEdit");

	}
	if(event_code == LV_EVENT_LONG_PRESSED) {
		timeselect_edit = 0;
		AddTimeSelectToGroup();
		HideTimeSelectObj();
		lv_group_focus_obj(TimeSelect_record);
	}
}

void ui_event_SelectDel(lv_event_t * e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
	if(event_code == LV_EVENT_CLICKED)
	{
		if(timeselect_edit != 2)return;
		ESP_LOGI("ui_event_Select", "ui_event_SelectDel");
	}
	if(event_code == LV_EVENT_LONG_PRESSED) {
		timeselect_edit = 0;
		AddTimeSelectToGroup();
		HideTimeSelectObj();
		lv_group_focus_obj(TimeSelect_record);
	}
}