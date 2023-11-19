//? will take in car
#include <mysqlx/xdevapi.h> 

class Parts {
public:
    void viewParts() {
        mysqlx::SqlResult result = session.sql("SELECT * FROM parts").execute();
        
        // C++ code to send the data to the frontend
    }
    void ViewRecommendedParts() {
        mysqlx::SqlResult result = session.sql("SELECT * FROM parts").execute();
        
        // C++ code to send the data to the frontend
    }
    void ViewPartsPrice() {
        mysqlx::SqlResult result = session.sql("SELECT price FROM parts WHERE part_id = 1").execute();
        
        // C++ code to send the data to the frontend
    }
    void ViewInstructions() {
        mysqlx::SqlResult result = session.sql("SELECT description FROM parts WHERE part_id = 1").execute();
        
        // C++ code to send the data to the frontend
    }
    void RateParts() {
        mysqlx::SqlResult result = session.sql("SELECT rating FROM parts WHERE part_id = 1").execute();
        
        // C++ code to send the data to the frontend
    }
    void ViewPerformanceGain() {
        // create some formula for performance gain
        
        // C++ code to send the data to the frontend
    }
};
