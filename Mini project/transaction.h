struct Transaction {
    int customerID;
    char date[11]; 
    char transactionType[20];  // Deposit, Withdrawal, Transfer 
    float amount;
    float balance;
    char transactionStatus[20]; // Credited, Debited
};
