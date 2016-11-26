// Fig 17.7: Fig17_07.cpp
// Reading and printing a sequential file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

void outputLine (int, const string, double); // prototype

int main (void)
{
  
  // ifstream constructor opens the file
  ifstream inClientFile("clients.dat", ios::in);
  
  // exit program if ifstream could not open file
  if (!inClientFile)
  {
   std::cerr << "File could not  be opened" << std::endl;
   exit(1);
  } // end if
  
  int account;
  string name;
  double balance;
  
  std::cout << left << std::setw(10) << "Account" << std::setw(13)
    << "Name" << "Balance" << std::endl << std::fixed << std::showpoint;
  
  // display each record in file
  while (inClientFile >> account >> name >> balance)
    outputLine (account, name, balance);
} // end main

// display single record from file
void outputLine (int account, string name, double balance)
{
  std::cout << left << std::setw(10) << account << std::setw(13)
  << name << std::setw(7) << std::setprecision(2) << std::right << balance << std::endl;
} // end function outputLine
