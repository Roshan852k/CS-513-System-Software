#include "user.h"
//#include "customer.h"
#include "loan.h"
#include "feedback.h"
#include "manager.h"
#include "employee.h"
#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define FEED_FILENAME "feedbacks.dat" // File for customer feedback
#define EMP_FILENAME "employee.dat"  // File for employee account_info
#define CUST_FILENAME "accounts1.dat"  
#define LOAN_FILENAME "loan.dat" // File for customer loan

// Function prototypes

int authenticate_manager(int connFD, int userID, const char *username, const char *password) {
    struct Employee employee;
    FILE *file = fopen(EMP_FILENAME, "rb"); // Open the employee data file in binary mode
    if (file == NULL) {
        write(connFD, "Error opening employee file.\n", 30);
        return 0; // File error
    }
    
    // Check if user is already logged in
    if (is_user_logged_in(userID)) {
        write(connFD, "Error: Employee is already logged in.\n", 39);
        fclose(file);
        return 0; // User already logged in
    }

    // Iterate through the file to find the employee
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (strcmp(employee.name, username) == 0 && strcmp(employee.pass, password) == 0) {
            // Add the user to the session file (indicating login)
            if (strcmp(employee.role, "manager") != 0) {
                write(connFD, "Access Denied: Not a manager.\n", 30);
                fclose(file);
                return 0; // Not a manager
            }
            add_user_to_session(userID);
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    write(connFD, "Invalid credentials.\n", 21);
    return 0; // Authentication failed
}

// Function to logout and set isLoggedIn to false
void logout_manager(int connFD, int userID) {
    struct User user;
    FILE *file = fopen("session.txt", "r+");
    if (file == NULL) {
        printf("Error opening users file.\n");
        return;
    } 
    
    remove_user_from_session(userID);
    
     // Close the connection for the client after logging out
    close(connFD);
    fclose(file);
}

// Function to display the manager menu after successful login
void manager_menu(int connFD, int userID) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display manager menu options
        strcpy(buffer, "\nManager Menu:\n1. Activate/Deactivate Customer\n2. Assign Loan Process\n3. Review Feedback\n4. Change Password\n5. View Unassigned loans\n6. Logout\nEnter your choice : ");
        fflush(stdout);
        write(connFD, buffer, strlen(buffer));
        
        // Get user's choice
        bzero(buffer, sizeof(buffer));
        read(connFD, buffer, sizeof(buffer));  // Read user's input
        buffer[strcspn(buffer, "\n")] = 0;     // Remove any newline characters
        choice = atoi(buffer);                 // Convert choice to integer
        
        switch (choice) {
            case 1:
                // Activate/Deactivate customer function
                // activate_deactivate_customer(connFD);
                int customerID;
                char customerID_str[50];
                char choice_str[50];
                char buffer[1000]; 
                
                // Ask for the customer ID
                strcpy(buffer, "Enter Customer ID: ");
                write(connFD, buffer, strlen(buffer));
                
                bzero(customerID_str, sizeof(customerID_str));
                ssize_t bytesRead = read(connFD, customerID_str, sizeof(customerID_str) - 1);
                
                if (bytesRead > 0) {
                    customerID_str[bytesRead] = '\0'; // Ensure null-termination
                    customerID_str[strcspn(customerID_str, "\n")] = '\0'; // Remove newline character
                    customerID = atoi(customerID_str); // Convert to integer
                } 

                // Ask for the activated or deactivated
                strcpy(buffer, "1. Deactivate customer account\n2. Activate customer account\n");
                write(connFD, buffer, strlen(buffer));
 
                strcpy(buffer, "Enter your choice: ");
                write(connFD, buffer, strlen(buffer));
                
                bzero(choice_str, sizeof(choice_str));
                bytesRead = read(connFD, choice_str, sizeof(choice_str) - 1);
                
                if (bytesRead > 0) {
                    choice_str[bytesRead] = '\0'; // Ensure null-termination
                    choice_str[strcspn(choice_str, "\n")] = '\0'; // Remove newline character
                    choice = atoi(choice_str);
                }

                if (choice == 1) {
                    deactivate_account(connFD,customerID);
                }  
                else if (choice == 2) {
                    activate_account(connFD,customerID);
                } 
                else {
                    strcpy(buffer, "Invalid choice.\n");
                    write(connFD, buffer, strlen(buffer));
                }  
                
                break;
            case 2:
                // Assign loan process function
                assign_loan_to_employee(connFD);
                break;
            case 3:
                // Review feedback function
                review_feedback(connFD);
                break;
            case 4:
                change_manager_password(connFD,userID);
                break;
            case 5:
                view_unassigned_loans(connFD);
                break;
            case 6:
                // Logout and set isLoggedIn to false
                logout_manager(connFD, userID);
                //write(connFD, "Logging out...\n", 15);
                return;
            default:
                write(connFD, "Invalid option.\n", 16);
        }
        if (choice == 6) {
          break;
        } 
    }
}

// Function to get employeeID
int get_manager_employeeID(const char *username, const char *password, int connFD) {    
    struct Employee employee;
    FILE *file = fopen(EMP_FILENAME, "rb"); // Open the employee data file in binary mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing employee data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return 0; // File error
    }

    // Read each account from the file and compare username and password
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (strcmp(employee.name, username) == 0 && strcmp(employee.pass, password) == 0) {
              return employee.employeeID;  // Return customerID if credentials match
        }
    }
    
    printf("EmployeeID not found\n");
    fclose(file);
    return -1;  // Return -1 if no match found
}

// Manager login function
int manager_login(int connFD) {
    char buffer[1000], username[100], password[50];
    int userID;

        // Ask for employee ID
    strcpy(buffer, "Enter Employee ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(username, sizeof(username));
    read(connFD, username, sizeof(username));
    username[strcspn(username, "\n")] = 0; // Remove trailing newline if present
    
    // Ask for password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));
    password[strcspn(password, "\n")] = 0; 
    
    printf("Usename received: %s\n", username);
    printf("Password received: %s\n", password);

    // Validate manager credentials
    int employeeID = get_manager_employeeID(username, password, connFD);
    if (authenticate_manager(connFD, employeeID, username, password)) {
        manager_menu(connFD, employeeID);
        return 1;
    } else {
        strcpy(buffer, "Invalid Manager ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return 0;
    }
}

// Function to change admin password
void change_manager_password(int connFD, int managerID) {
    char buffer[1000], new_password[50];
    struct User user;
    int found = 0;

    // Ask for new password
    strcpy(buffer, "Enter new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));

    // Open the users.txt file to read/write
    FILE *file = fopen("users.txt", "rb+");  // Open in read/write binary mode
    if (file == NULL) {
        strcpy(buffer, "Error opening users.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the manager by userID
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == managerID && user.isManager == 1) {
            found = 1;
            // Update the password
            strcpy(user.password, new_password);

            // Go back to the position of this user in the file
            fseek(file, -sizeof(struct User), SEEK_CUR);
            // Write the updated record
            fwrite(&user, sizeof(struct User), 1, file);
            fclose(file);

            strcpy(buffer, "Password changed successfully.\n");
            write(connFD, buffer, strlen(buffer));
            return;
        }
    }

    fclose(file);
    if (!found) {
        strcpy(buffer, "Manager not found.\n");
        write(connFD, buffer, strlen(buffer));
    }
}

// Function to review customer feedback
void review_feedback(int connFD) {
    struct Feedback fbEntry;
    char buffer[1000];
    int customerID;

    // Ask for the customer ID
    strcpy(buffer, "Please enter your Customer ID: ");
    write(connFD, buffer, strlen(buffer));

    // Clear buffer and read the customer ID input
    bzero(buffer, sizeof(buffer));
    ssize_t bytesRead = read(connFD, buffer, sizeof(buffer) - 1);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Ensure null-termination
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Convert the input string to an integer
        customerID = atoi(buffer);
    } else {
        strcpy(buffer, "Error reading Customer ID.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Open the feedback file for reading
    FILE *file = fopen(FEED_FILENAME, "rb");
    if (file == NULL) {
        snprintf(buffer, sizeof(buffer), "Error opening feedback file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    snprintf(buffer, sizeof(buffer), "Feedbacks for Customer ID %d:\n", customerID);
    write(connFD, buffer, strlen(buffer));
    
    int found = 0;  // Flag to track if any feedback is found

    // Read all feedback entries and display those matching the customer ID
    while (fread(&fbEntry, sizeof(struct Feedback), 1, file) == 1) {
        if (fbEntry.customerID == customerID) {
            snprintf(buffer, sizeof(buffer), "- %s\n", fbEntry.feedback);  // Format feedback for output
            write(connFD, buffer, strlen(buffer));  // Send feedback to the client
            found = 1;  // Set flag if feedback is found
        }
    }

    fclose(file);
    
    if (!found) {
        snprintf(buffer, sizeof(buffer), "No feedback found for Customer ID %d.\n", customerID);
        write(connFD, buffer, strlen(buffer));  // Send message indicating no feedback found
    }
}

// Function to assigned loans employee
void assign_loan_to_employee(int connFD) {
    char buffer[1000], loanID_str[50], employeeID_str[50];
    struct Loan loan;
    int loanID, employeeID;
    bool loanFound = false; // Flag to check if loan is found

    // Prompt for Loan ID
    strcpy(buffer, "Enter Loan ID to assign: ");
    write(connFD, buffer, strlen(buffer));

    // Read Loan ID
    bzero(loanID_str, sizeof(loanID_str));
    read(connFD, loanID_str, sizeof(loanID_str));
    loanID = atoi(loanID_str); // Convert to integer

    // Prompt for Employee ID
    strcpy(buffer, "Enter Employee ID to assign the loan to: ");
    write(connFD, buffer, strlen(buffer));

    // Read Employee ID
    bzero(employeeID_str, sizeof(employeeID_str));
    read(connFD, employeeID_str, sizeof(employeeID_str));
    employeeID = atoi(employeeID_str); // Convert to integer

    // Open the loan file
    FILE *file = fopen(LOAN_FILENAME, "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening loan.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the loan by loanID
    while (fread(&loan, sizeof(struct Loan), 1, file) == 1) {
        if (loan.loanID == loanID) {
            loanFound = true;
            loan.assignedEmployee = employeeID; // Assign the employee ID

            // Move the file pointer back to overwrite the record
            fseek(file, -sizeof(struct Loan), SEEK_CUR);
            fwrite(&loan, sizeof(struct Loan), 1, file);

            // Inform the manager of the successful assignment
            sprintf(buffer, "LoanID %d has been assigned to EmployeeID %d.\n", loanID, employeeID);
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    // If loan not found, inform the user
    if (!loanFound) {
        sprintf(buffer, "LoanID %d not found.\n", loanID);
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file); // Close the loan file
}

// Function to view unassigned loans
void view_unassigned_loans(int connFD) {
    struct Loan loan;
    FILE *file = fopen("loan.dat", "rb"); // Open the loan file in binary read mode
    if (file == NULL) {
        char *errorMsg = "Error opening loan.dat file.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    char buffer[1000];
    int byteswrie;
    int tmp = 0; // check there is pending loan application

    // Read the loan data from file and display unassigned loans
    
    strcpy(buffer, "\n------ Loan Application -----\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "LoanID: | CustomerID: | AccountNumber: | Amount: ₹ | Status: \n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));

    while (fread(&loan, sizeof(struct Loan), 1, file) == 1) {
        if (loan.assignedEmployee == 0) {
            snprintf(buffer, sizeof(buffer), "%d | %d | %d | ₹%.2f | %d\n", 
                     loan.loanID, loan.customerID, loan.accountNumber, loan.loanAmount, loan.loanStatus);
            write(connFD, buffer, strlen(buffer));
            tmp = 1;
        }
    }

    if (!tmp) {
        char *noLoansMsg = "No unassigned loans found.\n";
        write(connFD, noLoansMsg, strlen(noLoansMsg));
    }

    fclose(file);
}

// Function to deactivate account
void deactivate_account(int connFD, int customerID) {
    char buffer[1000];
    struct Account user;
    FILE *file = fopen(CUST_FILENAME, "rb+");  // Open in binary read/update mode
    if (file == NULL) {
        strcpy(buffer, "Error opening account data.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found = 0;
    
    // Read each account to find the one with the specified customerID
    while (fread(&user, sizeof(struct Account), 1, file) == 1) {
        if (user.customerID == customerID) {
            found = 1;
            user.status = 0;  // Set status to 0 (deactivated)

            // Move the file pointer back to the position of the current account
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&user, sizeof(struct Account), 1, file);  // Write the updated account back
            
            snprintf(buffer, sizeof(buffer), "Account with ID %d has been deactivated.\n", customerID);
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!found) {
        snprintf(buffer, sizeof(buffer), "Account with ID %d not found.\n", customerID);
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

// Function to activate account
void activate_account(int connFD, int customerID) {
    char buffer[1000];
    struct Account user;
    FILE *file = fopen(CUST_FILENAME, "rb+");  // Open in binary read/update mode
    if (file == NULL) {
        strcpy(buffer, "Error opening account data.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found = 0;
    
    // Read each account to find the one with the specified customerID
    while (fread(&user, sizeof(struct Account), 1, file) == 1) {
        if (user.customerID == customerID) {
            found = 1;
            user.status = 1;  // Set status to 1 (activated)

            // Move the file pointer back to the position of the current account
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&user, sizeof(struct Account), 1, file);  // Write the updated account back
            
            snprintf(buffer, sizeof(buffer), "Account with ID %d has been activated.\n", customerID);
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!found) {
        snprintf(buffer, sizeof(buffer), "Account with ID %d not found.\n", customerID);
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}
