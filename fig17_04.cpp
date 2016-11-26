// Fig 17.4: Fig17_04.cpp
// Create a sequential file
#include <iostream>
#include <string>
#include <fstream> // file stream
#include <cstdlib>

int main (void)
{
  
  // ofstream constructor opens file
  ofstream outClientFile ( "clients.dat", ios::out);
  
  // exit program if unable to create file
  if (!outClientFile)
  {
    std::cerr << "File could not be opened" << std::endl;
    exit(1);
  }
  
  std::cout << "Enter the account, name, and balance." << std::endl
    << "Enter end-of-file to end input. \n?;
    
  int account;
  string name;
  double balance;
  
  // read account, name, and balance from std::cin, then place in file
  while (std::cin >> account >> name >> balance)
  {
   outClientFile << account << ' ' << name << ' ' << balance << std::endl;
   std::cout << "?";
  } // end while
} // end main
