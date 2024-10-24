struct Feedback {
    int customerID;         // Unique ID for the customer
    char feedback[100];     // Feedback message
};

void add_customer_feedback(int connFD, int userID);
