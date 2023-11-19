#include "BruteForceMitigation.h"
#include <ctime>
#include <unistd.h>

BruteForceMitigation::BruteForceMitigation(int maxAttempts, int lockoutDuration)
    : maxAttempts_(maxAttempts),
      lockoutDuration_(lockoutDuration),
      failedAttempts_(0),
      lockedOut_(false),
      lockoutStartTime_(0) {}

bool BruteForceMitigation::login(const string& username, const string& password) 
{
    if (isLockedOut()) 
    {
        cout << "Account is locked out. Please try again later.\n";
        return false;
    }

    //hardcoded for now, authentication code 
    string correctUsername = "admin";
    string correctPassword = "password123";

    if (username == correctUsername && password == correctPassword) 
    {
        cout << "Login successful!\n";
        resetAttempts();
        return true;
    } 
    else 
    {
        cout << "Login failed. Please try again.\n";
        failedAttempts_++;

        if (failedAttempts_ >= maxAttempts_) 
        {
            cout << "Too many failed attempts. Account locked out for " << lockoutDuration_
                      << " seconds.\n";
            lockedOut_ = true;
            lockoutStartTime_ = time(nullptr);
        }

        return false;
    }
}

bool BruteForceMitigation::isLockedOut() const 
{
    if (lockedOut_) 
    {
        time_t currentTime = time(nullptr);
        if (currentTime - lockoutStartTime_ >= lockoutDuration_) 
        {
            lockedOut_ = false;
            resetAttempts();
        }
    }

    return lockedOut_;
}

void BruteForceMitigation::resetAttempts() 
{
    failedAttempts_ = 0;
    lockedOut_ = false;
    lockoutStartTime_ = 0;
}
