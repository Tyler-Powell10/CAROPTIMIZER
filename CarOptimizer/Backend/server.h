#ifndef SERVER_H
#define SERVER_H

#include "httplib.h"
#include "signup.h"
#include <nlohmann/json.hpp>
#include <mysqlx/xdevapi.h>
#include "login.h"
#include "getInfoFromDB.h"

using json = nlohmann::json;
using namespace std;
using namespace mysqlx;

class Server
{
private:
    httplib::Server srv;
    Session dbSession;

public:
    //! put password here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! put password here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Server() : dbSession("localhost", 33060, "root", "USERPASS!") {}
    //! put password here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! put password here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    // method to start the server on a given port
    void start(uint16_t port)
    {
        const char *CORS_HEADERS = "Access-Control-Allow-Origin: *\n"
                                   "Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept, Authorization\n"
                                   "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\n";

        // request handler for pre-flight requests
        srv.Options(".*", [CORS_HEADERS](const httplib::Request &, httplib::Response &res)
                    {
            res.set_content("", "text/plain");
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept, Authorization");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS"); });

        auto set_cors_headers = [CORS_HEADERS](httplib::Response &res)
        {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept, Authorization");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        };

        // fetches cars from the db
        srv.Get("/GetCar", [CORS_HEADERS](const httplib::Request &, httplib::Response &res) {
                    //! implement get car logic here
        });

        // posts cars to the db
        srv.Post("/PostCar", [CORS_HEADERS](const httplib::Request &req, httplib::Response &res)
                 {
            // extract the body as a string
            std::string body = req.body;

            // manually escape quotes by replacing " with \"
            std::string escaped_body;
            for (char c : body) {
                if (c == '\"') {
                    escaped_body += "\\\"";
                } else {
                    escaped_body += c;
                }
            }

            // create a JSON response string
            //! this is where we will insert it into the db, right now its just printing 
            std::string response_json = "{\"message\": \"Post received: this is where the selected car will go " + escaped_body + "\"}";

            // set content type to application/json
            res.set_content(response_json, "application/json");
            res.set_header("Access-Control-Allow-Origin", "*"); 
        });

        
        srv.Post("/login", [this, CORS_HEADERS](const httplib::Request &req, httplib::Response &res) {
            try {
                auto body = json::parse(req.body);
                std::string email = body["username"];
                std::string password = body["password"];
                Login loginHandler(dbSession);

                if (loginHandler.loginUser(email, password)) {
                    //! create json webtoken here
                    res.set_content(json({{"message", "User logged in successfully"}}).dump(), "application/json");
                } else {
                    std::cerr << "Login failed for username: " << email << std::endl;
                    res.status = 401;
                    res.set_content(json({{"message", "Invalid username or password"}}).dump(), "application/json");
                }
            } catch (const json::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
                res.status = 400;
                res.set_content(json({{"message", "Invalid JSON payload"}}).dump(), "application/json");
            } catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                res.status = 500;
                res.set_content(json({{"message", "Server error"}}).dump(), "application/json");
            }
            res.set_header("Access-Control-Allow-Origin", "*"); 
        });
        

        srv.Post("/signup", [this, CORS_HEADERS](const httplib::Request &req, httplib::Response &res) {
            try {
                auto body = json::parse(req.body);
                std::string username = body["username"];  
                std::string nameUser = body["name_user"]; 
                std::string password = body["password"];

                // print the email and name 
                std::cout << "Attempting to register user with username: " << username << " and name: " << nameUser << std::endl;

                // call the signup class
                Signup signupHandler(dbSession);
                    // check that the function call is successful 
                if (signupHandler.registerUser(username, nameUser, password)) {
                    res.set_content(json({{"message", "User registered successfully"}}).dump(), "application/json");
                } else {
                    // print the failed registration
                    std::cerr << "Registration failed for username: " << username << std::endl;
                    res.status = 400;
                    res.set_content(json({{"message", "Registration failed"}}).dump(), "application/json");
                }
            } catch (const json::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
                res.status = 400;
                res.set_content(json({{"message", "Invalid JSON payload"}}).dump(), "application/json");
            } catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                res.status = 500;
                res.set_content(json({{"message", "Server error"}}).dump(), "application/json");
            }
            res.set_header("Access-Control-Allow-Origin", "*"); 
        });


        srv.Post("/getUserInfo", [this, CORS_HEADERS](const httplib::Request &req, httplib::Response &res) {
             res.set_header("Access-Control-Allow-Origin", "*");
            try {
                auto body = json::parse(req.body);
                std::string email = body["email"];
                std::cout << "Email received in /getUserInfo: " << email << std::endl;


                UserInfoFetcher fetcher(dbSession);
                json userInfo = fetcher.getUserInfoByEmail(email);

                if (!userInfo.empty()) {
                    res.set_content(userInfo.dump(), "application/json");
                } else {
                    res.status = 404;
                    res.set_content(json({{"message", "User not found"}}).dump(), "application/json");
                }

            } catch (const json::exception& e) {
                cerr << "JSON parsing error: " << e.what() << endl;
                res.status = 400;
                res.set_content(json({{"message", "Invalid JSON payload"}}).dump(), "application/json");
            } catch (const std::exception& e) {
                cerr << "Exception: " << e.what() << endl;
                res.status = 500;
                res.set_content(json({{"message", "Server error"}}).dump(), "application/json");
            }
        });


        // error handling for undefined routes
        srv.set_error_handler([CORS_HEADERS](const httplib::Request &, httplib::Response &res)
                              {
            res.status = 404;
            res.set_content("Not found!", "text/plain");
            res.set_header("Access-Control-Allow-Origin", "*"); });

        // start listening for requests on the specified port
        srv.listen("localhost", port);
    }
};

// end of the include guard
#endif
