#include "SnakeGame.h"
#include <cstdlib>
#include <ctime>

// ==================== КОНСТРУКТОР ====================
SnakeGame::SnakeGame(wxPanel* parent) 
    : wxPanel(parent, wxID_ANY), 
      m_direction(DIR_RIGHT), 
      m_nextDirection(DIR_RIGHT), 
      m_isGameOver(false),
      m_keyboardActive(false) {  // По умолчанию клавиатура НЕ активна
    
    srand(time(nullptr));
    SetBackgroundColour(wxColour(30, 30, 30));
    
    // Привязываем события
    m_timer.Bind(wxEVT_TIMER, &SnakeGame::OnTimer, this);
    m_timer.Start(100);
    
    Bind(wxEVT_PAINT, &SnakeGame::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &SnakeGame::OnKeyDown, this);
    
    // ВАЖНО: При клике на игровое поле - активируем клавиатуру
    Bind(wxEVT_LEFT_DOWN, &SnakeGame::OnMouseClick, this);
    
    // ВАЖНО: При потере фокуса - деактивируем клавиатуру
    Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event) {
        m_keyboardActive = false;
        event.Skip();
    });
    
    InitGame();
}

// ==================== ДЕСТРУКТОР ====================
SnakeGame::~SnakeGame() {
    m_timer.Stop();
}

// ==================== АКТИВАЦИЯ КЛАВИАТУРЫ ====================
void SnakeGame::SetKeyboardActive(bool active) {
    m_keyboardActive = active;
    if (active) {
        SetFocus();  // Только когда активно
    }
}

// ==================== ИНИЦИАЛИЗАЦИЯ ====================
void SnakeGame::InitGame() {
    m_snake.clear();
    
    int startX = GRID_WIDTH / 2;
    int startY = GRID_HEIGHT / 2;
    m_snake.push_back(wxPoint(startX, startY));
    m_snake.push_back(wxPoint(startX - 1, startY));
    m_snake.push_back(wxPoint(startX - 2, startY));
    
    m_direction = DIR_RIGHT;
    m_nextDirection = DIR_RIGHT;
    m_isGameOver = false;
    GenerateFood();
}

// ==================== ГЕНЕРАЦИЯ ЕДЫ ====================
void SnakeGame::GenerateFood() {
    while (true) {
        wxPoint newFood(rand() % GRID_WIDTH, rand() % GRID_HEIGHT);
        
        bool onSnake = false;
        for (const auto& segment : m_snake) {
            if (segment == newFood) {
                onSnake = true;
                break;
            }
        }
        
        if (!onSnake) {
            m_food = newFood;
            break;
        }
    }
}

// ==================== ДВИЖЕНИЕ ЗМЕЙКИ ====================
void SnakeGame::MoveSnake() {
    if (m_isGameOver) return;

    m_direction = m_nextDirection;

    wxPoint head = m_snake.front();
    switch (m_direction) {
        case DIR_UP:    head.y--; break;
        case DIR_DOWN:  head.y++; break;
        case DIR_LEFT:  head.x--; break;
        case DIR_RIGHT: head.x++; break;
        default: break;
    }

    // Столкновение со стенами
    if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT) {
        m_isGameOver = true;
        Refresh();
        return;
    }

    bool ateFood = (head == m_food);

    m_snake.push_front(head);
    if (!ateFood) {
        m_snake.pop_back();
    } else {
        GenerateFood();
    }

    // Столкновение с собой
    for (size_t i = 1; i < m_snake.size(); ++i) {
        if (m_snake[i] == head) {
            m_isGameOver = true;
            break;
        }
    }

    Refresh();
}

// ==================== ОБРАБОТКА КЛАВИШ ====================
void SnakeGame::OnKeyDown(wxKeyEvent& event) {
    // Если клавиатура не активна - игнорируем
    if (!m_keyboardActive) {
        event.Skip();  // Передаем событие дальше (для переключения окон)
        return;
    }

    if (m_isGameOver) {
        InitGame();
        Refresh();
        return;
    }

    switch (event.GetKeyCode()) {
        case WXK_CONTROL_W:    
            if (m_direction != DIR_DOWN)  m_nextDirection = DIR_UP; 
            break;
        case WXK_CONTROL_S:  
            if (m_direction != DIR_UP)    m_nextDirection = DIR_DOWN;  
            break;
        case WXK_CONTROL_A :  
            if (m_direction != DIR_RIGHT) m_nextDirection = DIR_LEFT;  
            break;
        case WXK_CONTROL_D: 
            if (m_direction != DIR_LEFT)  m_nextDirection = DIR_RIGHT; 
            break;
        default:
            event.Skip();  // Передаем другие клавиши дальше
            return;
    }
    Refresh();
}

// ==================== КЛИК МЫШИ ====================
void SnakeGame::OnMouseClick(wxMouseEvent& event) {
    // Активируем клавиатуру при клике на игровое поле
    m_keyboardActive = true;
    SetFocus();
    event.Skip();
}

// ==================== РИСОВАНИЕ ====================
void SnakeGame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    dc.Clear();

    // Сетка
    dc.SetPen(wxPen(wxColour(50, 50, 50), 1));
    for (int x = 0; x <= GRID_WIDTH; ++x) {
        dc.DrawLine(x * GRID_SIZE, 0, x * GRID_SIZE, GRID_HEIGHT * GRID_SIZE);
    }
    for (int y = 0; y <= GRID_HEIGHT; ++y) {
        dc.DrawLine(0, y * GRID_SIZE, GRID_WIDTH * GRID_SIZE, y * GRID_SIZE);
    }

    // Тело змейки
    dc.SetBrush(wxBrush(wxColour(0, 255, 0)));
    dc.SetPen(wxPen(wxColour(0, 200, 0)));
    for (const auto& segment : m_snake) {
        dc.DrawRectangle(segment.x * GRID_SIZE, segment.y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
    }

    // Голова
    if (!m_snake.empty()) {
        wxPoint head = m_snake.front();
        dc.SetBrush(wxBrush(wxColour(0, 255, 128)));
        dc.SetPen(wxPen(wxColour(0, 200, 100)));
        dc.DrawRectangle(head.x * GRID_SIZE, head.y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
    }

    // Еда
    dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
    dc.SetPen(wxPen(wxColour(200, 0, 0)));
    dc.DrawCircle(m_food.x * GRID_SIZE + GRID_SIZE/2, 
                  m_food.y * GRID_SIZE + GRID_SIZE/2, 
                  GRID_SIZE/2 - 2);

    // Game Over
    if (m_isGameOver) {
        dc.SetTextForeground(wxColour(255, 0, 0));
        dc.SetFont(wxFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        wxString msg = "GAME OVER";
        wxSize textSize = dc.GetTextExtent(msg);
        dc.DrawText(msg, 
                    (GetSize().GetWidth() - textSize.GetWidth()) / 2, 
                    (GetSize().GetHeight() - textSize.GetHeight()) / 2);
    }
    
    // Подсказка
    if (!m_keyboardActive && !m_isGameOver) {
        dc.SetTextForeground(wxColour(200, 200, 200));
        dc.SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        wxString msg = "MMM";
        wxSize textSize = dc.GetTextExtent(msg);
        dc.DrawText(msg, 
                    (GetSize().GetWidth() - textSize.GetWidth()) / 2, 
                    GetSize().GetHeight() - 40);
    }
}

// ==================== ТАЙМЕР ====================
void SnakeGame::OnTimer(wxTimerEvent& event) {
    MoveSnake();
}