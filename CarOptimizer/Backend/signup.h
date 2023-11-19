#ifndef SIGNUP_H
#define SIGNUP_H

#include <iostream>
#include <mysqlx/xdevapi.h>
#include <bcrypt/BCrypt.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
using namespace std;
using namespace mysqlx;

class Signup
{
private:
    Session &dbSession; 

public:
    Signup(Session &session) : dbSession(session) {
        try {
            dbSession.sql("USE caroptimizerschema").execute();
        }
        catch (const mysqlx::Error &err) {
            cerr << "Error setting database schema in Signup: " << err.what() << endl;
        }
    }

    // method to register a new user
    bool registerUser(const std::string &username, const std::string &nameUser, const std::string &plainPassword) {
        // validate the email and password
        if (!isValidEmail(username) || !isStrongPassword(plainPassword))
        {
            return false;
        }
        // check if the email already exists
        if (emailExists(username)) {
            // email is already used
            return false;
        }

        //! hash the password
        std::string hashedPassword = BCrypt::generateHash(plainPassword);

        // store the user in the database
        try {
            dbSession.sql("INSERT INTO users (username, name_user, password_hash) VALUES (?, ?, ?)")
                .bind(username, nameUser, hashedPassword)
                .execute();
        }
        catch (const mysqlx::Error &e) {
            cerr << "Error: " << e.what() << endl;
            return false;
        }
        catch (const std::exception &ex) {
            cerr << "STD Exception: " << ex.what() << endl;
            return false;
        }

        // user was registered successfully
        return true;
    }

private:
    // method to validate email
    bool isValidEmail(const std::string &email) {
        try {
            // using literals to prevent an escape error
            return regex_match(email, regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"));
        }
        catch (const std::regex_error &e) {
            std::cerr << "Regex error: " << e.what() << std::endl;
            return false;
        }
    }

    //! check password strength
    bool isStrongPassword(const std::string &password) {
        return password.length() >= 8;
    }

    //! method to check if email already exists
    bool emailExists(const std::string &email) {
        SqlResult result = dbSession.sql("SELECT COUNT(*) FROM users WHERE username = ?")
                               .bind(email)
                               .execute();
        Row row = result.fetchOne();
        return row[0].get<int>() > 0;
    }
};

#endif // SIGNUP_H
