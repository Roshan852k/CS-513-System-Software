// session.h
#ifndef SESSION_H
#define SESSION_H

int is_user_logged_in(int userID);
void add_user_to_session(int userID);
void remove_user_from_session(int userID);

#endif

