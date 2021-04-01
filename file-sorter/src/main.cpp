#include "pch.h"
#ifdef SYSTEM_WINDOWS
#include <Windows.h>
#define MAIN WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR cmdline, int showcmd)
#endif
#include "window.h"
using namespace file_sorter;
platform::window_t window;
int MAIN{
	platform::init_window();
	window = platform::create_window("File sorter", 800, 600);
	int return_code = platform::loop();
	platform::destroy_window(window);
	return return_code;
}