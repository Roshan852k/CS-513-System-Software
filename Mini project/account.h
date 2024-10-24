#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_TRANSACTIONS 10
#define MAX_TRANSACTION_LEN 256

// Structure for Account Information
struct Account {
    int customerID;      // Added customerID
    char name[50];
    char pass[50];
    float balance;
    int accountNumber;   // Added accountNumber
    int status;          // 1 for Active, 0 for Deactivated
};

// Function Prototypes
void customer_login(int connFD);
void customer_menu(int connFD,int userID);
void view_account_balance(int connFD,int userID);
void deposit_money(int connFD,int userID);
void withdraw_money(int connFD,int userID);
void transfer_funds(int connFD,int userID);
void apply_for_loan(int connFD,int userID);
void change_password(int connFD,int userID);
void add_customer_feedback(int connFD,int userID);
//void view_transaction(int connFD,int userID);
void view_transaction_history(int connFD,int userID);

void customer_logout(int connFD, int userID);
// Helper function
int authenticate_customer(int userID, const char *password);
void remove_user_from_session(int userID);


#endif
