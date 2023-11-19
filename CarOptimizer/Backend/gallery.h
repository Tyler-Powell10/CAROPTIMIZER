#include <mysqlx/xdevapi.h>  // include header file.
class Gallery {
public:
    void viewGallery() {
        // C++ code to call the database Gallery Table
        mysqlx::SqlResult result = session.sql("SELECT * FROM gallery").execute();
        
        // C++ code to send the data to the frontend
    }
    void postGallery() {
        // C++ code to call the database Gallery Table
        mysqlx::SqlResult result = session.sql("INSERT INTO gallery WHERE configuration_id = 1").execute();

        // C++ code to send the data to the frontend
    }
    void deleteGallery() {
        // C++ code to call the database Gallery Table
        mysqlx::SqlResult result = session.sql("DELETE FROM gallery WHERE configuration_id = 1").execute();
        
        // C++ code to send the data to the frontend
    }
};