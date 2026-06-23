#pragma once
#include <wx/wx.h>
#include "../common.h" 
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(250,275), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER){
    wxPanel* panel = new wxPanel(this);
    wxButton* button_tic = new wxButton(panel, button_id_change_frame_tic, "Tic toe tac", wxPoint(25,25), wxSize(75,25));
    wxButton* button_snake = new wxButton(panel, button_id_change_frame_snake, "snake", wxPoint(25,50), wxSize(75,25));
    button_tic->Bind(wxEVT_BUTTON, &MainFrame::Button_tic, this);
    button_snake->Bind(wxEVT_BUTTON, &MainFrame::Button_snake, this);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::Onclose, this);
}


void MainFrame::Button_snake(wxCommandEvent& event){
    MyApp* app = wxDynamicCast(wxTheApp, MyApp);
    if (app) {
        app->mainframe->Show(false);
        app->ticframe->Show(false);
        app->snakeframe->Show(true);
    }
}

void MainFrame::Button_tic(wxCommandEvent& event){
    MyApp* app = wxDynamicCast(wxTheApp, MyApp);
    if (app) {
        app->mainframe->Show(false);
        app->ticframe->Show(true);
        app->snakeframe->Show(false);
    }
}


void MainFrame::Onclose(wxCloseEvent& event){
    // Закрываем все дочерние окна
    if (wxTheApp) {
        wxTheApp->ExitMainLoop();
    }
    Destroy();  // Уничтожаем окно
}