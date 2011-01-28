#include <curl/curl.h>
#include <oauthlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <tinyxml.h>
#include <tinystr.h>
#include <sstream>
#include <vector>
#include <sqlite3.h>
#include <locale>


static char errorBuffer[CURL_ERROR_SIZE];  
  
// Write all expected data in here  
static std::string buffer;  
  
// This is the writer call back function used by curl  
static int writer(char *data, size_t size, size_t nmemb,  
                  std::string *buffer)  
{  
  // What we will return  
  int result = 0;  
  
  // Is there anything in the buffer?  
  if (buffer != NULL)  
  {  
    // Append the data to the buffer  
    buffer->append(data, size * nmemb);  
  
    // How much did we write?  
    result = size * nmemb;  
  }  
  
  return result;  
}  
  
// You know what this does..  
void usage()  
{  
  std::cout << "curltest: \n" << "\n";  
  std::cout << "  Usage:  curltest url\n" << "\n";  
}   



int main()
{
  long maxIdNum = 235314984;

  srand48(time(NULL));

  long randomUser = drand48();
  std::stringstream ss;

  randomUser = 16369144;

  ss << randomUser;
  std::string tmpStr;
  ss >> tmpStr;
  std::cout << tmpStr << "\n";
  std::string urlStr = "www.twitter.com/users/" + tmpStr;

  std::cout << urlStr << "\n";

  CURL *curl;
  CURLcode result;

  curl = curl_easy_init();
  
  if(curl)
    {

      curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);  
      curl_easy_setopt(curl, CURLOPT_URL, urlStr.c_str());
      curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);  

      result = curl_easy_perform(curl);

      curl_easy_cleanup(curl);

      if(result == CURLE_OK)
	{
	  std::cout << buffer << "\n";
	  exit(0);
	}
      else  
	{  
	  std::cout << "Error: [" << result << "] - " << errorBuffer;  
	  exit(-1);  
	}  
	


    }



}
