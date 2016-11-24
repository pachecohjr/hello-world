// Fig 16.1: DividebyZeroException.h
// Class DivideByZero exception
#include <stdexcept> // stdexcept header file contains runtime_error

// DividebyZeroException objects should be thrown by functions
// upon detecting division-by-zero exceptions
class DivisionbyZeroException
{
  public:
  // constructor specifies default error message
  DividebyZeroException()
    : runtime_error("attempted to divide by zero") {}
}; // end class DivisionbyZeroException

// Fig 16.2: Fig16_02.cpp
// A simple exception-handling example that checks for
// divide-by-zero exceptions
#include <iostream>
#include "DivisionbyZeroException.h"

// perform division and throw DividebyZeroException object if
// divide-by-zero exception occurs
double quotient (int numerator, int denominator)
{
 // throw DividebyZeroException if trying to divide by zero
  if (denominator == 0)
    throw DividebyZeroException();
  
  // return division result
  return static_cast<double>(numerator)/denominator;
} // end function quotient

int main (void)
{
  int number1; // user-specified numerator
  int number2; // user-specified denominator
  double result; // result of division
  
  std::cout << "Enter two integers (end-of-file to end): ";
  
  // enable user to enter two integers to divide
  while (std::cin >> number1 >> number2)
  {
   try
   {
     // try block contains code that might throw exception
     // and code that should not execute if an exception occurs
     result = quotient(number1, number2);
     std::cout << "The quotient is " << result << std::endl;
   } // end try
    catch (DividebyZeroException &divideByZeroException)
   {
     std::cout << "Exception occurred: " << divideByZeroException.what() << std::endl;
   } // end catch
    
    std::cout << "\nEnter two integers (end-of-file to end): ";
  } // end while
} // end main
