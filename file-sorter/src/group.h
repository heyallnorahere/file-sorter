#pragma once
#include "file.h"
namespace file_sorter {
	class group {
	public:
		void add_file(const std::string& path);
		void serialize(const std::string& path);
		std::vector<std::string> get_file_names();
	private:
		std::vector<std::shared_ptr<file>> m_files;
	};
}