#include <curl/curl.h>
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
#include <sqlite3.h>
#include <locale>

twitCurl twitterObj;


void authorize()
{

  std::string tmpStr( "" );
  std::string replyMsg( "" );

  /* OAuth flegins */
  /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
  twitterObj.getOAuth().setConsumerKey( std::string( "mlzPWIdVN4FACcOnaOGFA"));
  twitterObj.getOAuth().setConsumerSecret( std::string( "ywhe43wccaFahINu5jlzPjiT6V2H0UZuGyq3vXJz40"));

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
}




int main()
{
  std::string username, tmpStr;
 
  while(true)
    {
      std::cout << "Input user name: ";
      std::cin >> username;

      if(strcmp(username.c_str(), "0") == 0)
	return 0;

      twitterObj.userGet(username, false);
      twitterObj.getLastWebResponse(tmpStr);

      std::cout << tmpStr << "\n";


      TiXmlDocument xmlDoc;
      xmlDoc.Parse(tmpStr.c_str());
      TiXmlHandle xmlHandle(&xmlDoc);
  
      if(xmlHandle.FirstChild("user").ToNode())
	{
	  xmlHandle = xmlHandle.FirstChild("user");
	  if(xmlHandle.FirstChild("created_at").ToNode())
	    {
	      tmpStr = xmlHandle.FirstChild("created_at").ToElement()->GetText() ;
	      std::cout << "Created at: " << tmpStr << "\n";
	      tmpStr = xmlHandle.FirstChild("id").ToElement()->GetText() ;
	      std::cout << "ID: " << tmpStr << "\n";
	    }


	}

    }
}
