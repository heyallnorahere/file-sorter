#include "pch.h"
#include <Windows.h>
#include "../window.h"
#include "../control.h"
#include "internal.h"
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace file_sorter {
	namespace platform {
		extern std::vector<callback_struct> callbacks;
		namespace windows {
			LRESULT wndproc(HWND window, uint32_t message, WPARAM wparam, LPARAM lparam) {
				switch (message) {
				case WM_DESTROY:
					PostQuitMessage(0);
					break;
				case WM_COMMAND:
				{
					if ((size_t)wparam < callbacks.size()) {
						auto cb = callbacks[(size_t)wparam];
						cb.callback(cb.window, cb.control);
					}
				}
					break;
				default:
					return DefWindowProcA(window, message, wparam, lparam);
					break;
				}
				return 0;
			}
		}
		const std::string class_name = "file_sorter_window";
		using namespace windows;
		void init_window() {
			WNDCLASSA wc;
			memset(&wc, 0, sizeof(WNDCLASSA));
			wc.lpszClassName = class_name.c_str();
			wc.style = CS_VREDRAW | CS_HREDRAW;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hInstance = (HINSTANCE)&__ImageBase;
			wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wc.lpfnWndProc = wndproc;
			assert(RegisterClassA(&wc));
		}
		window_t create_window(const std::string& title, size_t width, size_t height) {
			window_t w = new _window_t;
			w->window = CreateWindowA(class_name.c_str(), title.c_str(), WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (int)width, (int)height, NULL, NULL, NULL, NULL);
			return w;
		}
		void destroy_window(window_t window) {
			DestroyWindow(window->window);
			delete window;
		}
		int loop() {
			MSG msg;
			memset(&msg, 0, sizeof(MSG));
			while (msg.message != WM_QUIT) {
				if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			return (int)msg.wParam;
		}
	}
}