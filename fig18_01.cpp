// Fig. 18.1: Fig18_01.cpp
// Demonstrating string assignment and concatenation.

#include <iostream>
#include <string>

int main (void)
{
  string string1("cat");
  string string2; // initialized to the empty string
  string string3; // initialized to the empty string
  
  string2 = string1;
  string3.assign(string1);
  std::cout << "string1: " << string1 << "\nstring2: " << string2
    << "\nstring3: " << string3 << "\n\n";
  
  // modify string2 and string3
  string2[0] = string3[2] = 'r';
  
  std::cout << "After modification of string2 and string3:\n" << "string1: "
    << string1 << "\nstring2: " << string2 << "\nstring3: ";
  
  // demonstrating member function at
  for (int i = 0; i < string3.length(); ++i)
    std::cout << string3.at(i);
  
}
