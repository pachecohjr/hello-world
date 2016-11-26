// Fig 17.12: fig17_12.cpp
// Creating a randomly accessed file.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ClientData.h>

int main (void)
{
  ofstream outCredit ("credit.dat", ios::out | ios::binary);
  
  // exit program if ofstream could not open file
  if (!outCredit)
  {
    std::cerr << "File could not opened." << std::endl;
    exit(1);
  } // end if
  
  ClientData blankClient; // constructor zeros out each data member
  
  // output 100 blank records to a file
  for (int i = 0; i < 100; ++i)
    outCredit.write(reinterpret_cast<const char *>(&blankClient), sizeof(ClientData));
} // end main
