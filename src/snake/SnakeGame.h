#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <wx/wx.h>
#include <wx/timer.h>
#include <deque>

class SnakeGame : public wxPanel {
public:
    SnakeGame(wxPanel* parent);
    ~SnakeGame();

    void SetKeyboardActive(bool active);
    
    // ====== ПУБЛИЧНЫЕ МЕТОДЫ ДЛЯ УПРАВЛЕНИЯ ======
    void ProcessDirection(int dir);
    void TogglePause();
    
    enum Direction { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

private:
    static const int GRID_SIZE = 20;
    static const int GRID_WIDTH = 30;
    static const int GRID_HEIGHT = 30;

    std::deque<wxPoint> m_snake;
    wxPoint m_food;
    Direction m_direction;
    Direction m_nextDirection;
    wxTimer m_timer;
    bool m_isGameOver;
    bool m_keyboardActive;
    int m_score;
    bool m_isPaused;

    void InitGame();
    void GenerateFood();
    void MoveSnake();
    
    void OnTimer(wxTimerEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    
    void ProcessKeyCode(int key);
};

#endif