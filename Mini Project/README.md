Compilation command for MAC if openssl import doesn't work :
gcc -o banking_system account.c customer.c employee.c feedback.c loan.c main.c manager.c transaction.c user.c admin.c -I/opt/homebrew/Cellar/openssl@3/3.3.2/include -L/opt/homebrew/Cellar/openssl@3/3.3.2/lib -lssl -lcrypto -pthread

server : ./banking_system
client(s) : telnet localhost 8080 (telnet needs to be installed)
