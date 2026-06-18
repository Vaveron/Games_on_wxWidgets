#include "MainFrame.h"
#include <wx/wx.h>
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(250,275), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER){
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
    wxStaticText* steptext = new wxStaticText(panel, text_id, step, wxPoint(10, 10), wxSize(15,15));
    for (int i = 0; i < 9; i++) {
        text[i] = " ";
        buttons[i] = new wxButton(panel, ids[i], text[i], positions[i], wxSize(50, 50));
        buttons[i]->Bind(wxEVT_BUTTON, MainFrame::button_event, this);
    }
}
void MainFrame::button_event(wxCommandEvent& event){
    int id = event.GetId();
    switch (step)
    {
    case 'a':
        text[(id-2)] = "x";
        FindWindow(id)->SetLabel(text[(id-2)]);
        step = 'b';
        break;
    case 'b':
        text[(id-2)] = "o";
        FindWindow(id)->SetLabel(text[(id-2)]);
        step = 'a';
        break;
    }
    FindWindow(text_id)->SetLabel(step);
    check();
}
void MainFrame::check(){
    if((text[0] == "x" && text[1] == "x" && text[2] == "x") || (text[0] == "x" && text[4] == "x" && text[8] == "x") || (text[3] == "x" && text[4] == "x" && text[5] == "x") || (text[6] == "x" && text[7] == "x" && text[8] == "x") || (text[2] == "x" && text[4] == "x" && text[6] == "x") || (text[0] == "x" && text[3] == "x" && text[6] == "x") || (text[1] == "x" && text[4] == "x" && text[7] == "x") || (text[2] == "x" && text[5] == "x" && text[8] == "x")){
        wxMessageBox("Win A user");
        for(int i = 0; i < 9; i++){
            text[i] = " ";
            FindWindow((i+2))->SetLabel(text[i]);
            step = 'a';
        }
    }
    else if((text[0] == "o" && text[1] == "o" && text[2] == "o") || (text[0] == "o" && text[4] == "o" && text[8] == "o") || (text[3] == "o" && text[4] == "o" && text[5] == "o") || (text[6] == "o" && text[7] == "o" && text[8] == "o") || (text[2] == "o" && text[4] == "o" && text[6] == "o") || (text[0] == "o" && text[3] == "o" && text[6] == "o") || (text[1] == "o" && text[4] == "o" && text[7] == "o") || (text[2] == "o" && text[5] == "o" && text[8] == "o")){
        wxMessageBox("Win B user");
        for(int i = 0; i < 9; i++){
            text[i] = " ";
            FindWindow((i+2))->SetLabel(text[i]);
            step = 'a';
        }
    }
    
}