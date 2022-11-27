#pragma once

#include <d3d9.h>
#include <tchar.h>
#include <Windows.h>
#pragma comment(lib, "d3d9.lib")

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
	void render();
	void render_plot();
	void render_table();
}

namespace ui {
	// inline LPDIRECT3DDEVICE9 dev;
	inline const char* window_title = "RK4";
}

namespace ui {
	inline const float width = 1100.0f;
	inline const float height = 740.0f;
	inline ImVec2 window_pos{ 100,100 };
	inline ImVec2 window_size{ width, height };
	inline DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	inline DWORD table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchSame;
}