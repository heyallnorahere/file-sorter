#include "pch.h"
#include "../control.h"
#include "internal.h"
namespace file_sorter {
	namespace platform {
		std::vector<callback_struct> callbacks;
		control_t new_control(window_t parent, control_data* data) {
			control_t ctrl = new _control_t;
			switch (data->type) {
			case control_type::button:
			{
				button_data* btn_data = (button_data*)data;
				size_t index = callbacks.size();
				callback_struct cb;
				cb.callback = btn_data->callback;
				cb.control = ctrl;
				cb.window = parent;
				callbacks.push_back(cb);
				ctrl->window = CreateWindowA("Button", btn_data->text.c_str(), WS_VISIBLE | WS_CHILDWINDOW, btn_data->x, btn_data->y, btn_data->width, btn_data->height, parent->window, (HMENU)index, NULL, NULL);
			}
				break;
			case control_type::label:
			{
				label_data* lbl_data = (label_data*)data;
				ctrl->window = CreateWindowA("Static", lbl_data->text.c_str(), WS_VISIBLE | WS_CHILDWINDOW, lbl_data->x, lbl_data->y, lbl_data->width, lbl_data->height, parent->window, NULL, NULL, NULL);
			}
				break;
			}
			return ctrl;
		}
		void destroy_control(control_t control) {
			DestroyWindow(control->window);
			delete control;
		}
	}
}