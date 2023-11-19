#ifndef BRUTE_FORCE_MITIGATION_H
#define BRUTE_FORCE_MITIGATION_H

#include <iostream>
#include <string>
using namespace std;

class BruteForceMitigation {
public:
    BruteForceMitigation(int maxAttempts, int lockoutDuration);
    ~BruteForceMitigation();

    bool login(const string& username, const string& password);

private:
    int maxAttempts;
    int lockoutDuration;
    int failedAttempts;
    bool lockedOut;
    time_t lockoutStartTime;

    bool isLockedOut() const;
    void resetAttempts();
};

#endif // BRUTE_FORCE_MITIGATION_H
