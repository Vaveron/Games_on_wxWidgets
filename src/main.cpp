#include "common.h" // <--- Теперь здесь есть все определения

bool MyApp::OnInit() {
    mainframe = new MainFrame("Games");
    mainframe->Show(true);
    
    ticframe = new tictoetac("Tic toe tac");
    ticframe->Show(false);
    
    snakeframe = new snake("snake");
    snakeframe->Show(false);
    
    return true;
}

void MyApp::OnFatalException() {
    wxMessageBox("Error", "Error", wxOK | wxICON_ERROR);
}

wxIMPLEMENT_APP(MyApp);