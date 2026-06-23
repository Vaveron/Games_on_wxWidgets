#include <wx/wx.h>
#include "../common.h" 
#include "SnakeGame.h"

snake::snake(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(700,760), 
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
    
    Centre();
    
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Верхняя панель
    wxPanel* topPanel = new wxPanel(mainPanel);
    topPanel->SetBackgroundColour(wxColour(50, 50, 80));
    topPanel->SetMinSize(wxSize(-1, 50));
    
    // Создаем игровую панель
    m_game = new SnakeGame(mainPanel);
    
    // Кнопка "Назад"
    wxButton* button_back_frame = new wxButton(topPanel, wxID_ANY, 
                                               "← Назад", wxDefaultPosition, wxSize(100, 30));
    button_back_frame->Bind(wxEVT_BUTTON, &snake::Button_back, this);
    
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(button_back_frame, 0, wxALL, 10);
    topPanel->SetSizer(topSizer);
    
    mainSizer->Add(topPanel, 0, wxEXPAND);
    mainSizer->Add(m_game, 1, wxEXPAND | wxALL, 5);
    mainPanel->SetSizer(mainSizer);
    
    // ====== ВАЖНО: ПЕРЕХВАТЫВАЕМ ВСЕ КЛАВИШИ НА УРОВНЕ ФРЕЙМА ======
    Bind(wxEVT_KEY_DOWN, &snake::OnKeyDown, this);
    
    Bind(wxEVT_CLOSE_WINDOW, &snake::Onclose, this);
    
    // Активируем игру
    if (m_game) {
        m_game->SetKeyboardActive(true);
    }
}

snake::~snake() {
    // Деструктор
}

// ====== ПЕРЕХВАТ КЛАВИШ НА УРОВНЕ ФРЕЙМА ======
void snake::OnKeyDown(wxKeyEvent& event) {
    int key = event.GetKeyCode();
    
    // Отладка
    wxLogMessage("Frame получил клавишу: %d", key);
    
    // Если игра существует и видима - передаем ей событие
    if (m_game && m_game->IsShown()) {
        // Создаем копию события и отправляем игре
        wxKeyEvent evt = event;
        m_game->GetEventHandler()->ProcessEvent(evt);
    }
    
    // Всегда передаем событие дальше (для других элементов)
    event.Skip();
}

void snake::Button_back(wxCommandEvent& event) {
    MyApp* app = wxDynamicCast(wxTheApp, MyApp);
    if (app) {
        app->mainframe->Show(true);
        app->ticframe->Show(false);
        app->snakeframe->Show(false);
        app->mainframe->SetFocus();
    }
}

void snake::Onclose(wxCloseEvent& event) {
    Destroy();
}