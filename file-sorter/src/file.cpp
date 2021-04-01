#include "pch.h"
#include "file.h"
namespace file_sorter {
	file::file(const std::string& path) {
		this->m_in = std::ifstream(path, std::ios::binary);
		this->m_path = path;
	}
	void* file::read(size_t& size) {
		this->m_in.seekg(0, this->m_in.end);
		size = this->m_in.tellg();
		this->m_in.seekg(0, this->m_in.beg);
		void* buffer = malloc(size);
		assert(buffer);
		this->m_in.read((char*)buffer, size);
		return buffer;
	}
	std::string file::get_path() {
		return this->m_path;
	}
	file::~file() {
		this->m_in.close();
	}
}