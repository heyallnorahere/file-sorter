#pragma once
#include "types.h"
#include "group.h"
namespace file_sorter {
	class app {
	public:
		app();
		~app();
		int loop();
	private:
		platform::window_t m_window;
		std::map<std::string, std::shared_ptr<group>> m_groups;
		platform::control_t m_sort_button, m_path_input, m_path_select;
		void add_controls();
		void sort();
	};
}