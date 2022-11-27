#include "menu.h"

ui::state state_t;
parameters init;

void ui::render() {
    static tabs tab{ main };

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (state_t.show_demo_window)
        ImGui::ShowDemoWindow(&state_t.show_demo_window);

    // 1.1 Show ImPlot Demo
    if (state_t.implot_demo)
        ImPlot::ShowDemoWindow(&state_t.implot_demo);

    //2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::SetNextWindowPos(ImVec2());
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin("##_main", nullptr, ui::window_flags); {

            ImGuiWindow* window = ImGui::GetCurrentWindow();
            ImGui::PushClipRect(ImVec2(), ImVec2(width, height / 16), false);
            window->DrawList->AddRectFilled(ImVec2(), ImVec2(width, height / 16), ImColor(56, 56, 56));
            ImGui::PopClipRect();
            ImGui::SetCursorPos(ImVec2((250 - ImGui::CalcTextSize("RK4 Method | Task 11(2)").x) / 2, height / 48));
            ImGui::Text("RK4 Method | Task 11(2)");
            window->DrawList->AddLine(ImVec2(250, height / 128), ImVec2(250, height / 128 + 30), ImColor(75, 75, 75), 1.5f);

            ImGui::SetCursorPos(ImVec2(width / 3 + 100, height / 64));
            if (ImGui::Button("main", ImVec2(100, height / 32)))
                tab = main;

            ImGui::SetCursorPos(ImVec2(width / 3 + 350, height / 64));
            if (ImGui::Button("charts", ImVec2(100, height / 32)))
                tab = plot;

            if (tab == main) {

                window->DrawList->AddLine(ImVec2(250, height / 16 + 5), ImVec2(250, height - height / 16 - 5), ImColor(75, 75, 75), 1.5f);
                window->DrawList->AddLine(ImVec2(10, height / 16 + 25), ImVec2(245, height / 16 + 25), ImColor(75, 75, 75), 1.5f);

                ImGui::SetCursorPos(ImVec2((250 - ImGui::CalcTextSize("Parameters").x) / 2, height / 16 + 25 / 4));
                ImGui::Text("Parameters");            

                // Draw all inputs
                ImGui::SetCursorPosY(0 + height / 16 + height / 6);
                ImGui::Text("Step =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("Step =").x + 12, 0 + height / 16 + height / 6));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("Step =").x - 20));
                ImGui::InputDouble("##1", &init.step);
                ImGui::PopItemWidth();

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                ImGui::Text("Epsilon =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("Epsilon =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("Epsilon =").x - 20));
                ImGui::InputDouble("##2", &init.eps);
                ImGui::PopItemWidth();

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                ImGui::Text("Lenght =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("Lenght =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("Lenght =").x - 20));
                ImGui::InputDouble("##3", &init.l);
                ImGui::PopItemWidth();

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                ImGui::Text("T minimum =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("T minimum =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("T minimum =").x - 20));
                ImGui::InputInt("##4", &init.t_min);
                ImGui::PopItemWidth();

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                ImGui::Text("T maximum =");
                ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize("T maximum =").x + 12, ImGui::GetCursorPosY() - 20));
                ImGui::PushItemWidth((250 - ImGui::CalcTextSize("T maximum =").x - 20));
                ImGui::InputInt("##5", &init.t_max);
                ImGui::PopItemWidth();

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                if (ImGui::Button("Calculate", ImVec2(235, 42))) {
                    state_t.sys.RK4();
                    state_t.calc = true;
                }

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
                if (ImGui::Button("Clear", ImVec2(235, 42))) {
                    state_t.sys.clear();
                    state_t.calc = false;
                }
                    

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
#ifdef _DEBUG
                ImGui::Checkbox("Demo Window", &state_t.show_demo_window);
                ImGui::Checkbox("Demo Plot Window", &state_t.implot_demo);
                ImGui::Checkbox("Another Window", &state_t.show_another_window);
#endif // DEBUG

                // Draw plot
                ImGui::SetCursorPos(ImVec2(255, height / 16 + 25 / 4));
                render_plot();

                // Draw table
                ImGui::SetCursorPosX(255);
                render_table();

                // Draw time spent on RK4 // add std chrono duration for RK4 method
                ImGui::SetCursorPos(ImVec2((width + 100 - ImGui::CalcTextSize("Elapsed time").x) / 2, height - 70));
                ImGui::Text("Elapsed time %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

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

    // 3. Show another simple window.
    if (state_t.show_another_window)
    {
        ImGui::Begin("Another Window", &state_t.show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            state_t.show_another_window = false;
        ImGui::End();
    }
}

void ui::render_plot() {

    //float xs1[10], ys1[10];
    //if (state_t.calc) {
    //    std::vector<double> sol = state_t.sys.get_du();
    //    std::vector<double> x = state_t.sys.get_time();
    //    std::map<double, double> m_sol = state_t.sys.get_sol();
    //    size_t i = 0;

    //    for (int i = 0; i < x.size(); ++i)
    //        xs1[i] = x[i];
    //    for (int i = 0; i < sol.size(); ++i)
    //        ys1[i] = sol[i];

    //    /*for (auto _ : m_sol) {
    //        xs1[i] = _.first;
    //        ys1[i] = _.second;
    //        ++i;
    //    }*/
    //}


    std::vector<double> sol = state_t.sys.get_du();
    std::vector<double> x = state_t.sys.get_time();

    srand(0);
    float xs2[50], ys2[50];
    for (int i = 0; i < 50; i++) {
        xs2[i] = 0.25f + 0.2f * ((float)rand() / (float)RAND_MAX);
        ys2[i] = 0.75f + 0.2f * ((float)rand() / (float)RAND_MAX);
    }

    ImPlot::StyleColorsDark();
    if (ImPlot::BeginPlot("##dduu(t)", ImVec2(width - 275, (height - height / 16) / 2))) {
        //ImPlot::PlotScatter("U''(t)", xs1, ys1, 100);
        if(state_t.calc)
         ImPlot::PlotLine("Data 1", &x[0]/*xs1*/, &sol[0]/*ys1*/, sol.size());
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
        ImPlot::PlotScatter("Data 2", xs2, ys2, 50);
        ImPlot::PopStyleVar();
        ImPlot::EndPlot();
    }
}

void ui::render_table() {
    ImVec2 outer_size = ImVec2(width - 275, (height - height / 16) / 2 - 90);

    if (ImGui::BeginTable("##table", 9, table_flags, outer_size))
    {
        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("idx", ImGuiColumnsFlags_None);
        ImGui::TableSetupColumn("x", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("step", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("v - v2", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("loc. err", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("c1", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("c2", ImGuiTableColumnFlags_None);

        ImGui::TableHeadersRow();

        ImGuiListClipper clipper;
        clipper.Begin(1000);
        while (clipper.Step())
        {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 9; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Hello %d,%d", column, row);
                }
            }
        }
        ImGui::EndTable();
    }

}