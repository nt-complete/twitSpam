#include <twitcurl.h>
#include <oauthlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <tinyxml.h>
#include <tinystr.h>
#include <sstream>
#include <vector>
#include <boost/date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <locale>
#include "user.h"


twitCurl twitterObj;




bool userCheck(TiXmlHandle userRootHandle)
{


  int userCount = 0;
  if(userRootHandle.FirstChild("user").ToNode())
    {
      userCount++;
    
      TiXmlHandle statusRootHandle = userRootHandle.FirstChild("user").FirstChild("status");
      if(statusRootHandle.ToNode())
	{
	  const char* createdAtStr = statusRootHandle.FirstChild("created_at").ToElement()->GetText();

	  if(!(createdAtStr == NULL))
	    {
	      userCount++;
	      std::string weekday, month, day, time, year, tmpStr;
	      std::stringstream ss;
	      ss << createdAtStr;
	      ss >> weekday;
	      ss >> month;
	      ss >> day;
	      ss >> time;
	      ss >> tmpStr;
	      ss >> year;

	      tmpStr = weekday + " " + month + " " + day + " " + year + " " + time;
	      
	      std::stringstream strstream;
	      strstream << tmpStr;

	      strstream.imbue(std::locale(std::locale::classic(),
				   new boost::local_time::local_time_input_facet("%a %b %d %Y " "%H:%M:%S")));


	      boost::posix_time::ptime pt;
	     
	      strstream >> pt;
	      tmpStr = strstream.str();
	      std::cout << "Date: " << tmpStr << "\n";
	      std::cout << "PTime Date: " << pt.date() << "\n";
	      std::cout << "TimeOfDay: " << pt.time_of_day() << "\n";
	    }
  
	}
    }
  return (userCount == 2);
}


int main()
{
  
  std::string tmpStr( "" );
  std::string replyMsg( "" );

  /* OAuth flegins */
  /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
  twitterObj.getOAuth().setConsumerKey( std::string( "hbmV8ajouKJxB0hl8oeow" ) );
  twitterObj.getOAuth().setConsumerSecret( std::string( "ijGXssaTltaaqPaFouVPt733mkxDnwIUSokUJxOCE"));

  /* Step 1: Check if we already have OAuth access token from a previous run */
  char szKey[1024];
  std::string myOAuthAccessTokenKey("");
  std::string myOAuthAccessTokenSecret("");
  std::ifstream oAuthTokenKeyIn;
  std::ifstream oAuthTokenSecretIn;

  oAuthTokenKeyIn.open( "twitClient_token_key.txt" );
  oAuthTokenSecretIn.open( "twitClient_token_secret.txt" );

  memset( szKey, 0, 1024 );
  oAuthTokenKeyIn >> szKey;
  myOAuthAccessTokenKey = szKey;

  memset( szKey, 0, 1024 );
  oAuthTokenSecretIn >> szKey;
  myOAuthAccessTokenSecret = szKey;

  oAuthTokenKeyIn.close();
  oAuthTokenSecretIn.close();
    
  if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
    {
      /* If we already have these keys, then no need to go through auth again */
      std::cout << "\nUsing:\nKey: " << myOAuthAccessTokenKey.c_str() << "\nSecret: " << myOAuthAccessTokenSecret.c_str() << "\n\n";
 
      twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
      twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
  else
    {
      /* Step 2: Get request token key and secret */
      twitterObj.oAuthRequestToken( tmpStr );

      /* Step 3: Ask user to visit web link and get PIN */
      char szOAuthVerifierPin[1024];
      memset( szOAuthVerifierPin, 0, 1024 );
      std::cout << "\nPlease visit this link in web browser and authorize this application:\n" << tmpStr.c_str();
      std::cout << "\nEnter the PIN provided by twitter: " ;
      std::cin >> szOAuthVerifierPin;
      tmpStr = szOAuthVerifierPin;
      twitterObj.getOAuth().setOAuthPin( tmpStr );

      /* Step 4: Exchange request token with access token */
      twitterObj.oAuthAccessToken();

      /* Step 5: Now, save this access token key and secret for future use without PIN */
      twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
      twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );


      /* Step 6: Save these keys in a file or wherever */
      std::ofstream oAuthTokenKeyOut;
      std::ofstream oAuthTokenSecretOut;

      oAuthTokenKeyOut.open( "twitClient_token_key.txt" );
      oAuthTokenSecretOut.open( "twitClient_token_secret.txt" );

      oAuthTokenKeyOut.clear();
      oAuthTokenSecretOut.clear();

      oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
      oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

      oAuthTokenKeyOut.close();
      oAuthTokenSecretOut.close();
    }
  /* OAuth flow ends */

  std::string userStr = "ntiller";

  
  twitterObj.userGet(userStr);
  
  twitterObj.getLastWebResponse(userStr);



  TiXmlDocument userDoc;
  userDoc.Parse(userStr.c_str());


  TiXmlHandle userRoot(&userDoc);

  TiXmlHandle userRootHandle = userRoot.FirstChild("user");
  //  std::cout << userStr;



  
  //  std::cout << primUser << "\n";

  std::cout << "BEGIN: \n";
  /***        Followers           ***

  twitterObj.followersGet();

  std::string followersStr;
  twitterObj.getLastWebResponse(followersStr);


  TiXmlDocument followersDoc;
  followersDoc.Parse(followersStr.c_str());
  TiXmlHandle followersRootHandle(&followersDoc);
  //  std::cout << followersStr ;
  std::cout << "BEGIN: \n";
    primUser.setFollowers(followersRootHandle);

    /***         Friends             **
  std::cout << "BEGIN: \n";
  twitterObj.friendsGet();

  
  std::string friendsStr;
  twitterObj.getLastWebResponse(friendsStr);
  std::cout << "BEGIN: \n";

  //  std::cout << friendsStr;
  TiXmlDocument friendsDoc;
  friendsDoc.Parse(friendsStr.c_str());
  TiXmlHandle friendsRootHandle(&friendsDoc);
    std::cout << "BEGIN: \n";
  primUser.setFriends(friendsRootHandle);

  //  std::cout << primUser.printFriendNames();
  

  
  
  std::cout << "BEGIN: \n";
  tmpStr = "uotwitspam";
  twitterObj.userGet(tmpStr);

  twitterObj.getLastWebResponse(userStr);

  //  std::cout << userStr;

  */

  

  long maxIdNum = 235314984;

  srand48(time(NULL));




  double randNum = drand48();

  long idNum = maxIdNum * randNum;
  std::stringstream ss;
  ss << idNum;



  tmpStr = ss.str();
  //      tmpStr = "60239787";
  twitterObj.userGet(tmpStr, true);
  twitterObj.getLastWebResponse(tmpStr);
      
  TiXmlDocument tmpDoc;
  tmpDoc.Parse(tmpStr.c_str());
      

  std::cout << tmpStr;
  TiXmlHandle tmpRoot(&tmpDoc);
  userCheck(tmpRoot);
  /* if(!userCheck(tmpRoot))
    {
      //	  std::cout << ss.str() << "\n";
      //	  std::cout << tmpStr;
    }
  else
    {
      std::cout << i << ", ";
      i++;
    }
  */



  return 0;
}



