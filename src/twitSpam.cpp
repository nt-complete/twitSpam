#include <twitcurl.h>
#include <oauthlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main()
{
  twitCurl twitterObj;

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
      printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

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
      printf( "\nPlease visit this link in web browser and authorize this application:\n%s", tmpStr.c_str() );
      printf( "\nEnter the PIN provided by twitter: " );
      gets( szOAuthVerifierPin );
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



  std::string userName = "ntiller";
  twitterObj.setTwitterUsername(userName);
  std::string userPwd = "37nst35";
  twitterObj.setTwitterPassword(userPwd);

  twitterObj.followersGet();

  std::string followersStr;
  twitterObj.getLastWebResponse(followersStr);

  std::cout << followersStr << "\n";

}
