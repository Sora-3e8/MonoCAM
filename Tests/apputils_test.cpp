#include "app_utils.h"
#include <iostream>
int int main (int argc, char *argv[]) 
{
  try
  {
    std::string date = app_utils::datetime("%m/%d/%Y %H:%M");
    std::cout << date << std::endl;
  }
  catch(std::exception &e)
  {
    std::cout << "app_utils::datetime() failed with error:" <<"\n\t" << e.what() << std::endl;
    return 1;
  }
  return 0;
}
