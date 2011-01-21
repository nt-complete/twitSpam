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

//#define DEBUG 1


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

  
  // Checks whether the last 7 tweets occurred within a week

  for( int i = 0; i < 7 ; i++ )
    {
      TiXmlHandle statusRootHandle = timelineRootHandle.Child("status", i);
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
    }

  //  std::cout << "USER COUNT: " << userCount << "\n";
  return (userCount == 8);
}


void addFriendToDb(std::string userIdStr, std::string friendIdStr, sqlite3 *database)
{
  sqlite3_stmt *statement;
  std::string stmtStr;
  std::stringstream ss;
  
  stmtStr = "SELECT * FROM [FRIENDS] WHERE userId = " + userIdStr + " AND friendId = " + friendIdStr;



  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
    {
       if( sqlite3_step(statement) == SQLITE_ROW)
	{
	  std::cout << "That friendship already exists in the database.\n";
	  return;
	}

       stmtStr = "INSERT INTO [FRIENDS] (userId, friendId) VALUES (" + userIdStr + ", " + friendIdStr + ")";
         if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	   {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << stmtStr << "\n";
	      std::cout << "A friendship has been added to the FRIENDS table.\n";

	   }


    }




}

void addFollowerToDb(std::string userIdStr, std::string followerIdStr, sqlite3 *database)
{
  sqlite3_stmt *statement;
  std::string stmtStr;
  std::stringstream ss;
  
  stmtStr = "SELECT * FROM [FRIENDS] WHERE userId = " + userIdStr + " AND friendId = " + followerIdStr;
  std::cout << stmtStr << "\n";


  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
    {
       if( sqlite3_step(statement) == SQLITE_ROW)
	{
	  std::cout << "That followership already exists in the database.\n";
	  return;
	}

       stmtStr = "INSERT INTO [FOLLOWERS] (userId, followerId) VALUES (" + userIdStr + ", " + followerIdStr + ")";
         if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	   {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << "A followership has been added to the FOLLOWERS table.\n";

	   }


    }




}

void addTweetsToDb(TiXmlHandle timelineRootHandle, sqlite3 *database)
{
  TiXmlHandle rootHandle = timelineRootHandle;
  std::string statusText, dateTime, tweetId, replyToTweetId, replyToUserId, stmtStr, userId, retweetedCount;
  std::string weekday, month, day, time, tmpStr, year;
  std::stringstream ss, strstream;
  sqlite3_stmt *statement;


  for(int i = 0; i < 10; )
    {
      rootHandle = timelineRootHandle.Child("status", i);
      if(rootHandle.ToNode())
	{

	  tweetId = rootHandle.FirstChild("id").ToElement()->GetText();
	  userId = rootHandle.FirstChild("user").FirstChild("id").ToElement()->GetText();

	  stmtStr = "SELECT * FROM [TWEETS] WHERE userId = " + userId + " AND tweetId = " + tweetId;
	  

	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      if( sqlite3_step(statement) == SQLITE_ROW)
		{
		  std::cout << "That tweet already exists in the database.\n";
		  
		}
	      else
		{

		  stmtStr = "INSERT INTO [TWEETS] (statusText, dateTime, tweetId, replyToTweetId, replyToUserId, userId, retweetedCount) VALUES (";
		  statusText = rootHandle.FirstChild("text").ToElement()->GetText();
		  stmtStr += "\"" + statusText + "\", ";

		  dateTime = rootHandle.FirstChild("created_at").ToElement()->GetText();
		  ss.clear();
		  ss << dateTime;
		  ss >> weekday;
		  ss >> month;
		  ss >> day;
		  ss >> time;
		  ss >> tmpStr;
		  ss >> year;

		  tmpStr = weekday + " " + month + " " + day + " " + year + " " + time;
		  stmtStr += "\"" + tmpStr + "\", ";

		  stmtStr += "\"" + tweetId + "\", ";


		  if(rootHandle.FirstChild("in_reply_to_status_id").ToElement()->GetText())
		    {
		      replyToTweetId = rootHandle.FirstChild("in_reply_to_status_id").ToElement()->GetText();
		    }

		  stmtStr += "\"" + replyToTweetId + "\", ";


		  if(rootHandle.FirstChild("in_reply_to_user_id").ToElement()->GetText())
		    {
		      replyToUserId = rootHandle.FirstChild("in_reply_to_user_id").ToElement()->GetText();
		    }
		  stmtStr += "\"" + replyToUserId + "\", ";


		  stmtStr += userId + ", ";

		  retweetedCount = rootHandle.FirstChild("retweet_count").ToElement()->GetText();
		  stmtStr += retweetedCount + ")"; 
	  

	
		  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
		    {

		      sqlite3_step(statement);
		      sqlite3_finalize(statement);
		      std::cout << "A tweet has been added to the database.\n";
		      i++;
		    }



		}
	    }

	}
    }
}



void addUserToDb(User tmpUser, sqlite3 *database)
{

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

	  //	  std::cout << stmtStr << "\n";

	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << "A user has been added to the database.\n";
	    }

	}
    }
}


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
  std::stringstream ss;
  User tmpUser;
  std::string userIdStr;
  std::ofstream outStream;
  std::ifstream sampleXML;
  TiXmlDocument userDoc;
  TiXmlDocument tmpDoc;
  std::string tmpStr;
  bool cont;

 #ifndef DEBUG
 
  authorize();



  long maxIdNum = 235314984;

  srand48(time(NULL));

  int usersAddedCount = 0;
  while(usersAddedCount < 10)
    {

      double randNum = drand48();
      long idNum = maxIdNum * randNum;
      ss.clear();
      ss << idNum;

      userIdStr = ss.str();
      // tmpStr = "185097526";
      twitterObj.userGet(userIdStr, true);
      twitterObj.getLastWebResponse(tmpStr);

      //      std::cout << tmpStr;

#else
      std::string line;

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
      
      tmpDoc.Parse(tmpStr.c_str());
      
      TiXmlHandle tmpRoot(&tmpDoc);


      if(tmpRoot.FirstChild("errors").ToNode())
	{

	  sleep(60*62);
	  twitterObj.userGet(userIdStr, true);
	  twitterObj.getLastWebResponse(tmpStr);

	  tmpDoc.Parse(tmpStr.c_str());
      
	   tmpRoot = TiXmlHandle(&tmpDoc);

	}


      ///*** TIMELINE SECTION ***///


      

      twitterObj.timelineUserGet(userIdStr, true);
      twitterObj.getLastWebResponse(tmpStr);

#ifndef DEBUG
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
      
      TiXmlHandle timelineRootHandle(&tmpDoc);
      if(timelineRootHandle.FirstChild("errors").ToNode())
	{
	  sleep(60*62);
	  twitterObj.timelineUserGet(userIdStr, true);
	  twitterObj.getLastWebResponse(tmpStr);

	  tmpDoc.Parse(tmpStr.c_str());
	  timelineRootHandle = TiXmlHandle(&tmpDoc);

	}



     timelineRootHandle = timelineRootHandle.FirstChild("statuses");
      if(timelineRootHandle.ToNode())
	{

 
	  if( userCheck(tmpRoot, timelineRootHandle))
	    {
	      usersAddedCount++;
	      {
		sqlite3 *database;
		if(sqlite3_open("../twitSpam.db", &database) == SQLITE_OK)
		  {
		    std::string userIdStr;

		    tmpUser = User(tmpRoot.FirstChild("user"));
		    addUserToDb(tmpUser, database);

		    addTweetsToDb(timelineRootHandle, database);
	  






		    ///**** FRIEND SECTION ****///



		    ss.clear();
		    ss << tmpUser.m_id;
		    ss >> userIdStr;
		    twitterObj.friendsGet(userIdStr, true);
		    twitterObj.getLastWebResponse(tmpStr);

#ifndef	DEBUG
		    outStream.open("xmlFriends.txt");
		    if(outStream.is_open())
		      {
			outStream << tmpStr;
			outStream.close();
		      }
#else
		    sampleXML.open("xmlFriends.txt");
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

		    ///*** ADDS FRIENDS TO DB ****////

		    tmpDoc.Parse(tmpStr.c_str());
		    tmpRoot = TiXmlHandle(&tmpDoc);
	
		    if(tmpRoot.FirstChild("errors").ToNode())
		      {
			sleep(60*62);
			twitterObj.friendsGet(userIdStr, true);
			twitterObj.getLastWebResponse(tmpStr);
			tmpDoc.Parse(tmpStr.c_str());
			tmpRoot = TiXmlHandle(&tmpDoc);
		      }

		    tmpUser.setFriends(tmpRoot);

		    for(std::vector<User*>::iterator it = tmpUser.m_friends.begin(); 
			it != tmpUser.m_friends.end(); it++)
		      {
			std::string friendIdStr;
			addUserToDb((**it), database);
			ss.clear();
			ss << (**it).m_id;
			ss >> friendIdStr;

			ss.clear();
			ss << tmpUser.m_id;
			ss >> userIdStr;
			addFriendToDb(userIdStr, friendIdStr, database);


		      }

		    ///**** ADD FOLLOWERS TO DB ****////


#ifndef	DEBUG
		    ss.clear();
		    ss << tmpUser.m_id;
		    ss >> userIdStr;
		    twitterObj.followersGet(userIdStr, true);
		    twitterObj.getLastWebResponse(tmpStr);


		    outStream.open("xmlFollowers.txt");
		    if(outStream.is_open())
		      {
			outStream << tmpStr;
			outStream.close();
		      }
#else
		    sampleXML.open("xmlFollowers.txt");
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
		    tmpRoot = TiXmlHandle(&tmpDoc);


		    if(tmpRoot.FirstChild("errors").ToNode())
		      {
			sleep(60*62);
			twitterObj.followersGet(userIdStr, true);
			twitterObj.getLastWebResponse(tmpStr);

			tmpDoc.Parse(tmpStr.c_str());
			tmpRoot = TiXmlHandle(&tmpDoc);


		      }

		    tmpUser.setFollowers(tmpRoot);


		    for(std::vector<User*>::iterator iter = tmpUser.m_followers.begin(); 
			iter != tmpUser.m_followers.end(); iter++)
		      {

			std::string followerIdStr;

			addUserToDb((**iter), database);
			ss.clear();
			ss << (**iter).m_id;
			ss >> followerIdStr;

			ss.clear();
			ss << tmpUser.m_id;
			ss >> userIdStr;

			std::cout << "Adding follower: " << followerIdStr << ", user: " << userIdStr << "\n";

			addFriendToDb(followerIdStr, userIdStr, database);


		      }




		  }  
		sqlite3_close(database);


      


	      }

	    }
	}	

    }
  return 0;
}



