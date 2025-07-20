#include "app_utils.h"

std::string apputils::osutils::OSNAME()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

std::string apputils::osutils::OSTYPE()
{

  if(apputils::osutils::OSNAME().find("Windows")!=std::string::npos)
  {
    return "NT";
  }
  if(apputils::osutils::OSNAME().find("Linux")!=std::string::npos)
  {
    return "UNIX";
  }
  if(apputils::osutils::OSNAME().find("FreeBSD")!=std::string::npos)
  {
    return "UNIX";
  }
  if(apputils::osutils::OSNAME().find("Unix")!=std::string::npos)
  {
    return "UNIX";
  }

  if(apputils::osutils::OSNAME().find("Mac OSX")!=std::string::npos)
  {
    return "UNIX";
  }

  return "UNKNOWN";
}

std::string apputils::osutils::HOMEDIR()
{

  if(apputils::osutils::OSTYPE()=="NT")
  {
    const char* homedrive = getenv("HOMEDRIVE");
    const char* homepath = getenv("HOMEPATH");
    return (homedrive == NULL || homepath == NULL) ? "" : std::string(homedrive)+std::string(homepath);
  }
  else if(apputils::osutils::OSTYPE()=="UNIX")
  {
    const char* homedir = getenv("HOME");
    return (homedir == NULL) ? "": std::string(homedir);
  }

  return "";
}

