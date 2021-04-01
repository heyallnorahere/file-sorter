#include "pch.h"
#ifdef SYSTEM_WINDOWS
#include <Windows.h>
#define MAIN WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR cmdline, int showcmd)
#else
#error No other systems implemented yet!
#endif
#include "app.h"
int MAIN {
	file_sorter::app app;
	int return_code = app.loop();
	return return_code;
}