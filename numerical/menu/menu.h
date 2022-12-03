#pragma once

#include <d3d9.h>
#include <tchar.h>
#include <Windows.h>
#pragma comment(lib, "d3d9.lib")

#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/implot.h"
//#include "../imgui/implot_internal.h"

#include "../method/method.h"

namespace ui {
	struct state {
		bool show_demo_window = false;
		bool implot_demo = false;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		bool show_plot = false;
		bool calc = false;
		DSystem sys;
	};
}

namespace ui {
	enum tabs { main, plot };
}

namespace ui {
	void render(HWND hWnd);
	void render_plot(float width, float height);
	void render_table(float width, float height);

	void show_info_ww(bool opened);
}

namespace ui {
	inline const char* window_title = "RK4";
}

namespace ui {
	inline const float width = /*1100.0f*/1680.0f;
	inline const float height = /*740.0f*/1050.0f;
	inline ImVec2 window_pos{ 0,0 };
	inline ImVec2 window_size{ width, height };
	inline DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	inline DWORD table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchSame;
}

bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);