#include "pch.h"
#include "file.h"
namespace file_sorter {
	file::file(const std::string& path) {
		this->m = std::fstream(path, std::ios::binary);
		this->m_path = path;
	}
	void* file::read(size_t& size) {
		this->m.seekg(0, this->m.end);
		size = this->m.tellg();
		this->m.seekg(0, this->m.beg);
		void* buffer = malloc(size);
		this->m.read((char*)buffer, size);
		return buffer;
	}
	std::string file::get_path() {
		return this->m_path;
	}
	file::~file() {
		this->m.close();
	}
}