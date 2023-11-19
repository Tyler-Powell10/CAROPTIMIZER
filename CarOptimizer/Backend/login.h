#ifndef LOGIN_H
#define LOGIN_H

#include <mysqlx/xdevapi.h>
#include <bcrypt/BCrypt.hpp>

using namespace mysqlx;

class Login {
private:
    Session &dbSession;
public:
    Login(Session &session) : dbSession(session) {
        try {
            dbSession.sql("USE caroptimizerschema").execute();
        }
        catch (const mysqlx::Error &err) {
            cerr << "Error setting database schema in Signup: " << err.what() << endl;
        }
    }

    bool loginUser(const std::string &email, const std::string &plainPassword) {
        try {
            mysqlx::RowResult result = dbSession.sql("SELECT password_hash FROM users WHERE username = ?").bind(email).execute();
            if (result.count() == 1) {
                mysqlx::Row row = result.fetchOne();
                std::string storedHash = row[0].get<std::string>(); 
                return BCrypt::validatePassword(plainPassword, storedHash);
            }
        }
        catch (const mysqlx::Error &err) {
            std::cerr << "Login error: " << err.what() << std::endl;
        }
        catch (const std::exception &ex) {
            std::cerr << "STD Exception: " << ex.what() << std::endl;
        }
        return false;
    }
};

#endif 
