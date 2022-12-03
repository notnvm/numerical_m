#include "menu.h"
#include "elements.h"

#include <algorithm>

ui::state state_t;
parameters init;
extern out outers;
static int theme = 0;

void ui::show_info_ww(bool opened) {
    if (opened) {
        ImGui::SetNextWindowSize(ImVec2(525, 400));
        ImGui::Begin(u8"�������", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        {
            ImGui::SetCursorPos(ImVec2((525 - ImGui::CalcTextSize(u8"���������� ������").x) / 2, 10));
            ImGui::Text(u8"���������� ������");
            ImGui::Separator();

            int image_width = 0;
            int image_height = 0;
            PDIRECT3DTEXTURE9 texture = NULL;
            //bool ret = LoadTextureFromFile("G:\\dev\\numerical methods\\main\\numerical\\menu\\image.png", &texture, &image_width, &image_height);
            bool ret = LoadTextureFromFile("../image.png", &texture, &image_width, &image_height);
            IM_ASSERT(ret);

            ImGui::Image((void*)texture, ImVec2(image_width, image_height));
            
            ImGui::Text(
                u8"L - ����� ��������� ��������\ng - �������������� ����������\nu(x) - ����, ������������ ��������� ��������\nx - �����\n");
            ImGui::Text(
                u8"u0 - ��������� ���������� ��������\nv0 - ��������� ��������\nx0 - ��������� �����");
            ImGui::Text(
                u8"u0(0) = pi/10\nu0'(0) = 0\nL = 0.1 �\ng = 9.8 �/c^2");
        }
        ImGui::End();
    }
}

void ui::render(HWND hWnd) {
    static tabs tab{ main };

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (state_t.show_demo_window)
        ImGui::ShowDemoWindow(&state_t.show_demo_window);

    // 1.1 Show ImPlot Demo
    if (state_t.implot_demo)
        ImPlot::ShowDemoWindow(&state_t.implot_demo);

    //2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static bool info_opened = false;
        ImColor rect_light_col = ImColor(160, 206, 247);
        ImColor rect_dark_col = ImColor(56, 56, 56);

        ImGuiIO& io = ImGui::GetIO();

        float width = 0.0f, height = 0.0f;
        RECT rect;
        if (GetWindowRect(hWnd, &rect)) {
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;
        }

        static float f = 0.0f;
        static int counter = 0;

        ImGui::SetNextWindowPos(ImVec2());
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin("##_main", nullptr, ui::window_flags); {

            ImGuiWindow* window = ImGui::GetCurrentWindow();
            ImGui::PushClipRect(ImVec2(), ImVec2(width, height / 16), false);
            window->DrawList->AddRectFilled(ImVec2(), ImVec2(width, height / 16), !(theme == 0) ? rect_light_col : rect_dark_col);
            ImGui::PopClipRect();
            ImGui::SetCursorPos(ImVec2((270 - ImGui::CalcTextSize(u8"�������������� �������").x) / 2, 5));
            ImGui::Text(u8"�������������� �������");
            ImGui::SetCursorPos(ImVec2((270 - ImGui::CalcTextSize(u8"������ 11").x) / 2, ImGui::GetCursorPosY() - 2));
            ImGui::Text(u8"������ 11");
            ImGui::SetCursorPos(ImVec2((270 - ImGui::CalcTextSize(u8"������� 2").x) / 2, ImGui::GetCursorPosY() - 2));
            ImGui::Text(u8"������� 2");

            ImGui::SetCursorPos(ImVec2(280, 5));
            ImGui::Text(u8"�������� ���. �������");

            ImGui::SetCursorPos(ImVec2(265 + (ImGui::CalcTextSize(u8"�������� ���. �������").x) / 2, 22));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 255, 255, 0)));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(255, 255, 255, 0)));
            ImGui::PushFont(io.Fonts->Fonts[1]);
            if (ImGui::Button("L", ImVec2(35, 40))) info_opened = !info_opened;
            ImGui::PopFont();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();

            show_info_ww(info_opened);

#ifdef _DEBUG
            ImGui::SetCursorPos(ImVec2(550, 5));
            ImGui::Checkbox("Demo Window", &state_t.show_demo_window);
            ImGui::SetCursorPos(ImVec2(550, 35));
            ImGui::Checkbox("Demo Plot Window", &state_t.implot_demo);
#endif // DEBUG

            ImGui::SetCursorPos(ImVec2(width - 165, 5));
            ImGui::Text(u8"������� ���� ����");

            ImGui::SetCursorPos(ImVec2(width - 170, 25));
            ImGui::PushItemWidth(150);
            ImGui::Combo(u8"##������� ���� ����", &theme, u8"Ҹ����\0�������\0");
            ImGui::PopItemWidth();
            theme == 0 ? ImGui::StyleColorsDark() : ImGui::StyleColorsLight();

            window->DrawList->AddLine(ImVec2(270, 10), ImVec2(270, height / 16 - 10), ImColor(75, 75, 75), 1.5f);

#ifdef _DEBUG
            ImGui::SetCursorPos(ImVec2(270 + ((width - 270) / 2 - 200), height / 64));
            if (ImGui::Button("main", ImVec2(100, height / 32)))
                tab = main;
#endif // DEBUG

            ImGui::SetCursorPos(ImVec2(270 + ((width - 270) / 2 + 200), height / 64));
            if (ImGui::Button("charts", ImVec2(100, height / 32)))
                tab = plot;

            if (tab == main) {

                window->DrawList->AddLine(ImVec2(270, height / 16 + 5), ImVec2(270, height - height / 16 + 15), ImColor(75, 75, 75), 1.5f);
                window->DrawList->AddLine(ImVec2(10, height / 16 + 25), ImVec2(265, height / 16 + 25), ImColor(75, 75, 75), 1.5f);

                ImGui::SetCursorPos(ImVec2((270 - ImGui::CalcTextSize(u8"��������� �����").x) / 2, height / 16 + 25 / 4));
                ImGui::Text(u8"��������� �����");

                // Draw all inputs
                ImGui::SetCursorPosY(height / 16 + 40);
                ImGui::Text("h ="); 
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("h =").x + 12, 0 + height / 16 + 40));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("h =").x - 20));
                ImGui::InputDouble("##1", &init.step);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"��������� ��� ������");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text(u8"Eps =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize(u8"Eps =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize(u8"Eps =").x - 20));
                ImGui::InputDouble("##2", &init.eps);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"�������� �������� ��������� �����������");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text(u8"Eps ������� =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize(u8"Eps ������� =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize(u8"Eps ������� =").x - 20));
                ImGui::InputDouble("##3", &init.eps_br);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"�������� ������ �� ������ �������\n������������: Tmax - Eps_�������\n������������ ��� ��������� �����");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text("Nmax =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("Nmax =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("Nmax =").x - 20));
                ImGui::InputInt("##4", &init.n_max);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"������������ ����� �����\n������������ ��� ��������� �����");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text("Tmax =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("T max =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("T max =").x - 20));
                ImGui::InputInt("##5", &init.t_max);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"������ ������� �������");

                ImGui::SetCursorPos(ImVec2((250 - ImGui::CalcTextSize(u8"��������� �������").x) / 2, ImGui::GetCursorPosY() + 15));
                ImGui::Text(u8"��������� �������");
                window->DrawList->AddLine(ImVec2(10, ImGui::GetCursorPosY()), ImVec2(265, ImGui::GetCursorPosY()), ImColor(75, 75, 75), 1.5f);

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text("L =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("L =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("L =").x - 20));
                ImGui::InputDouble("##6", &init.l);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"����� ����");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text("G =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("G =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("G =").x - 20));
                ImGui::InputDouble("##7", &init.g);
                ImGui::PopItemWidth();
                ImGui::SameLine(247); hint(
                    u8"�������������� ����������");

               /* ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::Text("T minimum =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("T minimum =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("T minimum =").x - 20));
                ImGui::InputInt("##5", &init.t_min);
                ImGui::PopItemWidth();*/

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                if (ImGui::Button(u8"���������", ImVec2(255, 42))) {
                    state_t.sys.RK4();
                    state_t.calc = true;
                }

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                if (ImGui::Button(u8"��������", ImVec2(255, 42))) {
                    state_t.sys.clear();
                    state_t.calc = false;
                    outers.data.clear();
                    outers.divs_counter = 0;
                    outers.pows_counter = 0;
                }

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::TextColored(ImColor(168, 119, 9),u8"������� �� �������"); ImGui::SameLine();
                hint(u8"i - ������� ����� ����\nx - �����: x_i+1 = x_i + h_i \nh - ������� �������� ����\nv(1) - ������ ���������� ���������� �������\nv(1)_2 - ������ ���������� ���������� �������, ���������� ������� ������\nv(2) - ������ ���������� ���������� �������\nv(2)_2 - ������ ���������� ���������� �������, ���������� ������� ������\n���� - ������ ����� ��������� �����������: max(S1,S2)\n�������� - �����, � ������� ������������ � 2 ����\n������� - �����, � ������� ��� ���������� � 2 ����");
                
                if (state_t.calc) {
                    ImGui::SetCursorPos(ImVec2((270 - ImGui::CalcTextSize(u8"������� ������").x) / 2, ImGui::GetCursorPosY() + 15));
                    ImGui::Text(u8"������� ������"); ImGui::SameLine(); hint(u8"����� �����-����� ����� 4-�� �������\n�������� ��������� ����������� �������");
                    window->DrawList->AddLine(ImVec2(10, ImGui::GetCursorPosY()), ImVec2(265, ImGui::GetCursorPosY()), ImColor(75, 75, 75), 1.5f);

                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                    ImGui::Text("N: %i", state_t.sys.get_sol_x().size() - 1);
                    ImGui::SameLine(); hint(
                        u8"����� ����� ������");
                    ImGui::Text(u8"Tmax - Xn: %f��", init.t_max - std::get<1>(outers.data.back()));
                    ImGui::SameLine(); hint(
                        u8"���������� ���������� �� ������ ������� �����\n��� ������������� ��������: �� ����� �� �������\n��� ������������� ��������: ������� �� �������");
                    ImGui::Text(u8"����. ���: %f, ��� x = %.4f", outers.max_step, outers.max_step_time);
                    ImGui::Text(u8"���. ���: %f, ��� x = %.4f", outers.min_step, outers.min_step_time);
                    ImGui::Text(u8"����� ��������: %i", outers.pows_counter);
                    ImGui::Text(u8"����� �������: %i", outers.divs_counter);
                    ImGui::Text(u8"max ����: %f", outers.max_onlp); ImGui::SameLine(); hint(
                        u8"������������ ����� ��������� ����������� ( max(S1,S2) )");
                    ImGui::Text(u8"v(1) ����: %e", std::get<3>(outers.data.back())); ImGui::SameLine(); hint(
                        u8"���������� �������� ��� ������ �� �������");
                    ImGui::Text(u8"v(2) ����: %e", std::get<6>(outers.data.back())); ImGui::SameLine(); hint(
                        u8"�������� �������� ��� ������ �� �������");
                }

                // Draw plot
                ImGui::SetCursorPos(ImVec2(275, height / 16 + 25 / 4));
                render_plot(width, height);

                // Draw table
                ImGui::SetCursorPosX(275);
                render_table(width, height);

            }

            if (tab == plot) {
                ImGui::SetCursorPos(ImVec2(10, 0 + height / 16 + 10));
                ImGui::Text("graph");

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            
                ImGui::ColorEdit3("clear color", (float*)&state_t.clear_color); 

                if (ImGui::Button("Button"))                            
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);             
            }
        }
        ImGui::End();
    }
}

void ui::render_plot(float width, float height) {

    static bool line = true;
    static bool dots[3] = { false, false, false};
    static float thickness[3] = { 1,1,1 };

    static ImColor color_1 = ImColor(6, 116, 212);
    static ImColor color_2 = ImColor(212, 6, 65);
    static ImColor color_3 = ImColor(6, 212, 119); 

    std::map<double, double> sol_x = state_t.sys.get_sol_x();
    double xs1[10001]; double ys1[10001]; size_t idx = 0;
    for (auto& _ : sol_x) {
        xs1[idx] = _.first;
        ys1[idx] = _.second;
        ++idx;
    }

    std::map<double, double> sol_y = state_t.sys.get_sol_y();
    double xs2[10001]; double ys2[10001]; idx = 0;
    for (auto& _ : sol_y) {
        xs2[idx] = _.first;
        ys2[idx] = _.second;
        ++idx;
    }

    if (theme == 0)
        ImPlot::StyleColorsDark();
    if (!(theme == 0))
        ImPlot::StyleColorsLight();

    ImGui::SetCursorPos(ImVec2(275, height / 16 + 25 / 4));
    if (ImPlot::BeginPlot(u8"����������� ��������� �������� �� �������", ImVec2((width - 295) / 3, (height - height / 16) / 2))) {
        ImPlot::SetupAxes(u8"X - �����", u8"U - ���������� ��������");
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, init.t_max + 0.5);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -1, 1);

        if (state_t.calc) {
            if (line) {
                ImPlot::SetNextLineStyle(color_1, thickness[0]);
                ImPlot::PlotLine("u(x)", xs1, ys1, sol_x.size());
            }
            if (dots[0]) {
                ImPlot::SetNextMarkerStyle(color_1);
                ImPlot::PlotScatter("u(x)", xs1, ys1, sol_x.size());
            }
        }

        if (ImPlot::BeginLegendPopup("u(x)")) {
            ImGui::Separator();
            ImGui::ColorEdit3(u8"����", (float*)&color_1);
            ImGui::Checkbox(u8"�������� �����", &dots[0]);
            ImGui::SliderFloat(u8"�������", &thickness[0], 0, 3);
            ImPlot::EndLegendPopup();
        }

        ImPlot::EndPlot();
    }

    ImGui::SetCursorPos(ImVec2(275 + (width - 295) / 3 + 2, height / 16 + 25 / 4));
    if (ImPlot::BeginPlot(u8"����������� �������� �������� �� �������", ImVec2((width - 295) / 3 , (height - height / 16) / 2))) {
        ImPlot::SetupAxes(u8"X - �����", u8"U' - ��������");
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, init.t_max + 0.5);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -3.5, 3.5);

        if (state_t.calc) {
            if (line) {
                ImPlot::SetNextLineStyle(color_2, thickness[1]);
                ImPlot::PlotLine("u'(x)", xs2, ys2, sol_y.size());
            }
            if (dots[1]) {
                ImPlot::SetNextMarkerStyle(color_2);
                ImPlot::PlotScatter("u'(x)", xs2, ys2, sol_y.size());
            }
        }

        if (ImPlot::BeginLegendPopup("u'(x)")) {
            ImGui::Separator();
            ImGui::ColorEdit3(u8"����", (float*)&color_2);
            ImGui::Checkbox(u8"�������� �����", &dots[1]);
            ImGui::SliderFloat(u8"�������", &thickness[1], 0, 3);
            ImPlot::EndLegendPopup();
        }

        ImPlot::EndPlot();
    }

    ImGui::SetCursorPos(ImVec2(275 + 2 + 2 * ((width - 295) / 3) + 2, height / 16 + 25 / 4));
    if (ImPlot::BeginPlot(u8"������� �������", ImVec2((width - 295) / 3, (height - height / 16) / 2))) {
        ImPlot::SetupAxes(u8"U - ���������� ��������", u8"U' - ��������");
        ImPlot::SetupAxisLimits(ImAxis_X1, -3.5, 3.5);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -0.6, 0.6);

        if (state_t.calc) {
            if (line) {
                ImPlot::SetNextLineStyle(color_3, thickness[2]);
                ImPlot::PlotLine("u'(u)", ys2, ys1, (std::max)(sol_x.size(), sol_y.size()));
            }
            if (dots[2]) {
                ImPlot::SetNextMarkerStyle(color_3);
                ImPlot::PlotScatter("u'(u)", ys2, ys1, (std::max)(sol_x.size(), sol_y.size()));
            }
        }

        if (ImPlot::BeginLegendPopup("u'(u)")) {
            ImGui::Separator();
            ImGui::ColorEdit3(u8"����", (float*)&color_3);
            ImGui::Checkbox(u8"�������� �����", &dots[2]);
            ImGui::SliderFloat(u8"�������", &thickness[2], 0, 3);
            ImPlot::EndLegendPopup();
        }

        ImPlot::EndPlot();
    }
}

void ui::render_table(float width, float height) { // ADD: support several plots 
    ImVec2 outer_size = ImVec2(width - 295, (height - height / 16) / 2 - 55);

    static bool selected[10000] = {};
    //static bool* selected = new bool[init.n_max]{}; // should be deleted

    if (ImGui::BeginTable("##table", 12, table_flags, outer_size))
    {
        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("i", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("x", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("h", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(1)", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(1)_2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(1) - v(1)_2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(2)", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(2)_2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v(2) - v(2)_2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(u8"����", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(u8"��������", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(u8"�������", ImGuiTableColumnFlags_None);

        ImGui::TableHeadersRow();

        ImGuiListClipper clipper;
        clipper.Begin(outers.data.size());
        size_t i = 0;
        while (clipper.Step())
        {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                char buffer[100];        
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                sprintf_s(buffer, "%i", std::get<0>(outers.data[row]));
                ImGui::Selectable(buffer, &selected[row], ImGuiSelectableFlags_SpanAllColumns);
               // ImGui::Text("%i", std::get<0>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%f", std::get<1>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%f", std::get<2>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<3>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<4>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<5>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<6>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<7>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<8>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%e", std::get<9>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%i", std::get<10>(outers.data[row]));
                ImGui::TableNextColumn();
                ImGui::Text("%i", std::get<11>(outers.data[row]));
            }
        }
        ImGui::EndTable();
    }
}