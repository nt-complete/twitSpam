#include <curl/curl.h>
#include <iostream>

class Curler
{
 public:
  std::string getUserInfo(std::string);
 private:
  char errorBuffer[CURL_ERROR_SIZE];  
  std::string buffer;  
};

  int writer(char *data, size_t size, size_t nmemb,  
		    std::string *buffer);
