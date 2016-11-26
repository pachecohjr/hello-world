// Fig. 17.13: Fig17_13.cpp
// Writing to a random-access file.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ClientData.h>

int main (void)
{
 int accountNumber;
 string lastName;
 string firstName;
 double balance;
  
 fstream outCredit ("credit.dat", ios::in | ios::out | ios::binary);
  
 // exit program if fstream cannot open file
 if (!outCredit)
 {
   std::cerr << "File could not be opened." << std::endl;
   exit(1);
 }
  
  std::cout << "Enter account number (1 to 100, 0 to end input).\n? ";
  
  // require user to specify account #
  ClientData client;
  std::cin >> accountNumber;
  
  // user enters information, which is copied into filed
  while (accountNumber > 0 && accountNumber <= 100)
  {
    // user enters last name, first name, and balance
    std::cout << "Enter lastname, firstname, and balance\n? ";
    std::cin >> lastName;
    std::cin >> firstName;
    std::cin >> balance;
    
    // set record accountNumber, last name, first name, and balance values
    client.setAccountNumber(accountNumber);
    client.setLastName(lastName);
    client.setFirstName(firstName);
    client.setBalance(balance);
    
    // seek position in file of user-specified record
    outCredit.seekp((client.getAccountNumber() - 1) * sizeof(ClientData));
    
    // write user-specified information in file
    outCredit.write(reinterpret_cast <const char *>(&client), sizeof(ClientData));
    
    // enable user to enter another account
    std::cout << "Enter another account:\n? ";
    std::cin >> accountNumber;
  } // end while
} // end main
