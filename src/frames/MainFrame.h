#include <wx/wx.h>
#include <iostream>
class MainFrame : public wxFrame{
    public:
        enum IDs{
            button1_id = 2,
            button2_id = 3,
            button3_id = 4,
            button4_id = 5,
            button5_id = 6,
            button6_id = 7,
            button7_id = 8,
            button8_id = 9,
            button9_id = 10,
            text_id = 11
        };
        MainFrame(const wxString& title);
        wxString text[9];
        wxButton* buttons[9];

        char step = 'a';
        void button_event(wxCommandEvent& event);
        void check();
};