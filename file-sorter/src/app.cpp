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
		constexpr size_t input_width = 300;
		platform::control_data input_data;
		input_data.type = platform::control_type::text_input;
		input_data.x = 0;
		input_data.y = 0;
		input_data.width = input_width;
		input_data.height = 25;
		this->m_path_input = platform::new_control(this->m_window, &input_data);
		platform::button_data btn_data;
		btn_data.type = platform::control_type::button;
		btn_data.x = input_width;
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
	static std::vector<std::string> get_entries(const std::string& directory) {
		std::vector<std::string> filenames;
		for (const auto& n : fs::directory_iterator(directory)) {
			std::string path = n.path().string();
			// might add more to this later, idk
			filenames.push_back(path);
		}
		return filenames;
	}
	static std::string parse_filepath(const std::string& path) {
		size_t pos = path.find_last_of('/');
#ifdef SYSTEM_WINDOWS
		if (pos == std::string::npos) {
			pos = path.find_last_of('\\');
		}
#endif
		std::string local_name;
		if (pos == std::string::npos) {
			local_name = path;
		}
		else {
			local_name = path.substr(pos + 1);
		}
		pos = local_name.find_last_of('.');
		if (pos == std::string::npos) {
			return local_name;
		}
		else {
			return local_name.substr(0, pos);
		}
	}
	void app::sort() {
		std::string directory = platform::get_control_text(this->m_path_input);
		bool trailing_slash = (directory[directory.length() - 1] == '/');
#ifdef SYSTEM_WINDOWS
		if (!trailing_slash) {
			trailing_slash = (directory[directory.length() - 1] == '\\');
		}
#endif
		std::string final_directory = (trailing_slash ? directory : (directory + '/'));
		std::vector<std::string> entries = get_entries(final_directory);
		std::map<std::string, std::shared_ptr<group>> groups;
		for (const auto& filepath : entries) {
			std::string parsed_name = parse_filepath(filepath);
			if (groups.find(parsed_name) == groups.end()) {
				groups[parsed_name] = std::shared_ptr<group>(new group);
			}
			groups[parsed_name]->add_file(filepath);
		}
		for (auto& g : groups) {
			g.second->serialize(final_directory + g.first + ".zip");
		}
	}
}