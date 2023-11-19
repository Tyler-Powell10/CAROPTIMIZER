//! theres no need for this, thats what login is for
#ifndef CheckCredentials_H
#define CheckCredentials_H

#include <string>
using namespace std;

class CheckCredentials {
public:
    CheckCredentials(const string& validUsername, const string& validPassword);
    bool checkCredentials(const string& username, const string& password);

private:
    string validUsername;
    string validPassword;
};

#endif // CheckCredentials_H
