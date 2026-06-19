#include <wx/wx.h>
#include "frames/tictoetac.h"
#include "main/mainframe.h"
class MyApp : public wxApp{
    public:
        MainFrame* mainframe;
        tictoetac* ticframe;
        virtual bool OnInit() override{
            mainframe = new MainFrame("Games");
            mainframe->Show(true);
            ticframe = new tictoetac("Tic toe tac");
            ticframe->Show(false);
            wxWindow* btn = mainframe->FindWindow(MainFrame::button_id_change_frame);
            if (btn) {
                wxMessageBox("Button found!", "Debug", wxOK);
                btn->Bind(wxEVT_BUTTON, &MyApp::Button_click, this);
            } else {
                wxMessageBox("Button NOT found!", "Error", wxOK | wxICON_ERROR);
            }
            return true;
        }
        virtual void OnFatalException() override{
            wxMessageBox("Error", "Error", wxOK | wxICON_ERROR);
        }
        void Button_click(wxCommandEvent& event);
};

void MyApp::Button_click(wxCommandEvent& event){
    mainframe->Show(false);
    ticframe->Show(true);
}

wxIMPLEMENT_APP(MyApp);