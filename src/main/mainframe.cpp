#include <wx/wx.h>
#include "mainframe.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(250,275), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER){
    wxPanel* panel = new wxPanel(this);
    wxButton* button = new wxButton(panel, button_id_change_frame, "Tic toe tac", wxPoint(50,50), wxSize(125,75));
}
