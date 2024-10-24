#ifndef MY_FRAME_HPP
#define MY_FRAME_HPP

#include <wx/wx.h>
#include "LicenseModel.hpp"

class MyFrame : public wxFrame {
public:
    MyFrame();
    
private:
    void OnSubmit(wxCommandEvent& event);
    
    LicenseModel* model;
};

#endif // MY_FRAME_HPP
