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
				ctrl->window = CreateWindowA("Button", btn_data->text.c_str(), WS_VISIBLE | WS_CHILDWINDOW | BS_FLAT | BS_MULTILINE | BS_PUSHBUTTON, (int)btn_data->x, (int)btn_data->y, (int)btn_data->width, (int)btn_data->height, parent->window, (HMENU)index, NULL, NULL);
			}
				break;
			case control_type::label:
			{
				label_data* lbl_data = (label_data*)data;
				ctrl->window = CreateWindowA("Static", lbl_data->text.c_str(), WS_VISIBLE | WS_CHILDWINDOW, (int)lbl_data->x, (int)lbl_data->y, (int)lbl_data->width, (int)lbl_data->height, parent->window, NULL, NULL, NULL);
			}
				break;
			case control_type::text_input:
				ctrl->window = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, (int)data->x, (int)data->y, (int)data->width, (int)data->height, parent->window, NULL, NULL, NULL);
				break;
			}
			return ctrl;
		}
		void destroy_control(control_t control) {
			DestroyWindow(control->window);
			delete control;
		}
		std::string get_control_text(control_t control) {
			char buf[256];
			GetWindowTextA(control->window, buf, 256);
			return std::string(buf);
		}
		void set_control_text(control_t control, const std::string& text) {
			SetWindowTextA(control->window, text.c_str());
		}
	}
}