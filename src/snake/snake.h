#ifndef SNAKE_H
#define SNAKE_H

#include <wx/wx.h>

class SnakeGame;  // Forward declaration

class snake : public wxFrame {
public:
    snake(const wxString& title);
    ~snake();
    
    void Button_back(wxCommandEvent& event);
    void Onclose(wxCloseEvent& event);

private:
    SnakeGame* m_game;
    
    // ====== НОВЫЙ МЕТОД ДЛЯ ПЕРЕХВАТА КЛАВИШ ======
    void OnKeyDown(wxKeyEvent& event);
};

#endif