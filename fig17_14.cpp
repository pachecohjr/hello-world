// Fig 17.14: fig17_14.cpp
// Reading a random-access file sequentially
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ClientData.h>

void outputLine (ostream& , const ClientData & ); // prototype

int main (void)
{
 ifstream inCredit ("credit.dat", ios::in | ios::binary);
  
  // exit program if ifstream cannot open file
  if (!inCredit)
  {
    std::cout << "File could not be opened." << std::endl;
    exit(1);
  }
  
  std::cout << std::left << std::setw(10) << "Account" << std::setw(16)
    << "Last Name" << std::setw(11) << "First Name" << std::left
    << std::setw(10) << std::right << "Balance" << std::endl;
  
  ClientData client; // create record
  
  // read first record from the file
  inCredit.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
  
  // read all records from the file
  while (inCredit && !client.eof())
  {
    // display record
    if (client.getAccountNumber() != 0)
      outputLine(std::cout, client);
    
    // read next from file
    inCredit.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
  } // end while
} // end main

void outputLine (ostream &output, const ClientData &record)
{
    output << std::left << std::setw(10) << record.getAccountNumber() 
      << std::setw(16) << record.getLastName() 
      << std::setw(11) << record.getFirstName() 
      << std::setw(10) << std::setprecision(2) << std::right << std::fixed
      << std::showpoint << record.getBalance() << std::endl;
}
