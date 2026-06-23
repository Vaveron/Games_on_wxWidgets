#include <wx/wx.h>
#include "../common.h" 
tictoetac::tictoetac(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300,300), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER){
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxPoint positions[9] = {
        wxPoint(30, 30),   // 0
        wxPoint(105, 30),  // 1
        wxPoint(180, 30),  // 2
        wxPoint(30, 105),  // 3
        wxPoint(105, 105), // 4
        wxPoint(180, 105), // 5
        wxPoint(30, 180),  // 6
        wxPoint(105, 180), // 7
        wxPoint(180, 180)  // 8
    };
    int ids[9] = {button1_id, button2_id, button3_id, button4_id, button5_id, 
        button6_id, button7_id, button8_id, button9_id};
    wxStaticText* steptext = new wxStaticText(panel, text_id, wxString(step), wxPoint(10, 10), wxSize(15,15));
    for (int i = 0; i < 9; i++) {
        text[i] = " ";
        buttons[i] = new wxButton(panel, ids[i], text[i], positions[i], wxSize(50, 50));
        buttons[i]->Bind(wxEVT_BUTTON, &tictoetac::button_event, this);
    }
    wxButton* button_changeFrame = new wxButton(panel, button_id_changeFrame, "back", wxPoint(210,5), wxSize(75,25));
    button_changeFrame->Bind(wxEVT_BUTTON, &tictoetac::Button_back, this);
    Bind(wxEVT_CLOSE_WINDOW, &tictoetac::Onclose, this);
}
void tictoetac::button_event(wxCommandEvent& event){
    int id = event.GetId();
    if( text[(id-1000)] != "x" && text[(id-1000)] != "o" ){
        switch (step)
        {
        case 'a':
            text[(id-1000)] = "x";
            FindWindow(id)->SetLabel(text[(id-1000)]);
            step = 'b';
            break;
        case 'b':
            text[(id-1000)] = "o";
            FindWindow(id)->SetLabel(text[(id-1000)]);
            step = 'a';
            break;
        }
        FindWindow(text_id)->SetLabel(step);
        if((text[0] == "x" && text[1] == "x" && text[2] == "x") || (text[0] == "x" && text[4] == "x" && text[8] == "x") || (text[3] == "x" && text[4] == "x" && text[5] == "x") || (text[6] == "x" && text[7] == "x" && text[8] == "x") || (text[2] == "x" && text[4] == "x" && text[6] == "x") || (text[0] == "x" && text[3] == "x" && text[6] == "x") || (text[1] == "x" && text[4] == "x" && text[7] == "x") || (text[2] == "x" && text[5] == "x" && text[8] == "x")){
            wxMessageBox("Win A user");
            for(int i = 0; i < 9; i++){
                text[i] = " ";
                buttons[i]->SetLabel(text[i]);
                step = 'a';
            }
        }
        else if((text[0] == "o" && text[1] == "o" && text[2] == "o") || (text[0] == "o" && text[4] == "o" && text[8] == "o") || (text[3] == "o" && text[4] == "o" && text[5] == "o") || (text[6] == "o" && text[7] == "o" && text[8] == "o") || (text[2] == "o" && text[4] == "o" && text[6] == "o") || (text[0] == "o" && text[3] == "o" && text[6] == "o") || (text[1] == "o" && text[4] == "o" && text[7] == "o") || (text[2] == "o" && text[5] == "o" && text[8] == "o")){
            wxMessageBox("Win B user");
            for(int i = 0; i < 9; i++){
                text[i] = " ";
                buttons[i]->SetLabel(text[i]);
                step = 'a';
            }
        } 
    }
    
}




void tictoetac::Button_back(wxCommandEvent& event){
    MyApp* app = wxDynamicCast(wxTheApp, MyApp);
    if (app) {
        app->mainframe->Show(true);
        app->ticframe->Show(false);
        app->snakeframe->Show(false);
    }
}


void tictoetac::Onclose(wxCloseEvent& event){
    // Закрываем все дочерние окна
    if (wxTheApp) {
        wxTheApp->ExitMainLoop();
    }
    Destroy();  // Уничтожаем окно
}