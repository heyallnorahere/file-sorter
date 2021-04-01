#pragma once
#include "types.h"
namespace file_sorter {
	namespace platform {
		void init_window();
		window_t create_window(const std::string& title, size_t width, size_t height);
		void destroy_window(window_t window);
		int loop();
	}
}