#pragma once
namespace file_sorter {
	class file {
	public:
		file(const std::string& path);
		void* read(size_t& size);
		std::string get_path();
		~file();
	private:
		std::string m_path;
		std::fstream m;
	};
}