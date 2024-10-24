#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For read, write, close functions
#include <stdlib.h>
// #include "customer.h"  // Include the header file with declarations
#include "account.h"
#include <fcntl.h>
#include "feedback.h"
#include "loan.h"
#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"  
#include "session.h"
#include <time.h>

#define CUST_FILENAME "accounts1.dat"  // File for customer account_info
#define TRANS_FILENAME "transactions.dat" 
#define FEED_FILENAME "feedbacks.dat" // File for customer feedback
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

// Function to save transaction for a customer
// Function to lock the file for read/write operations
void lock_file(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;   // F_RDLCK for read, F_WRLCK for write
    lock.l_whence = SEEK_SET;  // Start of the file
    lock.l_start = 0;          // Offset from the start
    lock.l_len = 0;            // Lock the whole file (0 means entire file)
    lock.l_pid = getpid();     // Process ID

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking file");
        exit(EXIT_FAILURE);
    }
}

// Function to unlock the file after the operation
void unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;    // Unlock the file
    lock.l_whence = SEEK_SET; // Start of the file
    lock.l_start = 0;         // Offset from the start
    lock.l_len = 0;           // Unlock the whole file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking file");
        exit(EXIT_FAILURE);
    }
}

// Funntion to get customerID
int get_customerID(const char *username, const char *password, int connFD) {
    struct Account account;
    FILE *file = fopen(CUST_FILENAME, "rb");  // Open the file in binary read mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing account data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return 0;
    }
    

    // Read each account from the file and compare username and password
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (strcmp(account.name, username) == 0 && strcmp(account.pass, password) == 0) {
            if (account.status == 1) {  // Check if account is active
                fclose(file);
                return account.customerID;  // Return customerID if credentials match
            } else {
                printf("Account is deactivated.\n");
                fclose(file);
                return -1;
            }
        }
    }

    fclose(file);
    return -1;  // Return -1 if no match found
}

// Authenticate Customer Login System
int validate_user_info(int connFD, int userID, const char* username, const char* password) {
    struct Account user;
    
    FILE *file = fopen(CUST_FILENAME, "rb");  // Open in binary read mode
    if (file == NULL) {
        printf("Error loading account data.\n");
        return 0; // Indicate failure
    }
  
    printf("Username :%s\n",username);
    printf("Password :%s\n",password);
    
    // Read each account to check if username and password match
    printf("validating credential.\n");
    fflush(stdout);
    
    // Check if user is already logged in
    if (is_user_logged_in(userID)) {
        write(connFD, "Error: Employee is already logged in.\n", 39);
        fclose(file);
        return 0; // User already logged in
    }
    
    while (fread(&user, sizeof(struct Account), 1, file) == 1) {
        if (strcmp(user.name, username) == 0 && strcmp(user.pass, password) == 0) {
            printf("credential match successfully.\n");
            if (user.status == 1) {  // Check if the account is active
                add_user_to_session(userID);
                fclose(file);
                return 1;  // Login success
            } else {
                //printf("Your Account is deactivated. Please visit to your nearest branch office.\n");
                fclose(file);
                return -1;  // Indicate deactivated account
            }
        }
    }
    
    fclose(file);
    return 0;  // Username or password not found
}

// Customer Login System
void customer_login(int connFD) {
    char buffer[1024];
    char username[20], password[20];
    
    // Prompt for userID
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter Username: ");
    write(connFD, buffer, strlen(buffer));
    bzero(username, sizeof(username));
    read(connFD, username, sizeof(username));
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    // Prompt for password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));
    password[strcspn(password, "\n")] = 0;  // Remove newline character
    
    printf("Usename received: %s\n", username);
    printf("Password received: %s\n", password);

    // Authenticate customer
    int customerID = get_customerID(username, password, connFD);
    int validate = validate_user_info(connFD, customerID, username, password);
    if (validate==1) {
        // Call customer_menu with userID
        //int customerID = get_customerID(username, password, connFD);
        customer_menu(connFD, customerID);
    } 
    else if (validate==-1) {
        strcpy(buffer, "Your Account is deactivated. Please visit to your nearest branch office.\n");
        write(connFD, buffer, strlen(buffer));
    }
    else{
        strcpy(buffer, "Login failed. Invalid User ID or password.\n");
        write(connFD, buffer, strlen(buffer));
    }
    return;
}

// Customer Menu Function
void customer_menu(int connFD, int userID) {
    char buffer[1000];
    int choice;

  // Start an infinite loop
      while (1) {
      // Display menu
          strcpy(buffer, "\nCustomer Menu:\n1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Funds\n5. Apply for Loan\n6. Change Password\n7. Add Feedback\n8. View Transaction History\n9. Logout\nEnter your choice: ");
          fflush(stdout);
          write(connFD, buffer, strlen(buffer));  // Write menu to client
          
          // Get user's choice
          bzero(buffer, sizeof(buffer));
          read(connFD, buffer, sizeof(buffer));  // Read user's input
          buffer[strcspn(buffer, "\n")] = 0;     // Remove newline characters
          choice = atoi(buffer);                 // Convert choice to integer
          
          // Process user's choice
          switch (choice) {
              case 1:
                  view_account_balance(connFD, userID);  // Show balance
                  break;
              case 2:
                  deposit_money(connFD, userID);         // Handle deposit
                  break;
              case 3:
                  withdraw_money(connFD, userID);        // Handle withdrawal
                  break;
              case 4:
                  transfer_funds(connFD, userID);        // Handle funds transfer
                  break;
              case 5:
                  apply_for_loan(connFD, userID);        // Apply for loan
                  break;
              case 6:
                  change_password(connFD, userID);       // Change password
                  break;
              case 7:
                  add_customer_feedback(connFD, userID); // Add feedback
                  break;
              case 8:
                  view_transaction_history(connFD, userID);  // View transaction history
                  break;
              case 9:
                  customer_logout(connFD, userID);       // Handle logout
                  // printf("Logging out...\n");
                  break;  // Exit the loop on logout
              default:
                  // Invalid choice
                  strcpy(buffer, "Invalid choice! Please try again.\n");
                  write(connFD, buffer, strlen(buffer));  // Send error message to client
                  fflush(stdout);
                  break;
          }
          
          // Break the loop if user chooses to logout (choice == 9)
          if (choice == 9) {
              break;
          }
      }

    // After logout, close the connection
    strcpy(buffer, "Closing the connection to the server now!\n");
    write(connFD, buffer, strlen(buffer));
    close(connFD);
}

// Function to logout the customer
void customer_logout(int connFD, int userID) {
    // Remove customer from session (assuming a function exists to handle this)
    //remove_user_from_session(userID);  // remove_user_from_session() will handle removing the user from the session

    // Send confirmation message to customer
    char buffer[100];
    strcpy(buffer, "Customer successfully logged out.\n");
    write(connFD, buffer, strlen(buffer));
    
    remove_user_from_session(userID); 
    
    // Close the connection for the customer
    close(connFD);
    printf("Customer (UserID: %d) logged out successfully and connection closed.\n", userID);
}

// Deposit money into view account balance
void view_account_balance(int connFD, int customerID) {
    FILE *file = fopen(CUST_FILENAME, "rb");  // Open the file in binary read mode
    if (file == NULL) {
        char errorMsg[] = "Error accessing account data.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    struct Account user;
    
    // Loop through the file to find the account
    while (fread(&user, sizeof(struct Account), 1, file) == 1) {
        if (user.customerID == customerID) {
            char buffer[1000];
            snprintf(buffer, sizeof(buffer), "Account Balance for %s (ID: %d, Account Number: %d): ₹%.2f\n", user.name, user.customerID, user.accountNumber, user.balance);
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }
    fclose(file);
    return;
}

// Deposit money into account
void get_current_date(char* date_buffer) {
    time_t t = time(NULL); // Get the current time
    struct tm tm = *localtime(&t); // Convert to local time structure

    // Format the date into the buffer: "DD/MM/YYYY"
    sprintf(date_buffer, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void deposit_money(int connFD, int customerID) {
    char buffer[1000], amount_str[100];
    double deposit_amount;
    struct Account user;
    int found = 0;

    // Ask for the amount to deposit
    strcpy(buffer, "Enter the amount to deposit: ₹");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    
    // Reading deposit amount from the client
    int read_bytes = read(connFD, amount_str, sizeof(amount_str));
    if (read_bytes <= 0) {  // Handle failed read
        strcpy(buffer, "Error reading deposit amount.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    deposit_amount = atof(amount_str);

    // Validate deposit amount
    if (deposit_amount <= 0) {
        strcpy(buffer, "Invalid deposit amount. Must be greater than 0.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Open the account file in read/write mode to update the balance
    FILE *file = fopen(CUST_FILENAME, "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening account file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int account_fd = fileno(file);
    lock_file(account_fd, F_WRLCK);  // Acquire write lock

    // Search for the correct account
    while (fread(&user, sizeof(struct Account), 1, file)) {
        if (user.customerID == customerID) {
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Account not found.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);
        fclose(file);
        return;
    }

    // Update the account balance
    user.balance += deposit_amount;
    fseek(file, -sizeof(struct Account), SEEK_CUR); // Move file pointer back to overwrite
    fwrite(&user, sizeof(struct Account), 1, file);  // Write the updated account data

    // Log the transaction
    FILE *trans_file = fopen(TRANS_FILENAME, "a");  // Open in append mode
    if (trans_file == NULL) {
        strcpy(buffer, "Error opening transaction log file.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);
        fclose(file);
        return;
    }

    struct Transaction trans;
    trans.customerID = user.customerID;
    strcpy(trans.transactionType, "Deposit");
    trans.amount = deposit_amount;
    trans.balance = user.balance;
    strcpy(trans.transactionStatus, "Credited");

    char date[11]; // Buffer to hold the date in "DD/MM/YYYY" format
    get_current_date(date);  // Assumed function to get the current date
    strcpy(trans.date, date);

    fwrite(&trans, sizeof(struct Transaction), 1, trans_file);
    fclose(trans_file);

    // Prepare success message
    snprintf(buffer, sizeof(buffer), "Successfully deposited ₹%.2f. New balance: ₹%.2f\n", deposit_amount, user.balance);
    write(connFD, buffer, strlen(buffer));

    // Unlock the file and close
    unlock_file(account_fd);
    fclose(file);
}

// Withdraw money from account
void withdraw_money(int connFD, int customerID) {
    char buffer[1000], amount_str[100];
    double withdraw_amount;
    struct Account user;
    int found = 0;

    // Ask for the amount to withdraw
    strcpy(buffer, "Enter the amount to withdraw: ₹");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    
    // Read withdrawal amount from client
    int read_bytes = read(connFD, amount_str, sizeof(amount_str));
    if (read_bytes <= 0) {  // Handle failed read
        strcpy(buffer, "Error reading withdrawal amount.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }
    
    withdraw_amount = atof(amount_str);

    // Validate withdrawal amount
    if (withdraw_amount <= 0) {
        strcpy(buffer, "Invalid withdrawal amount. Must be greater than 0.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Open the customer file to find the customer by customerID
    FILE *file = fopen(CUST_FILENAME, "rb+");  // Open in read/write mode
    if (file == NULL) {
        strcpy(buffer, "Error opening customer file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }
    
    int account_fd = fileno(file);
    lock_file(account_fd, F_WRLCK);  // Acquire write lock

    // Find the customer by customerID
    while (fread(&user, sizeof(struct Account), 1, file)) {
        if (user.customerID == customerID) {
            found = 1;
            break; // Exit loop once customer is found
        }
    }

    if (!found) {
        strcpy(buffer, "Account not found.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }

    // Check if there are enough funds for the withdrawal
    if (user.balance < withdraw_amount) {
        strcpy(buffer, "Insufficient balance for withdrawal.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }
    
    // Update balance and write it back to the file
    user.balance -= withdraw_amount;
    fseek(file, -sizeof(struct Account), SEEK_CUR); // Move file pointer back to overwrite
    fwrite(&user, sizeof(struct Account), 1, file);  // Write the updated account data

  
    // Log the transaction
    FILE *trans_file = fopen(TRANS_FILENAME, "a");  // Open in append mode
    if (trans_file == NULL) {
        strcpy(buffer, "Error opening transaction log file.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }

    struct Transaction trans;
    trans.customerID = user.customerID;
    strcpy(trans.transactionType, "Withdrawal");
    trans.amount = withdraw_amount;
    trans.balance = user.balance;
    strcpy(trans.transactionStatus, "Debited");

    char date[11]; // Buffer to hold the date in "DD/MM/YYYY" format
    get_current_date(date);  // Assumed function to get the current date
    strcpy(trans.date, date);

    fwrite(&trans, sizeof(struct Transaction), 1, trans_file);
    fclose(trans_file);

    // Prepare success message
    snprintf(buffer, sizeof(buffer), "Successfully withdrew ₹%.2f. New balance: ₹%.2f\n", withdraw_amount, user.balance);
    write(connFD, buffer, strlen(buffer));

    // Unlock the file and close
    unlock_file(account_fd);
    fclose(file);
}

// Transfer funds from the current user's account to another user's account
void transfer_funds(int connFD, int senderID) {
    char buffer[1000], amount_str[100];
    double transfer_amount;
    struct Account sender_account, recipient_account; // Account structs for both sender and recipient
    int found_sender = 0, found_recipient = 0;
    int recipientID;

    // Ask for the recipient User ID
    snprintf(buffer, sizeof(buffer), "Enter the User ID of the recipient: ");
    write(connFD, buffer, strlen(buffer));
    bzero(buffer, sizeof(buffer));
    read(connFD, buffer, sizeof(buffer));
    recipientID = atoi(buffer);

    // Ask for the transfer amount
    snprintf(buffer, sizeof(buffer), "Enter the amount to transfer: ₹");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    read(connFD, amount_str, sizeof(amount_str));
    transfer_amount = atof(amount_str);

    // Open the account file to find the sender's account
    FILE *file = fopen(CUST_FILENAME, "rb+");
    if (file == NULL) {
        snprintf(buffer, sizeof(buffer), "Error opening account file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Lock the file before performing the transactions
    int account_fd = fileno(file);
    lock_file(account_fd, F_WRLCK);  // Acquire write lock

    // Find the sender's account
    while (fread(&sender_account, sizeof(struct Account), 1, file)) {
        if (sender_account.customerID == senderID) {
            found_sender = 1;
            break; // Exit loop once sender is found
        }
    }

    if (!found_sender) {
        snprintf(buffer, sizeof(buffer), "Sender account not found.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }

    // Check if sender has sufficient balance for the transfer
    if (sender_account.balance < transfer_amount) {
        snprintf(buffer, sizeof(buffer), "Insufficient balance in sender account.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }

    // Update balance and write it back to the file
    sender_account.balance -= transfer_amount;
    fseek(file, -sizeof(struct Account), SEEK_CUR); // Move file pointer back to overwrite
    fwrite(&sender_account, sizeof(struct Account), 1, file);  // Write the updated account data
    
    // Now, find the recipient's account
    rewind(file);  // Reset the pointer to the beginning
    while (fread(&recipient_account, sizeof(struct Account), 1, file)) {
        if (recipient_account.customerID == recipientID) {
            found_recipient = 1;
            break; // Exit loop once recipient is found
        }
    }

    if (!found_recipient) {
        snprintf(buffer, sizeof(buffer), "Recipient account not found.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);  // Release lock
        fclose(file);
        return;
    }

    // Add to recipient
    recipient_account.balance += transfer_amount;
    fseek(file, -sizeof(struct Account), SEEK_CUR); // Move file pointer back to overwrite
    fwrite(&recipient_account, sizeof(struct Account), 1, file);  // Write the updated account data

    // Log the transaction for sender
    FILE *trans_file = fopen(TRANS_FILENAME, "a");  // Open in append mode
    if (trans_file == NULL) {
        snprintf(buffer, sizeof(buffer), "Error opening transaction log file.\n");
        write(connFD, buffer, strlen(buffer));
        unlock_file(account_fd);
        fclose(file);
        return;
    }

    struct Transaction trans;

    // Log for sender
    trans.customerID = sender_account.customerID;
    strcpy(trans.transactionType, "Fund Transfer");
    trans.amount = transfer_amount;
    trans.balance = sender_account.balance;
    strcpy(trans.transactionStatus, "Debited");
    
    char date[11]; // Buffer to hold the date in "DD/MM/YYYY" format
    get_current_date(date);  // Assumed function to get the current date
    strcpy(trans.date, date);
    
    fwrite(&trans, sizeof(struct Transaction), 1, trans_file); // Log transaction for sender

    // Log for recipient
    trans.customerID = recipient_account.customerID;
    strcpy(trans.transactionType, "Fund Transfer");
    trans.amount = transfer_amount;
    trans.balance = recipient_account.balance;
    strcpy(trans.transactionStatus, "Credited");

    fwrite(&trans, sizeof(struct Transaction), 1, trans_file); // Log transaction for recipient
    fclose(trans_file);

    // Prepare success message
    snprintf(buffer, sizeof(buffer), "Successfully transferred ₹%.2f from %s (Account No: %d) to %s (Account No: %d).\n", 
             transfer_amount, sender_account.name, sender_account.accountNumber, recipient_account.name, recipient_account.accountNumber);
    write(connFD, buffer, strlen(buffer));
    
    snprintf(buffer, sizeof(buffer), "Your new balance: ₹%.2f\n", sender_account.balance); 
    write(connFD, buffer, strlen(buffer));
    
    // Unlock the file and close
    unlock_file(account_fd);
    fclose(file);
}

// Function for customer apply for loan
int generate_loan_id(){
    FILE *file = fopen(LOAN_FILENAME, "rb");  // Open in binary read mode
    if (file == NULL) {
        // If file does not exist, return 1 as the first customer ID
        return 1;
    }

    int lastID = 20241010;
    struct Loan loan;

    // Read all user accounts to find the last customer ID
    while (fread(&loan, sizeof(struct Loan), 1, file) == 1) {
        if (loan.loanID > lastID) {
            lastID = loan.loanID;  // Update lastID if current ID is higher
        }
    }

    fclose(file);
    return lastID + 1;  // Return the next customer ID
}

void apply_for_loan(int connFD, int customerID) {
    struct Account customer;
    struct Loan loan;
    //struct Loan new_loan;
    char buffer[1000];
    int accountNumber = -1;

    // Open the customer file to retrieve the accountNumber
    FILE *customer_file = fopen(CUST_FILENAME, "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customer file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the customer by customerID
    int found = 0;
    while (fread(&customer, sizeof(struct Account), 1, customer_file)) {
        if (customer.customerID == customerID) {
            found = 1;
            accountNumber = customer.accountNumber;  // Retrieve the accountNumber from the customer 
            break;
        }
    }
    fclose(customer_file);

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }
    
    FILE *loan_file = fopen(LOAN_FILENAME, "rb");  // Open read mode
    if (loan_file == NULL) {
        strcpy(buffer, "Error opening loan file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }
    
     int loanReqExists = 0 , LoanStatus;
     double LoanAmount;
     
     while (fread(&loan, sizeof(struct Loan), 1, loan_file)) {
        if (loan.customerID == customerID) {
            loanReqExists = 1;
            LoanStatus = loan.loanStatus;  // Retrieve the loan status from the customer 
            LoanAmount = loan.loanAmount;  // Retrieve the loan amount from the customer 
            break;
        }
    }
    
    fclose(loan_file);
    
     if (loanReqExists) {
        if (LoanStatus == 1) {
            sprintf(buffer, "You already have an approved loan of ₹%.2f.\nRepay the loan before applying for a new one.\n", LoanAmount);
            write(connFD, buffer, strlen(buffer));
            return;
        } 
        else if (LoanStatus == -1) {
            sprintf(buffer, "Your previous loan request for ₹%.2f is pending approval.\n", LoanAmount);
            write(connFD, buffer, strlen(buffer));
            return;
        } 
        else if (LoanStatus == 0) {
            sprintf(buffer, "Your previous loan request for ₹%.2f is rejected.\n", LoanAmount);
            write(connFD, buffer, strlen(buffer));
            return;
        }
    }

    // Ask for the loan amount
    strcpy(buffer, "Enter the loan amount: ");
    write(connFD, buffer, strlen(buffer));
    bzero(buffer, sizeof(buffer));
    read(connFD, buffer, sizeof(buffer));
    loan.loanAmount = atof(buffer);  // Convert input to double (float)

    // Fill in the loan details
    loan.customerID = customerID;
    loan.loanID = generate_loan_id();  // Generate unique loan ID
    loan.assignedEmployee = 0;  // Initially unassigned
    loan.loanStatus = -1;  // waiting for approval
    loan.accountNumber = accountNumber;  // Use retrieved accountNumber

    // Write the loan details to the .dat file
    loan_file = fopen(LOAN_FILENAME, "ab");  // Open for appending
    if (loan_file == NULL) {
        strcpy(buffer, "Error opening loan file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    fwrite(&loan, sizeof(struct Loan), 1, loan_file);  // Write the loan structure
    fclose(loan_file);

    strcpy(buffer, "Loan application submitted successfully.\n");
    write(connFD, buffer, strlen(buffer));
}

// Function for customer to add feedback
void add_customer_feedback(int connFD, int customerID) {
    struct Feedback fbEntry;
    char buffer[600]; // Buffer to store feedback input from the user

    // Ask for the feedback text from the customer
    strcpy(buffer, "Give your valuable feedback: ");
    write(connFD, buffer, strlen(buffer));

    // Clear buffer and read the feedback from the user
    bzero(buffer, sizeof(buffer));
    ssize_t bytesRead = read(connFD, buffer, sizeof(buffer) - 1);
    
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Ensure null-termination
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    } else {
        // Error handling for read failure
        strcpy(buffer, "Error reading feedback.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Fill the Feedback structure with customerID and feedback
    fbEntry.customerID = customerID;  // Set customerID directly
    strncpy(fbEntry.feedback, buffer, sizeof(fbEntry.feedback) - 1); // Copy feedback to the structure
    fbEntry.feedback[sizeof(fbEntry.feedback) - 1] = '\0'; // Ensure null-termination

    // Open the feedback file in append mode
    FILE *file = fopen(FEED_FILENAME, "ab");  // Open the file in binary append mode
    if (file == NULL) {
        strcpy(buffer, "Error opening feedback file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Write the feedback to the file
    fwrite(&fbEntry, sizeof(struct Feedback), 1, file);

    // Close the file after writing
    fclose(file);

    // Send confirmation message to the customer
    strcpy(buffer, "Thank you for your feedback!\n");
    write(connFD, buffer, strlen(buffer));
}

// Function to view user transaction history
void view_transaction_history(int connFD, int customerID) {
    char buffer[1000];
    FILE *file = fopen(TRANS_FILENAME, "rb");
    if (file == NULL) {
        strcpy(buffer, "Error loading transaction history.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    struct Transaction trans;
    int found = 0;

    // Prepare header for the transaction history
    strcpy(buffer, "\n------ Transaction History -----\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "Date: | Type: | Status: | Amount: ₹ | Balance: ₹\n");
    write(connFD, buffer, strlen(buffer));
    strcpy(buffer, "------------------------------------------------------------------\n");
    write(connFD, buffer, strlen(buffer));

    // Read the transaction file and send relevant transactions to the client
    while (fread(&trans, sizeof(struct Transaction), 1, file) == 1) {
        if (trans.customerID == customerID) {
            snprintf(buffer, sizeof(buffer), "%s | %s | %s | ₹%.2f | ₹%.2f\n", 
                     trans.date, trans.transactionType, trans.transactionStatus, 
                     trans.amount, trans.balance);
            write(connFD, buffer, strlen(buffer));
            found = 1;
        }
    }

    if (!found) {
        strcpy(buffer, "No transactions found for this customer.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

// Function to change customer password
void change_password(int connFD, int userID) {
    char buffer[1024], old_password[20], new_password[20], confirm_password[20];
    struct Account customer;
    FILE *file;

    // Open the customer.dat file in binary read/write mode
    file = fopen(CUST_FILENAME, "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening customer.dat file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the customer by userID in the .dat file
    int found = 0;
    while (fread(&customer, sizeof(struct Account), 1, file)) {
        if (customer.customerID == userID) {
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Prompt for old password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter your old password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(old_password, sizeof(old_password));
    read(connFD, old_password, sizeof(old_password));
    old_password[strcspn(old_password, "\n")] = 0;  // Remove newline character

    // Check if the old password matches
    if (strcmp(customer.pass, old_password) != 0) {
        strcpy(buffer, "Old password is incorrect.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Prompt for new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter your new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));
    new_password[strcspn(new_password, "\n")] = 0;  // Remove newline character

    // Prompt to confirm the new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Confirm your new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(confirm_password, sizeof(confirm_password));
    read(connFD, confirm_password, sizeof(confirm_password));
    confirm_password[strcspn(confirm_password, "\n")] = 0;  // Remove newline character

    // Check if new password and confirm password match
    if (strcmp(new_password, confirm_password) != 0) {
        strcpy(buffer, "New password and confirmation do not match.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Lock the file before modifying (assuming lock_file is implemented)
    int fd = fileno(file);
    lock_file(fd, F_WRLCK);  // Lock for writing

    // Update the password in the customer structure
    strncpy(customer.pass, new_password, sizeof(customer.pass) - 1);
    customer.pass[sizeof(customer.pass) - 1] = '\0';  // Ensure null-termination

    // Move file pointer to the correct position and update the record
    fseek(file, -sizeof(struct Account), SEEK_CUR);
    fwrite(&customer, sizeof(struct Account), 1, file);

    // Unlock the file after writing
    unlock_file(fd);

    // Close the file
    fclose(file);

    // Notify the user of the successful password change
    strcpy(buffer, "Password changed successfully.\n");
    write(connFD, buffer, strlen(buffer));
}

