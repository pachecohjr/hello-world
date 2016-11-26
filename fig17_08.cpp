// Fig. 17.8: Fig17_08.cpp
// Credit inquiry program
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

enum RequestType {ZERO_BALANCE = 1, CREDIT_BALANCE, DEBIT_BALANCE, END};
int  getRequest();
bool shouldDisplay (int , double );
void outputLine (int , const string , double );

int main (void)
{
  // ifstream constructor opens file
  ifstream inClientFile ("clients.dat", ios::in);
  
  // exit program if ifstream could not open file
  if (!inClientFile)
  {
   std::cerr << "Could not open file" << std::endl;
   exit(1); 
  }
  
  int account;
  string name;
  double balance;
  
  request = getRequest();
  
  while (request != END)
  {
    switch (request)
    {
     case ZERO_BALANCE:
       std::cout << "\nAccounts with zero balances\n";
       break;
     case CREDIT_BALANCE:
       std::cout << "\nAccounts with credit balances\n";
       break;
     case DEBIT_BALANCE:
       std::cout << "\nAccounts with debit balances\n";
       break;  
    } // end switch
    
    // read account, name, and balance from file
    inClientFile >> account >> name >> balance;
    
    while (!inClientFile.eof())
    {
      // display record
      if (shouldDisplay (request, balance))
        outputLine (account, name, balance);
      
      // read account, name, and balance from file
      inClientFile >> account >> name >> balance;
    } // end inner while
    
    inClientFile.clear(); // reset eof for next input
    inClientFile.seekg(0); // reposition to begining of file
    request = getRequest(); // get additional request from user
  } // end outer while
  
  std::cout << "End of run." << std::endl;
} // end main

// obtain request from user
int getRequest()
{
 int request; // get request from user
  
  // display request options
  std::cout << "\nEnter request" << std::endl
  " 1 - List accounts with zero balances" << std::endl
  " 2 - List accounts with credit balances" << std::endl
  " 3 - List accounts with debit balances" << std::endl
  " 4 - End of run" << std::fixed << std::showpoint;
  
  // input user request
  do 
  { 
    std::cout << "\n?";
    std::cin  >> request;
  } while (request < ZERO_BALANCE && request > END);
  
  return request;
} // end function request

// determine whether to display given record
bool shouldDisplay (int type, double balance)
{
 // determine whether to display zero balances
 if (type == ZERO_BALANCE && balance == 0)
   return true;
  
 // determine whether to display credit balances 
 if (type == CREDIT_BALANCE && balance < 0) 
   return true;
  
 // determine whether to display debit balances
 if (type == DEBIT_BALANCE && balance > 0)
   return true;
  
 return false;
} // end function shouldDisplay

// display single record from file
void outputLine (int account, const string name, double balance)
{
   std::cout << left << std::setw(10) << account << std::setw(13)
  << name << std::setw(7) << std::setprecision(2) << std::right << balance << std::endl; 
} // end function outputLine
