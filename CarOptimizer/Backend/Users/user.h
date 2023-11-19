class User {
public:
    void login();
    void viewProfile();
    void editProfile();
};

class RegularUser : public User {
    void login() override;
    void viewProfile() override;
    void editProfile() override;
};

class ProfessionalUser : public User {
    void login() override;
    void viewProfile() override;
    void editProfile() override;
};

class DatabaseAdmin {
public:
    void manageDatabase();

};

class SystemAdmin {
public:
    void manageUserAccess();
    void accessSystemLogs();
};