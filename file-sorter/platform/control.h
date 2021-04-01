#pragma once
#include "types.h"
namespace file_sorter {
	namespace platform {
		enum class control_type {
			label,
			button,
			text_input,
		};
		struct control_data {
			control_type type;
			size_t x, y, width, height;
		};
		struct label_data : public control_data {
			std::string text;
		};
		using button_callback = std::function<void(window_t, control_t)>;
		struct button_data : public control_data {
			button_callback callback;
			std::string text;
		};
		control_t new_control(window_t parent, control_data* data);
		void destroy_control(control_t control);
		std::string get_control_text(control_t control);
		void set_control_text(control_t control, const std::string& text);
	}
}