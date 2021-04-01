#include "pch.h"
#include "group.h"
#include <zip.h>
namespace file_sorter {
	void group::add_file(const std::string& path) {
		this->m_files.push_back(std::shared_ptr<file>(new file(path)));
	}
	void group::serialize(const std::string& path) {
		zip_t* zip = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
		for (auto& f : this->m_files) {
			std::string path = f->get_path();
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
			zip_entry_open(zip, local_name.c_str());
			size_t buffer_size;
			void* buffer = f->read(buffer_size);
			zip_entry_write(zip, buffer, buffer_size);
			free(buffer);
			zip_entry_close(zip);
		}
		zip_close(zip);
	}
}