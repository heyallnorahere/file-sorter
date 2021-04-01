#include "pch.h"
#ifdef SYSTEM_WINDOWS
#include <Windows.h>
#define MAIN WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR cmdline, int showcmd)
#endif
#include "window.h"
#include "control.h"
using namespace file_sorter;
platform::window_t window;
int MAIN{
	platform::init_window();
	window = platform::create_window("File sorter", 800, 600);
	platform::button_data data;
	data.type = platform::control_type::button;
	data.x = 0;
	data.y = 0;
	data.width = 100;
	data.height = 50;
	data.text = "test";
	data.callback = [](platform::window_t window, platform::control_t control) {
		// not platform independent yet...
		MessageBoxA(NULL, "hello!", NULL, MB_OK);
	};
	platform::control_t ctrl = platform::new_control(window, &data);
	int return_code = platform::loop();
	platform::destroy_control(ctrl);
	platform::destroy_window(window);
	return return_code;
}