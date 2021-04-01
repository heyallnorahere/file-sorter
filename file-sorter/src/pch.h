#pragma once
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cassert>
#include <memory>
#ifdef SYSTEM_LINUX
#include <experimental/filesystem>
namespace fs = std::expiremental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif