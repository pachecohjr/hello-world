// Fig. 17.11: ClientData.cpp
// Class ClientData stores customer's credit information
#include <string>
#include <ClientData.h>

// default ClientData constructor
ClientData::ClientData (int accountNumberValue, string lastNameValue, string firstNameValue, double balanceValue)
{
 setAccountNumber (accountNumberValue);
 setLastName (lastNameValue);
 setFirstName (firstNameValue);
 setBalance (balanceValue);
} // end ClientData constructor

// get account-number value
int ClientData::getAccountNumber () const
{
 return accountNumber;
}

// set account-number value
void ClientData::setAccountNumber (int accountNumberValue)
{
 accountNumber = accountNumberValue; // should validate 
} // end function setAccountNumber

// get last-name value
string ClientData::getLastName() const
{
 return lastName; 
} // end function getLastName

// set last-name value
void ClientData::setLastName (string lastNameString)
{
  // copy at most 15 characters 
  int length = lastNameString.size();
  length = (length < 15 ? length : 14);
  lastNameString.copy(lastName, length);
  lastName[length] = '\0'; // append null character to lastName
} // end function setLastName

string ClientData::getFirstName() const
{
 return firstName; 
}

void ClientData::setFirstName (string firstNameString)
{
 // copy at most 10 characters from string
 int length = firstNameString.size();
 length = (length < 10 ? length : 9);
 firstNameString.copy(firstName, length);
 firstName[length] = '\0'; // append null character to first name
} // end function setFirstName

// get balance value
double getBalance() const
{
  return balance;
} // end function getBalance

double setBalance (double balanceValue)
{
 balance = balanceValue; // should validate 
} // end function setBalance
