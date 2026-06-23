#include <wx/wx.h>
#include <iostream>
class tictoetac : public wxFrame{
    public:
        enum IDs{
            button1_id = 1000,
            button2_id = 1001,
            button3_id = 1002,
            button4_id = 1003,
            button5_id = 1004,
            button6_id = 1005,
            button7_id = 1006,
            button8_id = 1007,
            button9_id = 1008,
            text_id = 1013,
            button_id_changeFrame = 1014,
        };
        tictoetac(const wxString& title);
        wxString text[9];
        wxButton* buttons[9];

        char step = 'a';
        void button_event(wxCommandEvent& event);
        void Button_back(wxCommandEvent& event);
        void Onclose(wxCloseEvent& event);
};