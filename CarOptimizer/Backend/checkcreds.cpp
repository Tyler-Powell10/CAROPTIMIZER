//! theres no need for this, thats what login is for
#include "CheckCredentials.h"

CheckCredentials::CheckCredentials(const std::string& validUsername, const std::string& validPassword)
    : validUsername(validUsername), validPassword(validPassword) {}

bool CheckCredentials::checkCredentials(const std::string& username, const std::string& password) 
{
    return (username == validUsername) && (password == validPassword);
}
