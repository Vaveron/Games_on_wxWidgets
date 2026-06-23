#include <wx/wx.h>


class MainFrame : public wxFrame{
    public:
        enum IDs{
            button_id_change_frame_tic = 2001,
            button_id_change_frame_snake = 2002
        };
        MainFrame(const wxString& title);
        void Button_tic(wxCommandEvent& event);
        void Button_snake(wxCommandEvent& event);
        void Onclose(wxCloseEvent& event);
};