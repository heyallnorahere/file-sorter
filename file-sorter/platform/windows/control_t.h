#pragma once
#include <Windows.h>
namespace file_sorter {
	namespace platform {
		// must be in global platform namespace
		struct _control_t {
			HWND window;
		};
	}
}