// Fig 16.3: 
// Demonstrating exception throwing.
#include <iostream>
#include <exception>

// throw, catch, and rethrow exception
void throwException()
{
 // try exception and catch it immediately
  try
  {
   std::cout << "    Function throwException throws an exception\n";
    throw exception();
  } // end try
  catch (exception& ) // handle exception
  {
    std::cout << "  Exception handled in function throwException"
      << "\n Function throwException rethrows exception";
    throw; // rethrow exception for further processing
  } // end catch
  
  std::cout << "This also should not print \n";
} // end function throwException

int main (void)
{
 // throw exception
  try
  {
    std::cout << "\nmain invokes function throwException\n";
    throwFunction();
    std::cout << "This should not print\n";
  } // end try
  catch (exception & ) // handle exception
  {
    std::cout << "\n\nException handled in main\n";  
  } // end catch
  std::cout << "Program control continues after catch in main \n\n";
} // end
