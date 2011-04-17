#include <curl/curl.h>
#include "curler.h"


extern int writer(char *data, size_t size, size_t nmemb,  
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

std::string Curler::getTweetInfo(std::string username, std::string tweetId)
{

  std::string urlStr = "www.twitter.com/#!/" + username + "/statuses/" + tweetId;

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

      if(result != CURLE_OK)
	{  
	  std::cout << "Error: [" << result << "] - " << errorBuffer;  
	}  

    }

  return buffer;

}

std::string Curler::getUserInfo(std::string username)
{

  std::string urlStr = "www.twitter.com/users/" + username;

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

      if(result != CURLE_OK)
	{  
	  std::cout << "Error: [" << result << "] - " << errorBuffer;  
	}  

    }

  return buffer;

}

