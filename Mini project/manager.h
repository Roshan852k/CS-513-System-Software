#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <string.h>

// Function prototypes for manager actions

// Authenticates the manager by checking userID and password in the users file.
// Returns 1 if authentication is successful, 0 otherwise.
//int authenticate_manager(int connFD, int userID, const char *password);
int authenticate_manager(int connFD, int userID, const char *username, const char *password);

// Logs out the manager by setting isLoggedIn to false in the users file.
//void logout_manager(int userID);
void logout_manager(int connFD, int userID);

// Displays the manager menu and handles manager choices such as activate/deactivate customer, 
// assign loan process, review feedback, change password, and logout.
void manager_menu(int connFD, int userID);

// Handles manager login process. Prompts the manager for userID and password and validates them.
// Calls `manager_menu` on successful login.
int manager_login(int connFD);

// Changes the manager's password by updating the user record in the users file.
void change_manager_password(int connFD, int managerID);

// Activates or deactivates a customer by toggling their `isActive` status in the customers file.
//void activate_deactivate_customer(int connFD);
void activate_account(int connFD, int customerID);
void deactivate_account(int connFD, int customerID);


// Reviews customer feedback by reading feedback entries from the feedback file and displaying them.
void review_feedback(int connFD);

void assign_loan_to_employee(int connFD);
void view_unassigned_loans(int connFD);

// Employee authentication and login-related functions
int is_user_logged_in(int userID);
void add_user_to_session(int userID);
void remove_user_from_session(int userID);


#endif
