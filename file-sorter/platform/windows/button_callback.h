#pragma once
#include "../control.h"
namespace file_sorter {
	namespace platform {
		struct callback_struct {
			button_callback callback;
			control_t control;
			window_t window;
		};
	}
}