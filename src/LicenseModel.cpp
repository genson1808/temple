#include "LicenseModel.hpp"

LicenseModel::LicenseModel(const wxString& productCode, const wxString& macAddress, const wxString& expirationDate)
    : productCode(productCode), macAddress(macAddress), expirationDate(expirationDate) {}

wxString LicenseModel::GetProductCode() const {
    return productCode;
}

wxString LicenseModel::GetMacAddress() const {
    return macAddress;
}

wxString LicenseModel::GetExpirationDate() const {
    return expirationDate;
}
