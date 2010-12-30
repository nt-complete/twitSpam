#include <twitcurl.h>
#include <iostream>

int main()
{
  twitCurl twitterObj;
  std::string userName = "ntiller";
  twitterObj.setTwitterUsername(userName);
  twitterObj.followersGet();


}
