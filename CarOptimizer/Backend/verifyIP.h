#ifndef IP_VERIFICATION_H
#define IP_VERIFICATION_H

#include <string>
using namespace std;

class IPVerification 
{
public:
    static bool isValidIPv4(const string& ipAddress);
};

#endif // IP_VERIFICATION_H
