#pragma once
#include <wx/wx.h>
#include "main/mainframe.h"
#include "tic/tictoetac.h"
#include "snake/snake.h"


class MyApp : public wxApp {
public:
    MainFrame* mainframe = nullptr;
    tictoetac* ticframe = nullptr;
    snake* snakeframe = nullptr;
    
    virtual bool OnInit() override;
    virtual void OnFatalException() override;
    void Button_click(wxCommandEvent& event);
};