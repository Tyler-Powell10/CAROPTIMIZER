//! this needs to only pull what it needs from the db rather than the 
//! hashed password but its fine for now 

#ifndef GET_INFO_FROM_DB_H
#define GET_INFO_FROM_DB_H

#include <mysqlx/xdevapi.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;
using namespace mysqlx;

class UserInfoFetcher {
private:
    Session& dbSession;

public:
    UserInfoFetcher(Session& session) : dbSession(session) {
        try {
            dbSession.sql("USE caroptimizerschema").execute();
        }
        catch (const mysqlx::Error &err) {
            cerr << "Error setting database schema in getInfo: " << err.what() << endl;
        }
    }

    json getUserInfoByEmail(const std::string& email) {
        json userInfo;
        try {
            mysqlx::RowResult result = dbSession.sql("SELECT * FROM users WHERE username = ?")
                                                .bind(email)
                                                .execute();

            
            //? list column names
            std::vector<std::string> columnNames = {"id", "username", "password_hash", "name_user", "level_of_access", "actor_type", "description"};
            
            for (mysqlx::Row row : result) {
                for (size_t i = 0; i < columnNames.size(); ++i) {
                    if (!row[i].isNull()) {
                        switch (row[i].getType()) {
                            case mysqlx::Value::Type::STRING:
                                userInfo[columnNames[i]] = row[i].get<std::string>();
                                break;
                            case mysqlx::Value::Type::INT64:
                                userInfo[columnNames[i]] = row[i].get<int64_t>();
                                break;
                            default:                            
                                break;
                        }
                    } else {
                        userInfo[columnNames[i]] = nullptr;
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in getUserInfoByEmail: " << e.what() << std::endl;
        }
        return userInfo;
    }
};
#endif // GET_INFO_FROM_DB_H
