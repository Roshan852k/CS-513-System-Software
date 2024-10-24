#ifndef ADMIN_H
#define ADMIN_H

//#include "customer.h"  // Include customer for managing customer details

struct Admin {
    int adminID;
    char name[50];
    char pass[20];
};

// Function Prototypes
void admin_login(int connFD);
//void admin_menu(int connFD);
void admin_menu(int connFD, int userID);
// int authenticate_admin(int adminID, const char* password);
int authenticate_admin(int connFD, int userID, const char* adminID, const char* password);
//void admin_logout(int connFD);
void admin_logout(int connFD, int userID);


// Admin Functionalities
void add_new_employee(int connFD);
//void modify_customer_employee_details(int connFD);
void modify_employee_details(int connFD);
void manage_user_roles(int connFD);
void admin_change_password(int connFD);
#endif
