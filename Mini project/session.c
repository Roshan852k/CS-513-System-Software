// session.c
#include <stdio.h>
#include "session.h"
#include <stdlib.h>  // Required for atoi
#include <string.h>  // Required for strtok

int is_user_logged_in(int userID) {
    FILE *session_file = fopen("session.txt", "r");
    if (session_file == NULL) {
        return 0; // If session.txt doesn't exist, assume no one is logged in
    }

    int id;
    while (fscanf(session_file, "%d", &id) != EOF) {
        if (id == userID) {
            fclose(session_file);
            return 1; // User is already logged in
        }
    }

    fclose(session_file);
    return 0; // User is not logged in
}

void add_user_to_session(int userID) {
    FILE *session_file = fopen("session.txt", "a");
    if (session_file == NULL) {
        printf("Error opening session.txt\n");
        return;
    }

    fprintf(session_file, "%d\n", userID); // Add the userID to session.txt
    fclose(session_file);
}

void remove_user_from_session(int userID) {
    FILE *session_file = fopen("session.txt", "r");
    if (session_file == NULL) {
        printf("Error opening session.txt\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temp file\n");
        fclose(session_file);
        return;
    }

    char line[1000]; // Buffer to hold the entire line of IDs

    // Read the entire line of user IDs
    if (fgets(line, sizeof(line), session_file) != NULL) {
        // Tokenize the line by spaces
        char *token = strtok(line, " ");
        
        while (token != NULL) {
            int id = atoi(token); // Convert token to integer
            printf("%d %d",id,userID);
            if (id != userID) {
                fprintf(temp_file, "%d ", id); // Write to temp file if it's not the one to remove
            }
            token = strtok(NULL, " "); // Get the next token
        }
        fprintf(temp_file, "\n"); // End the line in the temp file
    }

    fclose(session_file);
    fclose(temp_file);
    
    remove("session.txt"); // Remove old session.txt
    rename("temp.txt", "session.txt"); // Rename temp.txt to session.txt
}



