#include <wx/wx.h>
#include "MyFrame.hpp"

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
