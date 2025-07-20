#include <string>
#include <ctime>
#include <iostream>
class apputils
{
  public:
    static std::string datetime(const char* format);

    class osutils
    {
      public:
        static std::string OSNAME();
        static std::string OSTYPE();
        static std::string HOMEDIR();
    };

};
