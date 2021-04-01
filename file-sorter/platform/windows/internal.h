#pragma once
#include "../control.h"
#include <Windows.h>
#include "../types.h"
namespace file_sorter {
	namespace platform {
		struct _control_t {
			HWND window;
		};
		struct callback_struct {
			button_callback callback;
			control_t control;
			window_t window;
		};
		struct _window_t {
			HWND window;
		};
	}
}