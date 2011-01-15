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
#include <boost/date_time/gregorian/gregorian.hpp>
#include <sqlite3.h>
#include <locale>
#include "user.h"


twitCurl twitterObj;

#define DEBUG 1


bool userCheck(TiXmlHandle userRootHandle, TiXmlHandle timelineRootHandle)
{
  std::string weekday, month, day, time, year, tmpStr;

  std::stringstream ss;
  std::stringstream strstream;
  boost::posix_time::ptime ptime, pt, currentTime, mostRecentTweetTime;
  boost::posix_time::time_duration hourDiff;


  int userCount = 0;
  if(userRootHandle.FirstChild("user").ToNode())
    {
      // Checks to see if the most recent status update
      // occured in the past 48 hours

      TiXmlHandle statusRootHandle = userRootHandle.FirstChild("user").FirstChild("status");
      if(statusRootHandle.ToNode())
	{
	  const char* createdAtStr = statusRootHandle.FirstChild("created_at").ToElement()->GetText();

	  if(!(createdAtStr == NULL))
	    {


	      ss << createdAtStr;
	      ss >> weekday;
	      ss >> month;
	      ss >> day;
	      ss >> time;
	      ss >> tmpStr;
	      ss >> year;

	      tmpStr = weekday + " " + month + " " + day + " " + year + " " + time;
	      

	      strstream << tmpStr;

	      strstream.imbue(std::locale(std::locale::classic(), new boost::local_time::local_time_input_facet("%a %b %d %Y " "%H:%M:%S")));

	      currentTime = boost::posix_time::second_clock::local_time();
	      
	      strstream >> mostRecentTweetTime;
	      tmpStr = strstream.str();

	      boost::posix_time::time_duration hourDiff = currentTime - mostRecentTweetTime;

	      std::cout << currentTime << " - " << mostRecentTweetTime << " = " << hourDiff << "\n";

	      if(hourDiff.hours() < 48)
		userCount++;
	    }
  
	}
    }

  
  // Checks whether the most recent other tweet occurred recently


  TiXmlHandle statusRootHandle = timelineRootHandle.Child("status", 1);
  if(statusRootHandle.ToNode())
    {


      const char* createdAtStr = statusRootHandle.FirstChild("created_at").ToElement()->GetText();

      if(!(createdAtStr == NULL))
	{
	  ss.clear();
	  ss << createdAtStr;
	  ss >> weekday;
	  ss >> month;
	  ss >> day;
	  ss >> time;
	  ss >> tmpStr;
	  ss >> year;

	  tmpStr = weekday + " " + month + " " + day + " " + year + " " + time;

	  strstream.clear();
	  strstream << tmpStr;

	  strstream.imbue(std::locale(std::locale::classic(),
				      new boost::local_time::local_time_input_facet("%a %b %d %Y " "%H:%M:%S")));
	      

	  strstream >> pt;
	  tmpStr = strstream.str();

	  hourDiff = mostRecentTweetTime - pt;

	  std::cout << mostRecentTweetTime << " - " << pt << " = " << hourDiff << "\n";

	  if(hourDiff.hours() < (7 * 24))
	    {
	      userCount++;
	    }
	}
    }


  std::cout << "USER COUNT: " << userCount << "\n";
  return (userCount == 2);
}


void addUserToDb(TiXmlHandle rootHandle, sqlite3 *database)
{
  User tmpUser(rootHandle.FirstChild("user"));
  
  sqlite3_stmt *statement;
  std::string stmtStr;
  std::stringstream ss;
  std::string tmpStr;
  stmtStr = "SELECT * FROM [USERS] WHERE userId = ";
  ss << tmpUser.m_id;
  ss >> tmpStr;
  ss.clear();
  stmtStr += tmpStr;
  


  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
    {
      if( sqlite3_step(statement) == SQLITE_ROW)
	{
	  std::cout << "That user already exists in the database.\n";
	  return;
	}
      else
	{

	  stmtStr = "INSERT INTO [Users] (userId, name, screenName, friendsCount, followersCount) VALUES (" ;

	  ss << tmpUser.m_id;

	  ss >> tmpStr;
	  stmtStr += tmpStr + ", \"" + tmpUser.m_name + "\", \"" + tmpUser.m_screenName + "\", ";
	  ss.clear();
	  ss << tmpUser.m_friendsCount;
	  ss >> tmpStr;
	  stmtStr += tmpStr + ", ";
	  ss.clear();
	  ss << tmpUser.m_followersCount;
	  ss >> tmpStr;
	  stmtStr += tmpStr + ")";

	  std::cout << stmtStr << "\n";

	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << "A user has been added to the database.\n";
	    }

	}
    }
}


int main()
{
  
  std::string tmpStr( "" );
  std::string replyMsg( "" );

 #ifndef DEBUG
  
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

  std::string userStr = "ntiller";

  
  twitterObj.userGet(userStr);
  
  twitterObj.getLastWebResponse(userStr);



  TiXmlDocument userDoc;
  userDoc.Parse(userStr.c_str());


  TiXmlHandle userRoot(&userDoc);

  TiXmlHandle userRootHandle = userRoot.FirstChild("user");
  //  std::cout << userStr;



  
  //  std::cout << primUser << "\n";

 
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
  tmpStr = "185097526";
  twitterObj.userGet(tmpStr, true);
  twitterObj.getLastWebResponse(tmpStr);



#else
  std::string line;
  std::ifstream sampleXML;
  tmpStr = "";
  sampleXML.open("xmlUser.txt");
  if(sampleXML.is_open())
    {
      while(sampleXML.good() )
	{
	  getline (sampleXML, line);
	  tmpStr += line + "\n";
	}
    }

  sampleXML.close();

#endif
      
  TiXmlDocument tmpDoc;
  tmpDoc.Parse(tmpStr.c_str());
      

  //  std::cout << tmpStr;
  TiXmlHandle tmpRoot(&tmpDoc);

#ifndef DEBUG

  twitterObj.timelineUserGet("185097526", true);
  twitterObj.getLastWebResponse(tmpStr);
  


  std::ofstream outStream;
  outStream.open("xmlUserTimeline.txt");
  if(outStream.is_open())
    {
      outStream << tmpStr;
      outStream.close();
    }

#else

  sampleXML.open("xmlUserTimeline.txt");
  if(sampleXML.is_open())
    {
      while(sampleXML.good() )
	{
	  getline (sampleXML, line);
	  tmpStr += line + "\n";
	}
    }

  sampleXML.close();


#endif

  tmpDoc.Parse(tmpStr.c_str());

  //  std::cout << tmpStr;
      
  TiXmlHandle timelineRootHandle(&tmpDoc);
  timelineRootHandle = timelineRootHandle.FirstChild("statuses");
  if(timelineRootHandle.ToNode())



    //  if( userCheck(tmpRoot, timelineRootHandle))
    {
      sqlite3 *database;
      if(sqlite3_open("../twitSpam.db", &database) == SQLITE_OK)
	{
	  addUserToDb(tmpRoot, database);

#ifndef DEBUG
	  twitterObj.friendsGet



#else



#endif

	  addFriends(tmpRoot,
	}  
      sqlite3_close(database);


    }





  return 0;
}



