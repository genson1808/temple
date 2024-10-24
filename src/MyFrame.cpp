#include "MyFrame.hpp"
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <vector>
#include <utility>

std::vector<std::pair<wxString, int>> expirationOptions = {
    {L"1 Year", 3},
    {L"2 Years", 20},
    {L"3 Years", 15},
    {L"4 Years", 5}
};

std::vector<std::pair<wxString, wxString>> productCodeOptions = {
    {L"Product Code A", L"product_A"},
    {L"Product Code B", L"product_B"},
    {L"Product Code C", L"product_C"}
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "License Generator", wxDefaultPosition, wxSize(400, 400)), model(nullptr) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    
    wxString productChoices[] = { "Enter product code", "Select product code" };
    wxRadioBox* productRadioBox = new wxRadioBox(panel, wxID_ANY, wxT("Product code options"), wxDefaultPosition, wxDefaultSize, WXSIZEOF(productChoices), productChoices, 1, wxRA_SPECIFY_ROWS);
    vbox->Add(productRadioBox, 0, wxALL | wxEXPAND, 10);

    wxBoxSizer* productSizer = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl* productInput = new wxTextCtrl(panel, wxID_ANY, wxT("Enter product code"), wxDefaultPosition, wxSize(350, 25));
    productSizer->Add(productInput, 1, wxALL | wxEXPAND, 5);

    wxArrayString productChoicesArray;
    for (const auto& option : productCodeOptions) {
        productChoicesArray.Add(option.first);
    }

    wxChoice* productSelectBox = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(350, 25), productChoicesArray);
    productSizer->Add(productSelectBox, 1, wxALL | wxEXPAND, 5);
    productSelectBox->Hide();

    vbox->Add(productSizer, 0, wxALL | wxEXPAND, 10);

    wxStaticText* macLabel = new wxStaticText(panel, wxID_ANY, wxT("Enter MAC Address"));
    wxTextCtrl* macInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(350, 25));
    vbox->Add(macLabel, 0, wxALL | wxEXPAND, 5);
    vbox->Add(macInput, 0, wxALL | wxEXPAND, 5);

    wxString expirationChoices[] = { "Enter expiration", "Select expiration" };
    wxRadioBox* expirationRadioBox = new wxRadioBox(panel, wxID_ANY, wxT("Expiration date options"), wxDefaultPosition, wxDefaultSize, WXSIZEOF(expirationChoices), expirationChoices, 1, wxRA_SPECIFY_ROWS);
    vbox->Add(expirationRadioBox, 0, wxALL | wxEXPAND, 10);

    wxBoxSizer* expirationSizer = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl* expirationInput = new wxTextCtrl(panel, wxID_ANY, wxT("Enter expiration"), wxDefaultPosition, wxSize(350, 25));
    expirationSizer->Add(expirationInput, 1, wxALL | wxEXPAND, 5);

    wxArrayString expirationChoicesArray;
    for (const auto& option : expirationOptions) {
        expirationChoicesArray.Add(option.first);
    }

    wxChoice* expirationSelectBox = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(350, 25), expirationChoicesArray);
    expirationSizer->Add(expirationSelectBox, 1, wxALL | wxEXPAND, 5);
    expirationSelectBox->Hide();

    vbox->Add(expirationSizer, 0, wxALL | wxEXPAND, 10);

    wxButton* submitButton = new wxButton(panel, wxID_ANY, wxT("Submit"));
    vbox->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    productRadioBox->Bind(wxEVT_RADIOBOX, [productInput, productSelectBox, productSizer, panel](wxCommandEvent& event) {
        if (event.GetSelection() == 0) {
            productInput->Show();
            productSelectBox->Hide();
        } else {
            productInput->Hide();
            productSelectBox->Show();
        }
        productSizer->Layout();
        panel->Layout();
    });

    expirationRadioBox->Bind(wxEVT_RADIOBOX, [expirationInput, expirationSelectBox, expirationSizer, panel](wxCommandEvent& event) {
        if (event.GetSelection() == 0) {
            expirationInput->Show();
            expirationSelectBox->Hide();
        } else {
            expirationInput->Hide();
            expirationSelectBox->Show();
        }
        expirationSizer->Layout();
        panel->Layout();
    });

    submitButton->Bind(wxEVT_BUTTON, [this, productInput, productSelectBox, macInput, expirationInput, expirationSelectBox](wxCommandEvent&) {
        wxString productCode;
        wxString expirationDate;

        // Get selected product code
        if (productInput->IsShown()) {
            productCode = productInput->GetValue();
        } else {
            wxString selectedProduct = productSelectBox->GetStringSelection();
            for (const auto& option : productCodeOptions) {
                if (option.first == selectedProduct) {
                    productCode = option.second;
                    break;
                }
            }
        }

        // Get selected expiration date
        if (expirationInput->IsShown()) {
            expirationDate = expirationInput->GetValue();
        } else {
            wxString selectedExpiration = expirationSelectBox->GetStringSelection();
            for (const auto& option : expirationOptions) {
                if (option.first == selectedExpiration) {
                    expirationDate = wxString::Format(wxT("%d"), option.second);
                    break;
                }
            }
        }

        wxString macAddress = macInput->GetValue();

        // Create the model with the data
        model = new LicenseModel(productCode, macAddress, expirationDate);
        wxLogMessage("Product Code: %s\nMAC Address: %s\nExpiration Date: %s", model->GetProductCode(), model->GetMacAddress(), model->GetExpirationDate());
    });

    panel->SetSizer(vbox);
}
