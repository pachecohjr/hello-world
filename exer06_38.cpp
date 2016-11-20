// program that performs Towers of Hanoi using recursion

#include <iostream>

void towersofHanoi (int, char, char, char);

int main (void)
{
  int n; // variable represents number of disks
  
  // Prompt user
  std::cout << "A recursion program to perform the Tower of Hanoi: ";
  std::cout << "\nEnter the number of disks: ";
  std::cin  >> n;
  
  // call recursive function towersofHanoi
  towersofHanoi (n, '1', '2', '3');
  
  return 0;
}

void towersofHanoi (int n, char peg1, char peg2, char peg3)
{
 if (n != 0)
 {
   // recursively call
   towersofHanoi (n - 1, peg1, peg3, peg2);
  
   std::cout << "Move of disk " << n << " is " << peg1 << "->" << peg3 << std::endl;
   
   // recursively call
   towersofHanoi (n - 1, peg2, peg1, peg3);
 }
}
