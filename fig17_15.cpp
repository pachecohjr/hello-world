// Fig 17.15: fig17_15.cpp
// This program reads a random-access file sequentially, updates
// data previously written to the file, creates data to be placed
// in the file, and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ClientData.h>

int enterChoice();
void createTextFile (fstream& );
void updateRecord (fstream& );
void newRecord (fstream& );
void deleteRecord (fstream& );
void outputLine (ostream& , const ClientData & );
int getAccount (const char * const);

enum Choices {PRINT = 1, UPDATE, NEW, DELETE, END};

int main (void)
{
  // open file for reading and writing
  fstream inOutCredit ("credit.dat", ios::in | ios::out | ios::binary);
  
  // exit program if fstream cannot open from file
  if (!inOutCredit)
  {
    std::cerr << "File could not be opened." << std::endl;
    exit(1);
  } // end if
  
  int choice; // store user choice
  
  // enable user to specify action
  while ( (choice = enterChoice()) != END)
  {
    switch (choice)
    {
      case PRINT: // create text file from record file
        createTextFile(inOutCredit);
        break;
      case UPDATE:
        updateRecord(inOutCredit); // update record
        break;
      case NEW:
        newRecord(inOutCredit); // create record
        break;
      case DELETE:
        deleteRecord(inOutCredit); // delete existing record from file
        break;
      default: // display error if user does not make correct choice
        std::cout << "Incorrect choice" << std::endl;
    } // end switch
    
    inOutCredit.clear(); // reset end-of-file indicator
  } // end while
} // end main

// enable user to input menu choice
int enterChoice()
{
  // display available options
  std::cout << "\nEnter your choice" << std::endl
    << "1 - store a formatted text file of account" << std::endl
    << "    called a \"print.txt\" for printing " << std::endl
    << "2 - update an account" << std::endl
    << "3 - create a new account" << std::endl
    << "4 - delete an account" << std::endl
    << "5 - end program\n? ";
  
  int menuChoice;
  std::cin >> menuChoice; // input menu selection from user
  return menuChoice;
} // end function enterChoice

// create formatted text file for printing
void createTextFile (fstream &readFromFile)
{
  // create text file
  ofstream outPrintFile ("print.txt", ios::out);
  
  // exit program if ofstream cannot create file
  if (!outPrintFile)
  {
    std::cerr << "File could not be created." << std::endl;
    exit(1);
  } // end if
  
    outPrintFile << std::left << std::setw(10) << "Account" << std::setw(16)
    << "Last Name" << std::setw(11) << "First Name" << std::left
    << std::setw(10) << std::right << "Balance" << std::endl;
  
  // set file-position pointer to beginning of readFromFile
  readFromFile.seekg(0);
  
  // read first record from record file
  ClientData client;
  readFromFile.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
  
  // copy all records from record file into text file
  while (!readFromFile.eof())
  {
    // write single record to text file
    if (client.getAccountNumber() != 0)
      outputLine(outPrintFile, client);
    
    // read next record from record file
    readFromFile.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
  } // end while
} // end function createTextFile

// update balance in record
void updateRecord (fstream &updateFile)
{
  // obtain number of account to update
  int accountNumber = getAccount("Enter account to update");
  
  // move file-position pointer to correct record in file
  updateFile.seekg((accountNumber - 1) * sizeof(ClientData));
  
  // read first record from file
  ClientData client;
  updateFromFile.read(reinterpret_cast<char *>(&client),
                      sizeof(ClientData));
  
  if (client.getAccountNumber() != 0)
  {
   outputLine(std::cout, client); // display the record
    
   // request user to specify transaction
    std::cout << "\nEnter charge (+) or payment (-): ";
    double transaction; // charge or payment
    std::cin >> transaction;
    
   // update record balance
    double oldBalance = client.getBalance();
    client.setBalance(oldBalance + transaction);
    outputLine (std::cout, client); // display the record
    
   // move file-position pointer to correct record in file
    updateFile.seekp((accountNumber - 1) * sizeof(ClientData));
    
   // write updated record over old record in file
    updateFile.write(reinterpret_cast<const char *>(&client),
                     sizeof(ClientData));
  } // end if
  else
    std::cerr << "Account #" << accountNumber << " has no information." << std::endl;
} // end function updateRecord

void newRecord (fstream &insertFile)
{
  // obtain number of account to create
  int accountNumber = getAccount("Enter new account number");
  
  // move file-position pointer to correct record in file
  insertFile.seekg((accountNumber - 1) * sizeof(ClientData));
  
  // read record from file
  ClientData client;
  insertFile.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
  
  // create record, if record does not previously exist
  if (client.getAccountNumber() == 0)
  {
    string lastName;
    string firstName;
    double balance;
    
    // user enters last name, first name, and balance
    std::cout << "Enter lastname, firstname, and balance\n? ";
    std::cin >> std::setw(15) >> lastName;
    std::cin >> set::setw(15) >> firstName;
    std::cin >> balance;
    
    // use values to populate account values
    client.setLastName(lastName);
    client.setFirstName(firstName);
    client.setBalance(balance);
    client.setAccountNumber(accountNumber);
    
    // move file pointer to correct record in file
    insertFile.seekp((accountNumber - 1) * sizeof(ClientData));
    
    // insert record into file
    insertFile.write(reinterpret_cast<const char *>(&client),
                     sizeof(ClientData));
    
  } // end if
  else // display error if account already exists
    std::cerr << "Account #" << accountNumber << " already contains information. " << std::endl;
} // end function newRecord

void deleteRecord (fstream &deleteFromFile)
{
  // obtain number of account to delete
  int accountNumber = getAccount ("Enter account to delete");
  
  // move file-position pointer to correct record in file
  deleteFromFile.seekg((accountNumber - 1) * sizeof(ClientData));
  
  // read record from file
  ClientData client;
  deleteFromFile.read(reinterpret_cast<char *>(&client),
                      sizeof(ClientData));
  
  // delete record, if record exists in file
  if (client.getAccountNumber() != 0)
  {
    ClientData blankClient; // create blank record
    
    // move file-position pointer to correct record from file
    deleteFromFile.seekp( (accountNumber - 1) * sizeof(ClientData));
    
    // replace existing record with blank record
    deleteFromFile.write(reinterpret_cast<const char *>(&blankClient), sizeof(ClientData));
    
    std::cout << "Account #" << accountNumber << " deleted.\n";
  } // end if
  else // display error if record does not exist
    std::cerr << "Account #" << accountNumber << " is empty.\n";
} // end deleteRecord


void outputLine (ostream &output, const ClientData &record)
{
    output << std::left << std::setw(10) << record.getAccountNumber() 
      << std::setw(16) << record.getLastName() 
      << std::setw(11) << record.getFirstName() 
      << std::setw(10) << std::setprecision(2) << std::right << std::fixed
      << std::showpoint << record.getBalance() << std::endl;
}

int getAccount (const char * const prompt)
{
  int accountNumber;
  
  // obtain account-number value
  do
  {
  std::cout << prompt << " (1 - 100): ";
  std::cin  >> accountNumber;
  } while (accountNumber < 1 || accountNumber > 100);
  
  return accountNumber;
}
