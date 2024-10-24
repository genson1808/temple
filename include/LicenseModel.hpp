#ifndef LICENSE_MODEL_HPP
#define LICENSE_MODEL_HPP

#include <wx/string.h>

class LicenseModel {
public:
    LicenseModel(const wxString& productCode, const wxString& macAddress, const wxString& expirationDate);
    
    wxString GetProductCode() const;
    wxString GetMacAddress() const;
    wxString GetExpirationDate() const;

private:
    wxString productCode;
    wxString macAddress;
    wxString expirationDate;
};

#endif // LICENSE_MODEL_HPP
