#include "pch.h"
#include "app.h"
#include "window.h"
#include "control.h"
namespace file_sorter {
	app::app() {
		platform::init_window();
		this->m_window = platform::create_window("File sorter", 800, 600);
		this->add_controls();
	}
	app::~app() {
		platform::destroy_control(this->m_path_select);
		platform::destroy_control(this->m_path_input);
		platform::destroy_control(this->m_sort_button);
		platform::destroy_window(this->m_window);
	}
	int app::loop() {
		return platform::loop();
	}
	void app::add_controls() {
		platform::control_data input_data;
		input_data.type = platform::control_type::text_input;
		input_data.x = 0;
		input_data.y = 0;
		input_data.width = 200;
		input_data.height = 25;
		this->m_path_input = platform::new_control(this->m_window, &input_data);
		platform::button_data btn_data;
		btn_data.type = platform::control_type::button;
		btn_data.x = 200;
		btn_data.y = 0;
		btn_data.width = 50;
		btn_data.height = 25;
		btn_data.text = "...";
		btn_data.callback = [this](platform::window_t window, platform::control_t control) {
			// todo: folder selection
			platform::set_control_text(this->m_path_input, "path/to/folder");
		};
		this->m_path_select = platform::new_control(this->m_window, &btn_data);
		btn_data.x = 0;
		btn_data.y = 25;
		btn_data.height = 50;
		btn_data.text = "Sort!";
		btn_data.callback = [this](platform::window_t window, platform::control_t control) {
			this->sort();
		};
		this->m_sort_button = platform::new_control(this->m_window, &btn_data);
	}
	void app::sort() {
		// todo: sort
	}
}