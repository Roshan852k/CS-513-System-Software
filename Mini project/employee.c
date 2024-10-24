#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "employee.h"
// #include "customer.h"
#include "user.h"
#include "loan.h"
#include "account.h"  
#include "transaction.h"

#define CUST_FILENAME "accounts1.dat"  // File for customer account_info
#define TRANS_FILENAME "transactions.dat" 
#define EMP_FILENAME "employee.dat"  // File for employee account_info
#define LOAN_FILENAME "loan.dat" // File for customer loan

/*
struct Transaction {
    int customerID;
    char date[11]; 
    char transactionType[20];  // Deposit, Withdrawal, Transfer 
    float amount;
    float balance;
    char transactionStatus[20]; // Credited, Debited
};
*/

// Authenticate Employee Login System
int authenticate_employee(int connFD, int userID, const char *username, const char *password) {
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
            if (strcmp(employee.role, "manager") == 0) {
                write(connFD, "Access Denied: Not for manager.\n", 33);
                fclose(file);
                return 0; // a manager
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

// Funntion to get get_employeeID
int get_employeeID(const char *username, const char *password, int connFD) {    
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

// Employee Login System
int employee_login(int connFD) {
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

    // Validate employee credentials
    int employeeID = get_employeeID(username, password, connFD);
    if (authenticate_employee(connFD, employeeID, username, password)) {
        employee_menu(connFD, employeeID);
        return 1;
    } else {
        strcpy(buffer, "Invalid Employee ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return 0;
    }
}

// Function to get the next customerID
int get_next_customer_id() {
    FILE *file = fopen(CUST_FILENAME, "rb");  // Open in binary read mode
    if (file == NULL) {
        // If file does not exist, return 1 as the first customer ID
        return 1;
    }

    int lastID = 1000;
    struct Account tempAccount;

    // Read all user accounts to find the last customer ID
    while (fread(&tempAccount, sizeof(struct Account), 1, file) == 1) {
        if (tempAccount.customerID > lastID) {
            lastID = tempAccount.customerID;  // Update lastID if current ID is higher
        }
    }

    fclose(file);
    return lastID + 1;  // Return the next customer ID
}

// Function to get the next account number
int get_next_account_number() {
    FILE *file = fopen(CUST_FILENAME, "rb");  // Open in binary read mode
    if (file == NULL) {
        // If file does not exist, return 10001 as the first account number
        return 10001;
    }

    int lastAccountNumber = 10000;  // Initialize to one less than the starting number
    struct Account tempAccount;

    // Read all user accounts to find the last account number
    while (fread(&tempAccount, sizeof(struct Account), 1, file) == 1) {
        if (tempAccount.accountNumber > lastAccountNumber) {
            lastAccountNumber = tempAccount.accountNumber;  // Update if current account number is higher
        }
    }

    fclose(file);
    return lastAccountNumber + 1;  // Return the next account number
}

// Function to add new employee
void add_new_customer(int connFD) {
    char buffer[1000], username[100], password[50], amount[20];
    int balance;
    struct Account newCustomer;
    
    FILE *customerFile = fopen(CUST_FILENAME, "ab");  // Open in binary append mode
    if (customerFile == NULL) {
        char errorMsg[] = "Error opening customer file.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    // Ask for customer name
    strcpy(buffer, "Enter username: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(username, sizeof(username));
    ssize_t bytesRead = read(connFD, username, sizeof(username) - 1);
    
    if (bytesRead > 0) {
        username[bytesRead] = '\0'; // Ensure null-termination
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
        strncpy(newCustomer.name, username, sizeof(newCustomer.name) - 1);
        newCustomer.name[sizeof(newCustomer.name) - 1] = '\0'; // Ensure null-termination
    }

    // Ask for customer password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(password, sizeof(password));
    bytesRead = read(connFD, password, sizeof(password) - 1);
    
    if (bytesRead > 0) {
        password[bytesRead] = '\0'; // Ensure null-termination
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
        strncpy(newCustomer.pass, password, sizeof(newCustomer.pass) - 1);
        newCustomer.pass[sizeof(newCustomer.pass) - 1] = '\0'; // Ensure null-termination
    }
    
    // Ask for customer password 
    strcpy(buffer, "Enter initial balance ₹: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(amount, sizeof(amount));
    bytesRead = read(connFD, amount, sizeof(amount) - 1);
    
    if (bytesRead > 0) {
        amount[bytesRead] = '\0'; // Ensure null-termination
        amount[strcspn(amount, "\n")] = '\0'; // Remove newline character
        newCustomer.balance = atoi(amount);
    }
    
    newCustomer.customerID = get_next_customer_id();  // Get the next customer ID
    newCustomer.accountNumber = get_next_account_number();  // Generate account number
    
    // Set isActive to 1 (active)
    newCustomer.status = 1;
    
    // Save the new customer data
    fwrite(&newCustomer, sizeof(struct Account), 1, customerFile);

    // Close both files
    fclose(customerFile);

    // Notify the user that the new customer and account have been added
    snprintf(buffer, sizeof(buffer), "New user added successfully! Your Customer ID is: %d and Account Number is: %d\n", newCustomer.customerID, newCustomer.accountNumber);
    write(connFD, buffer, strlen(buffer));
}

// Function to modify customer details
void modify_customer_details(int connFD) {
    char buffer[1000], CustomerID_str[100],choice_str[100];
    int CustomerID, found = 0;
    struct Account account;
    
    // Ask for the customer ID to modify
    strcpy(buffer, "Enter Customer User ID to modify: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(CustomerID_str, sizeof(CustomerID_str));
    read(connFD, CustomerID_str, sizeof(CustomerID_str));
    CustomerID = atoi(CustomerID_str);

    // Open the customer file to find and modify the customer details
    FILE *file = fopen(CUST_FILENAME, "rb+");  // Open the file in binary read mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing account data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    // Search for the customer by CustomerID
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (account.customerID == CustomerID) {
            found = 1;

            // Display the current details of the customer
            snprintf(buffer, sizeof(buffer),
                     "\nCurrent Customer Details:\n"
                     "Customer ID: %d\nName: %s\nPassword: %s\n\n",
                     account.customerID, account.name, account.pass);
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
                    bzero(account.name, sizeof(account.name));
                    read(connFD, account.name, sizeof(account.name));
                    break;

                case 2:
                    // Modify Password
                    strcpy(buffer, "Enter new Password: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(account.pass, sizeof(account.pass));
                    read(connFD, account.pass, sizeof(account.pass));
                    break;

                default:
                    strcpy(buffer, "Invalid choice.\n");
                    write(connFD, buffer, strlen(buffer));
                    fclose(file);
                    return;
            }

            // Move the file pointer back to the correct position
            fseek(file, -sizeof(struct Account), SEEK_CUR);

            // Write the updated customer data back to the file
            fwrite(&account, sizeof(struct Account), 1, file);

            strcpy(buffer, "Customer details updated successfully.\n");
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

// Function to approve or reject loan application 
void approve_reject_loans(int connFD, int employeeID) {
    struct Loan loan;
    FILE *file = fopen(LOAN_FILENAME, "rb+");
    char buffer[1000];

    if (file == NULL) {
        strcpy(buffer, "Error opening loan file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found = 0;
    // Go through each loan in the file
    while (fread(&loan, sizeof(struct Loan), 1, file) == 1) {
        // Check if the loan is assigned to the current employee and is still pending
        if (loan.assignedEmployee == employeeID && loan.loanStatus == -1) {
            found = 1;
            snprintf(buffer, sizeof(buffer), 
                     "Loan ID: %d, Customer ID: %d, Amount: %.2f\n",
                     loan.loanID, loan.customerID, loan.loanAmount);
            write(connFD, buffer, strlen(buffer));
            
            // Ask for acceptance or rejection
            strcpy(buffer, "Do you want to accept or reject this loan? (a/r): ");
            write(connFD, buffer, strlen(buffer));
            
            char response[10];
            bzero(response, sizeof(response));
            ssize_t bytesRead = read(connFD, response, sizeof(response) - 1);
            
            if (bytesRead > 0) {
                response[bytesRead] = '\0';
                response[strcspn(response, "\n")] = '\0'; // Remove newline character

                if (strcmp(response, "a") == 0) {
                    loan.loanStatus = 1; // Mark the loan as accepted
                    strcpy(buffer, "Loan accepted.\n");
                } 
                else if (strcmp(response, "r") == 0) {
                    loan.loanStatus = -1; // Mark the loan as rejected
                    strcpy(buffer, "Loan rejected.\n");
                } 
                else {
                    strcpy(buffer, "Invalid input. Skipping this loan.\n");
                }
                
                write(connFD, buffer, strlen(buffer));
                
                // Move the file pointer to the start of the current loan record
                fseek(file, -sizeof(struct Loan), SEEK_CUR);
                // Update the loan status in the file
                fwrite(&loan, sizeof(struct Loan), 1, file);
                fflush(file); // Ensure the write is immediately reflected
            }
        }
    }

    if (!found) {
        strcpy(buffer, "No pending loans assigned to you.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

// Function to employee admin password
void change_employee_password(int connFD, int employeeID) {
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
    
    
    FILE *file = fopen(EMP_FILENAME, "rb+");
    if (file == NULL) {
        printf("Error opening admin file.\n");
        return;  // Authentication failed due to file access issue
    }

    struct Employee employee;
    int found = 0;
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (strcmp(old_password, employee.pass) == 0) {
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
        strncpy(employee.pass, new_password, sizeof(employee.pass) - 1);
        fseek(file, -sizeof(struct Employee), SEEK_CUR);
        fwrite(&employee, sizeof(struct Employee), 1, file);
        strcpy(buffer, "Password changed successfully.\n");
    } else {
        strcpy(buffer, "New password and confirmation do not match.\n\n");
    }
    
    fclose(file);
    write(connFD, buffer, strlen(buffer));
}

// Function to view customer transaction history
void view_customer_transactions(int connFD) {
    char buffer[1000], custID[50];
    int customerID;
    struct Transaction trans;
    
    // Ask for the customer ID
    strcpy(buffer, "Enter your CustomerID: ");
    write(connFD, buffer, strlen(buffer));
    
    bzero(custID, sizeof(custID));
    ssize_t bytesRead = read(connFD, custID, sizeof(custID) - 1);
    if (bytesRead <= 0) {
        strcpy(buffer, "Error reading CustomerID.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }
    
    custID[bytesRead] = '\0'; // Null-terminate
    customerID = atoi(custID); // Convert input to integer

    // Open the transaction file
    FILE *file = fopen(TRANS_FILENAME, "rb");
    if (file == NULL) {
        strcpy(buffer, "Error loading transaction history.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found = 0;

    // Header to display transaction details
    strcpy(buffer, "\n------ Transaction History -----\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "Date: | Type: | Status: | Amount: ₹ | Balance: ₹\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));

    // Read each transaction from the file
    while (fread(&trans, sizeof(struct Transaction), 1, file) == 1) {
        if (trans.customerID == customerID) {
            // Format the transaction details into the buffer and send them to the client
            snprintf(buffer, sizeof(buffer), "%s | %s | %s | ₹%.2f | ₹%.2f\n",
                     trans.date, trans.transactionType, trans.transactionStatus, trans.amount, trans.balance);
            write(connFD, buffer, strlen(buffer));
            found = 1;
        }
    }

    if (!found) {
        strcpy(buffer, "No transactions found for the specified CustomerID.\n");
        write(connFD, buffer, strlen(buffer));
    }

    // Close the file after processing
    fclose(file);
}


// Function to logout and set isLoggedIn to false
void logout_employee(int connFD, int userID) {
    remove_user_from_session(userID); // Remove from session.txt
    write(connFD, "Logging out...\n", 15);

    // Close the connection for the client after logging out
    close(connFD);
    printf("Employee (EmployeeId: %d) logged out successfully and connection closed.\n", userID);
}

// Employee Menu Function
void employee_menu(int connFD, int employeeID) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display menu options
        strcpy(buffer, "\n--- Employee Menu ---\n"
                       "1. Add New Customer\n"
                       "2. Modify Customer Details\n"
                       "3. Approve/Reject Loans\n"
                       "4. View Assigned Loan Applications\n"
                       "5. View Customer Transactions\n"
                       "6. Change Password\n"
                       "7. Logout\n"
                       "Enter your choice: ");
        write(connFD, buffer, strlen(buffer));

        // Get employee's choice
        bzero(buffer, sizeof(buffer));
        read(connFD, buffer, sizeof(buffer));
        choice = atoi(buffer);

        // Perform action based on choice
        switch (choice) {
            case 1:
                add_new_customer(connFD);
                break;
            case 2:
                modify_customer_details(connFD);
                break;
            case 3:
                approve_reject_loans(connFD,employeeID);
                break;
            case 4:
                view_assigned_loans(connFD,employeeID);
                break;
            case 5:
                view_customer_transactions(connFD);
                break;
            case 6:
                change_employee_password(connFD,employeeID);
                break;
            case 7:
                logout_employee(connFD, employeeID);
                return;  // Exit the menu after logout
            default:
                strcpy(buffer, "Invalid choice. Please try again.\n");
                write(connFD, buffer, strlen(buffer));
        }
         if (choice == 7) {
          break;
      }
    }
}

// Function to view the assigned loans
void view_assigned_loans(int connFD, int employeeID) {
    struct Loan loan;
    char buffer[1000];

    // Open the loan file for reading
    FILE *file = fopen(LOAN_FILENAME, "rb"); // Use "rb" for binary reading
    if (file == NULL) {
        sprintf(buffer, "Error opening loan file.\n");
        write(connFD, buffer, strlen(buffer)); // Send error message to client
        return;
    }

    // Prepare to display loans assigned to the specified employee
    sprintf(buffer, "Loans assigned to EmployeeID %d:\n", employeeID);
    write(connFD, buffer, strlen(buffer)); // Send the header to the client
    
    int byteswrie;
    int tmp = 0; // check there is pending loan application
    
    
    strcpy(buffer, "\n------ Loan Application -----\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "LoanID: | CustomerID: | AccountNumber: | Amount: ₹\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));
    
    // Read loans from the file
    while (fread(&loan, sizeof(struct Loan), 1, file) == 1) {
        if (loan.assignedEmployee == employeeID) {
            snprintf(buffer, sizeof(buffer), "%d | %d | %d | ₹%.2f\n", 
                     loan.loanID, loan.customerID, loan.accountNumber, loan.loanAmount);
            write(connFD, buffer, strlen(buffer));
            tmp = 1;
        }
    }

    if (!tmp) {
        sprintf(buffer, "No loans assigned to EmployeeID %d.\n", employeeID);
        write(connFD, buffer, strlen(buffer)); // Send message to client if no loans found
    }
    
    fclose(file); // Close the file
}
