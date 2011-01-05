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
#include "user.h"


twitCurl twitterObj;


/*
bool mutualFriends(long id1, long id2)
{
  bool friend1, friend2;
  std::string str;
  friend1 = friend2 = false;
  
  twitterObj.userGet(id1, true);

  twitterObj.getLastWebResponse(str);

  std::cout << str;
  return true;
}*/




using namespace std;
int main()
{
  
  std::string tmpStr( "" );
  std::string replyMsg( "" );

  /* OAuth flegins */
  /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
  twitterObj.getOAuth().setConsumerKey( std::string( "hbmV8ajouKJxB0hl8oeow" ) );
  twitterObj.getOAuth().setConsumerSecret( std::string( "ijGXssaTltaaqPaFouVPt733mkxDnwIUSokUJxOCE" ) );

  /* Step 1: Check if we alredy have OAuth access token from a previous run */
  char szKey[1024];
  std::string myOAuthAccessTokenKey("");
  std::string myOAuthAccessTokenSecret("");
  std::ifstream oAuthTokenKeyIn;
  std::ifstream oAuthTokenSecretIn;

  oAuthTokenKeyIn.open( "twitterClient_token_key.txt" );
  oAuthTokenSecretIn.open( "twitterClient_token_secret.txt" );

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
      ofstream oAuthTokenKeyOut;
      ofstream oAuthTokenSecretOut;

      oAuthTokenKeyOut.open( "twitterClient_token_key.txt" );
      oAuthTokenSecretOut.open( "twitterClient_token_secret.txt" );

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

  User primUser(userRootHandle);
  std::cout << primUser << "\n";
  std::cout << userStr << "\n";
  //***        Followers           ***//

  twitterObj.followersGet();

  std::string followersStr;
  twitterObj.getLastWebResponse(followersStr);


  TiXmlDocument followersDoc;
  followersDoc.Parse(followersStr.c_str());
  TiXmlHandle followersRootHandle(&followersDoc);
  primUser.setFollowers(followersRootHandle);

  //***         Friends             ***//

 
  twitterObj.friendsGet();

  std::string friendsStr;
  twitterObj.getLastWebResponse(friendsStr);

  //  std::cout << friendsStr;
  TiXmlDocument friendsDoc;
  friendsDoc.Parse(friendsStr.c_str());
  TiXmlHandle friendsRootHandle(&friendsDoc);
  
  primUser.setFriends(friendsRootHandle);
  
  //  std::cout << primUser.printFriendNames();
  

  twitCurl nellObj;

  tmpStr = "128346877";
  nellObj.userGet(tmpStr, true);

  nellObj.getLastWebResponse(userStr);

  //  std::cout << userStr;

  TiXmlDocument tmpDoc;
  tmpDoc.Parse(userStr.c_str());

  TiXmlHandle tmpRoot(&tmpDoc);


  tmpStr = "16369144";
  nellObj.friendsGet(tmpStr, true);
  nellObj.getLastWebResponse(tmpStr);
  //  std::cout << tmpStr;



  if(nellObj.friendsGet(tmpStr, true))
    {
      std::cout << "Should not be true.";
      nellObj.getLastWebResponse(userStr);
      //      std::cout << userStr;
    }
  else
    {
      std::cout << "TRUE. Perfect.";
    }

  return 0;
}
