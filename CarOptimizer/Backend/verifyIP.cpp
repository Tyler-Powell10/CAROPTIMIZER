#include "ip_verification.h"
#include <sstream>
#include <vector>
using namespace std;

namespace {
    vector<string> split(const string& s, char delimiter) 
    {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) 
        {
            tokens.push_back(token);
        }
        return tokens;
    }
}

bool IPVerification::isValidIPv4(const string& ipAddress) 
{
    vector<string> parts = split(ipAddress, '.');

    if (parts.size() != 4) 
    {
        return false;
    }

    for (const auto& part : parts) 
    {
        try {
            int value = stoi(part);
            if (value < 0 || value > 255) 
            {
                return false;
            }
        } catch (invalid_argument&) 
        {
\            return false;
        } catch (out_of_range&) 
        {
            return false;
        }
    }

    return true;
}
