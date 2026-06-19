#include <wx/wx.h>


class MainFrame : public wxFrame{
    public:
        enum IDs{
            button_id_change_frame = 12
        };
        MainFrame(const wxString& title);
        void button_click(wxCommandEvent& event);
};