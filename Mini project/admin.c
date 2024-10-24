#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "admin.h"
// #include "customer.h"
#include "user.h"
#include "employee.h"
#include "account.h"

#define ADMIN_FILENAME "admin.dat"
#define EMP_FILENAME "employee.dat"  // File for employee account_info
#define CUST_FILENAME "accounts1.dat"  // File for customer account_info

/*
const char* predefined_adminID = "admin";
const char* predefined_password = "admin@123";
// Function to authenticate the admin using hardcoded credentials (adminID = 0, password = "admin1")
*/

// Funntion to get adminID
int get_adminID(const char *username, const char *password, int connFD) {
    struct Admin admin;
    FILE *file = fopen(ADMIN_FILENAME, "rb");  // Open the file in binary read mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing account data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return 0;
    }

    // Read each account from the file and compare username and password
    while (fread(&admin, sizeof(struct Admin), 1, file)) {
        if (strcmp(admin.name, username) == 0 && strcmp(admin.pass, password) == 0) {
              fclose(file);
              return admin.adminID;  // Return customerID if credentials match
        }
    }

    fclose(file);
    return -1;  // Return -1 if no match found
}

// Authenticate Admin Login System
int authenticate_admin(int connFD, int userID, const char* username, const char* password) {
    FILE *file = fopen(ADMIN_FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening admin file.\n");
        return 0;  // Authentication failed due to file access issue
    }
    
    printf("Username :%s\n",username);
    printf("Password :%s\n",password);
    
    if (is_user_logged_in(userID)) {
        write(connFD, "Error: Employee is already logged in.\n", 39);
        fclose(file);
        return 0; // User already logged in
    }

    struct Admin admin;

    // Read each admin record from the file and compare credentials
    while (fread(&admin, sizeof(struct Admin), 1, file)) {
        if (strcmp(username, admin.name) == 0 && strcmp(password, admin.pass) == 0) { 
            add_user_to_session(userID);
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0;
}

// Admin Login System
void admin_login(int connFD) {
    char buffer[1000], username[100], password[50];

    // Ask for admin ID
    strcpy(buffer, "Enter Admin ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(username, sizeof(username));
    read(connFD, username, sizeof(username));
    username[strcspn(username, "\n")] = 0; // Remove trailing newline if present

    // Ask for password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));
    password[strcspn(password, "\n")] = 0; // Remove trailing newline if present


    // Debug: Print the values to check
    printf("Username received: %s\n", username);
    printf("Password received: %s\n", password);

    // Validate admin credentials
    int adminID = get_adminID(username, password, connFD);
    if (authenticate_admin(connFD,adminID, username, password)) {
        admin_menu(connFD, adminID);
        return ;
    } else {
        strcpy(buffer, "Invalid Admin ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return ;
    }
}

// Admin Menu Function
void admin_menu(int connFD, int userID) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display the menu
        sprintf(buffer, "\nAdmin Menu:\n1. Add New Bank Employee\n2. Modify Customer/Employee Details\n3. Manage User Roles\n4. Change Password\n5. Logout\nEnter your choice: ");
        write(connFD, buffer, strlen(buffer));
        bzero(buffer, sizeof(buffer));
        // Read the choice from the admin
        read(connFD, buffer, sizeof(buffer));
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                add_new_employee(connFD);
                break;
            case 2:
                modify_employee_details(connFD);
                break;
            case 3:
                manage_user_roles(connFD);
                break;
            case 4:
                admin_change_password(connFD);
                break;
            case 5:
                admin_logout(connFD, userID);
                return;
            default:
                strcpy(buffer, "Invalid choice, try again.\n");
                write(connFD, buffer, strlen(buffer));
        }
        
         if (choice == 5) {
            break;
        }
    }
    strcpy(buffer, "Closing the connection to the server now!\n");
    write(connFD, buffer, strlen(buffer));
    close(connFD);
}

// Function to logout the admin
void admin_logout(int connFD, int userID) {

    // Send confirmation message to admin
    char buffer[100];
    strcpy(buffer, "Admin successfully logged out.\n");
    write(connFD, buffer, strlen(buffer));
    
    remove_user_from_session(userID); 

    // Close the connection for the admin
    close(connFD);
    return;
    
}

// Function to get the next employee ID
int get_next_employee_id() {
    FILE *file = fopen(EMP_FILENAME, "rb");  // Open in binary read mode
    if (file == NULL) {
        // If file does not exist, return 1 as the first employee ID
        return 1;
    }

    int lastID = 2000;  // Starting employee ID (can be adjusted)
    struct Employee tempEmployee;

    // Read all employee records to find the last employee ID
    while (fread(&tempEmployee, sizeof(struct Employee), 1, file) == 1) {
        if (tempEmployee.employeeID > lastID) {
            lastID = tempEmployee.employeeID;  // Update lastID if current ID is higher
        }
    }

    fclose(file);
    return lastID + 1;  // Return the next employee ID
}

//add new employee
void add_new_employee(int connFD) {
    char buffer[1000], emp_name[50], emp_password[50], emp_role[50];
    int empID;
    struct Employee employee;    
    
    FILE *empFile = fopen(EMP_FILENAME, "ab");  // Open in binary append mode
    if (empFile == NULL) {
        char errorMsg[] = "Error opening employee file.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }
    
    // Ask for employee name
    strcpy(buffer, "Enter Employee Name: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(emp_name, sizeof(emp_name));
    ssize_t bytesRead = read(connFD, emp_name, sizeof(emp_name) - 1);  // Only one read is needed
    
    if (bytesRead > 0) {
        emp_name[bytesRead] = '\0'; // Ensure null-termination
        emp_name[strcspn(emp_name, "\n")] = '\0'; // Remove newline character
        strncpy(employee.name, emp_name, sizeof(employee.name) - 1);
        employee.name[sizeof(employee.name) - 1] = '\0'; // Ensure null-termination
    } else {
        // Error handling for employee name input
        char errorMsg[] = "Error reading employee name.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        fclose(empFile);
        return;
    }

    // Ask for employee password
    strcpy(buffer, "Enter Employee Password: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(emp_password, sizeof(emp_password));
    bytesRead = read(connFD, emp_password, sizeof(emp_password) - 1);
    
    if (bytesRead > 0) {
        emp_password[bytesRead] = '\0'; // Ensure null-termination
        emp_password[strcspn(emp_password, "\n")] = '\0'; // Remove newline character
        strncpy(employee.pass, emp_password, sizeof(employee.pass) - 1);
        employee.pass[sizeof(employee.pass) - 1] = '\0'; // Ensure null-termination
    } else {
        // Error handling for employee password input
        char errorMsg[] = "Error reading employee password.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        fclose(empFile);
        return;
    }
    
    // Ask for employee role
    strcpy(buffer, "Enter Employee Role (manager/employee): ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(emp_role, sizeof(emp_role));
    bytesRead = read(connFD, emp_role, sizeof(emp_role) - 1);
    
    if (bytesRead > 0) {
        emp_role[bytesRead] = '\0'; // Ensure null-termination
        emp_role[strcspn(emp_role, "\n")] = '\0'; // Remove newline character
        
        // Validate the role
        if (strcmp(emp_role, "manager") != 0 && strcmp(emp_role, "employee") != 0) {
            char errorMsg[] = "Invalid role. Please enter 'manager' or 'employee'.\n";
            write(connFD, errorMsg, strlen(errorMsg));
            fclose(empFile);  // Close the file before returning
            return;
        }
    
        strncpy(employee.role, emp_role, sizeof(employee.role) - 1);
        employee.role[sizeof(employee.role) - 1] = '\0'; // Ensure null-termination
    } else {
        // Error handling for employee role input
        char errorMsg[] = "Error reading employee role.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        fclose(empFile);
        return;
    }
    
    // Assign the employee ID
    employee.employeeID = get_next_employee_id();
    
    // Save the new employee data 
    fwrite(&employee, sizeof(struct Employee), 1, empFile);

    // Close the employee file
    fclose(empFile);

    // Notify the user that the new employee has been added
    snprintf(buffer, sizeof(buffer), "New employee added successfully! Employee ID is: %d\n", employee.employeeID);
    write(connFD, buffer, strlen(buffer));
}

// Function to modify employee details
void modify_employee_details(int connFD) {
    char buffer[1000], employeeID_str[100], choice_str[100];
    int employeeID, found = 0;
    struct Employee employee;

    // Ask for the employee ID to modify
    strcpy(buffer, "Enter Employee ID to modify: ");
    write(connFD, buffer, strlen(buffer));

    bzero(employeeID_str, sizeof(employeeID_str));
    read(connFD, employeeID_str, sizeof(employeeID_str));
    employeeID = atoi(employeeID_str);

    // Open the employee file to find and modify the employee details
    FILE *file = fopen(EMP_FILENAME, "rb+");  // Open the file in binary read mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing employee data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    // Search for the employee by employeeID
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (employee.employeeID == employeeID) {
            found = 1;

            // Display the current details of the employee
            snprintf(buffer, sizeof(buffer),
                     "\nCurrent Employee Details:\n"
                     "Employee ID: %d\nName: %s\nPassword: %s\nRole: %s\n\n",
                     employee.employeeID, employee.name, employee.pass, employee.role);
            write(connFD, buffer, strlen(buffer));

            // Ask which field to modify
            strcpy(buffer, "What would you like to modify?\n1. Name\n2. Password\nEnter your choice: ");
            write(connFD, buffer, strlen(buffer));
            bzero(choice_str, sizeof(choice_str));
            read(connFD, choice_str, sizeof(choice_str));
            int choice = atoi(choice_str);

            switch (choice) {
                case 1:
                    // Modify Name
                    strcpy(buffer, "Enter new Name: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(employee.name, sizeof(employee.name));
                    read(connFD, employee.name, sizeof(employee.name));
                    break;

                case 2:
                    // Modify Password
                    strcpy(buffer, "Enter new Password: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(employee.pass, sizeof(employee.pass));
                    read(connFD, employee.pass, sizeof(employee.pass));
                    break;

                default:
                    strcpy(buffer, "Invalid choice.\n");
                    write(connFD, buffer, strlen(buffer));
                    fclose(file);
                    return;
            }

            // Move the file pointer back to the correct position
            fseek(file, -sizeof(struct Employee), SEEK_CUR);

            // Write the updated employee data back to the file
            fwrite(&employee, sizeof(struct Employee), 1, file);

            strcpy(buffer, "Employee details updated successfully.\n");
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Employee not found.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

// Function to manage user roles
void manage_user_roles(int connFD) {
    struct Employee employee;
    int employeeID;
    char buffer[1000];

    // Ask for the employeeID of the person whose role is to be changed
    strcpy(buffer, "Enter the employeeID of the person whose role you want to change: ");
    write(connFD, buffer, strlen(buffer));

    // Read employeeID input from the admin
    bzero(buffer, sizeof(buffer));  // Clear the buffer before reading new input
    read(connFD, buffer, sizeof(buffer));
    employeeID = atoi(buffer);  // Convert the input to integer (assuming employeeID is an integer)

    // Open the file "Emp.dat" containing employee data
    FILE *file = fopen(EMP_FILENAME, "rb+");
    if (!file) {
        strcpy(buffer, "Error opening Emp.dat file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the employee by employeeID
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (employee.employeeID == employeeID) {
            // Toggle the role between "employee" and "manager"
            if (strcmp(employee.role, "employee") == 0) {
                strcpy(employee.role, "manager");
            } 
            else if (strcmp(employee.role, "manager") == 0) {
                strcpy(employee.role, "employee");
            } 
            else {
                strcpy(buffer, "Invalid role found.\n");
                write(connFD, buffer, strlen(buffer));
                fclose(file);
                return;
            }

            // Move the file pointer back to the beginning of the current record
            fseek(file, -sizeof(struct Employee), SEEK_CUR);

            // Write the updated employee record back to the file
            fwrite(&employee, sizeof(struct Employee), 1, file);

            // Inform the admin that the role has been changed
            strcpy(buffer, "Employee role changed successfully.\n");
            write(connFD, buffer, strlen(buffer));

            fclose(file);
            return;
        }
    }

    // If the employeeID was not found, inform the admin
    fclose(file);
    strcpy(buffer, "Employee not found.\n");
    write(connFD, buffer, strlen(buffer));
}

// Function to change admin password
void admin_change_password(int connFD) {
    char buffer[1000], old_password[50], new_password[50], confirm_password[50];
    
    // Ask for old password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter your old password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(old_password, sizeof(old_password));
    read(connFD, old_password, sizeof(old_password));
    old_password[strcspn(old_password, "\n")] = 0;  // Remove newline character
    
    // Ask for new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter New Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));
    new_password[strcspn(new_password, "\n")] = 0;  // Remove newline character

    // Confirm new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Confirm New Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(confirm_password, sizeof(confirm_password));
    read(connFD, confirm_password, sizeof(confirm_password));
    confirm_password[strcspn(confirm_password, "\n")] = 0;  // Remove newline character
    
    
    FILE *file = fopen(ADMIN_FILENAME, "rb+");
    if (file == NULL) {
        printf("Error opening admin file.\n");
        return;  // Authentication failed due to file access issue
    }

    struct Admin admin;
    int found = 0;
    while (fread(&admin, sizeof(struct Admin), 1, file)) {
        if (strcmp(old_password, admin.pass) == 0) {
            found = 1;  // Authentication successful
            break;
        }
    }
    
    if (!found) {
        strcpy(buffer, "Old password is incorrect.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }
    
    printf("%s\n",new_password);
    printf("%s\n",confirm_password);

    if (strcmp(new_password, confirm_password) == 0) {
        strncpy(admin.pass, new_password, sizeof(admin.pass) - 1);
        fseek(file, -sizeof(struct Admin), SEEK_CUR);
        fwrite(&admin, sizeof(struct Admin), 1, file);
        strcpy(buffer, "Password changed successfully.\n");
    } else {
        strcpy(buffer, "New password and confirmation do not match.\n\n");
    }
    
    fclose(file);
    write(connFD, buffer, strlen(buffer));
}
