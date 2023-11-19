#include <mysqlx/xdevapi.h>  // include header file.
#include <iostream>         // include the input/output stream library.
#include <vector>           
#include <memory>      

using namespace std;

//! this only shows how many rows there are right now, i didnt get it to print values
void QueryTable(mysqlx::Session& session, const string& table_name) {
    try {
        cout << "Contents of table " << table_name << ":" << endl;

        // execute a query
        mysqlx::SqlResult result = session.sql("SELECT * FROM " + table_name).execute();

        // fetch rows from the result
        while (result.hasData()) {
            mysqlx::Row row = result.fetchOne();
            // this will only get the first column as an example
            cout << row[0] << endl; // Using column index 0 as an example
        }

        cout << endl;

    } catch (const mysqlx::Error& e) {
        cerr << "error while querying table " << table_name << ": " << e.what() << endl;

    } catch (exception& ex) {
        cerr << "std Exception: " << ex.what() << endl;

    } catch (const char* ex) {
        cerr << "exception: " << ex << endl;
    }
}

// Function to insert data into the "cars" table for all fields except ID
void InsertIntoCarsTable(mysqlx::Session& session, const string& make, const string& model, int year, double torque, double horsepower, double weight) {
    try {
        string insertQuery = "INSERT INTO cars (car_make, car_model, car_year, torque, horsepower, weight) VALUES ('" + make + "', '" + model + "', " + to_string(year) + ", " + to_string(torque) + ", " + to_string(horsepower) + ", " + to_string(weight) + ")";
        session.sql(insertQuery).execute();

        cout << "Data inserted successfully into the 'cars' table." << endl;
    } catch (const mysqlx::Error& e) {
        cerr << "Error while inserting data into the 'cars' table: " << e.what() << endl;
    }
}


int main() {
    try {

        // connect to db 
        //! this will be env variables eventually
        mysqlx::Session session("localhost", 33060, "root", "USERPASS");

        // set the schema
        session.sql("USE caroptimizerschema").execute();

        //! adds cars to the table 
        InsertIntoCarsTable(session, "Toyota", "Camry", 2023, 250.0, 200.0, 3000.0);


        // define the tables to querry
        //! this is for testing to ensure they all work 
        vector<string> tables = {
            "cars", "parts", "reviews"
            
        };

        // query each table 
        for (const string& table : tables) {
            QueryTable(session, table); 
        }

    } catch (const mysqlx::Error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;

    } catch (exception& ex) {
        cerr << "STD Exception: " << ex.what() << endl;
        return 1;

    } catch (const char* ex) {
        cerr << "Exception: " << ex << endl;
        return 1;
    }

    return 0;
}
