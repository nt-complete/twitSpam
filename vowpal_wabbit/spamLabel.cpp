#include <iostream> 
#include <fstream>
#include <sstream>
#include <set>
#include <boost/regex.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdlib.h>
#include <string.h>
#include "curler.h"
#include "../include/tinystr.h"
#include "../include/tinyxml.h"



std::string getTweetAge(std::string tweetXML)
{
  TiXmlDocument tweetDoc;

  std::cout << tweetXML;

  tweetDoc.Parse(tweetXML.c_str());
  TiXmlHandle tweetRootHandle(&tweetDoc);
  if(!tweetRootHandle.FirstChild("").ToNode())
    {}

  return "";

}


std::vector<std::string> parseXML(std::string userXML)
{
  std::vector<std::string> info;
  boost::posix_time::ptime currentTime, createdTime;
  std::string createdStr;
  std::string weekday, month, day, time, year, tmpStr;
  TiXmlDocument userDoc;
  std::stringstream ss, strstream;
  boost::posix_time::time_duration hourDiff;
  int dayDiff;


  userDoc.Parse(userXML.c_str());
  TiXmlHandle userRootHandle(&userDoc);
  if(!userRootHandle.FirstChild("user").ToNode())
    {
      return info;
    }
  userRootHandle = userRootHandle.FirstChild("user");
  info.push_back(userRootHandle.FirstChild("friends_count").ToElement()->GetText());
  info.push_back(userRootHandle.FirstChild("followers_count").ToElement()->GetText());
  createdStr = userRootHandle.FirstChild("created_at").ToElement()->GetText();

  currentTime = boost::posix_time::second_clock::local_time();


  ss.str("");
  ss << createdStr;
  ss >> weekday;
  ss >> month;
  ss >> day;
  ss >> time;
  ss >> tmpStr;
  ss >> year;

  tmpStr = weekday + " " + month + " " + day + " " + year + " " + time;
	      
  strstream.str("");
  strstream << tmpStr;

  strstream.imbue(std::locale(std::locale::classic(), new boost::local_time::local_time_input_facet("%a %b %d %Y " "%H:%M:%S")));


	      
  strstream >> createdTime;

  hourDiff = currentTime - createdTime;
  dayDiff = (int)(hourDiff.hours()/24);

  std::stringstream dayStream;
  dayStream << dayDiff;

  info.push_back(dayStream.str());

  return info;

}

void addHyperlink(std::string tmpStr, std::string* tweetStr)
{
  int i = 0;
  while(tmpStr.at(i) != '/')
    {
      if(tmpStr.at(i) == ':')
	{
	  tmpStr.replace(i, 1, "_");
	}
      i++;
    }
  i += 2;
  if(strncmp(tmpStr.substr(i,4).c_str(), "www.", 4) == 0)
    {
      i += 4;
    }
  
  while(i < tmpStr.size())
    {
      while(tmpStr.at(i) != '/' && tmpStr.at(i) != '.' && i < tmpStr.size() - 1)
	{
	  if(tmpStr.at(i) == ':')
	    {
	      tmpStr.replace(i, 1, "_");
	    }
	  i++;
	}
  
      *tweetStr += " " + tmpStr.substr(0, i);
  
      i++;
    }
    
  *tweetStr += tmpStr.at(tmpStr.size()-1);
  *tweetStr += " ";
}



int main(int argc, char** argv)
{
  std::string tmpStr, tweetId, tweetStr, wordStr, userId;
  std::string userXML, tweetXML, tweetDate;
  std::stringstream strStream;
  std::vector<std::string> userInfoVec;
  bool addBool, checkUser, useCurl;
  std::ofstream outStream;
  std::ifstream inStream;  
  std::string outputName, inputName, fullStr;

  std::set<std::string> tweetIdSet;
  int retweet = 0;
  int retweetCount = 0;
  long lineNum = 142046;
  int spam = 0;
  int spamCount = 0;
  double count = 0;
  double percentage;


  checkUser = true;
  useCurl = true;

  if(argc < 2)
    {
      std::cout << "Please pass the file that should be made into input.\n";
      return 1;
    }


  if(strcmp(argv[1], "-c") == 0)
    {
   
      useCurl = false;
      outputName = argv[2];
    } else {

    if(strcmp(argv[1], "-n") == 0)
      {
	checkUser = false;
	outputName = argv[2];
      }
    else
      {
	outputName = argv[1];
      }
  }
  inputName = outputName;
  outputName += ".output";
  std::cout << "Beginning formatting file and outputting as " << outputName << "\n";

  outStream.open(outputName.c_str());

  if(outStream.is_open())
    {
      inStream.open(inputName.c_str());
      if(inStream.is_open())
	{
	  while(!inStream.eof())
	    {
	    start:
	      count++;
	      getline(inStream, fullStr);
	      if(fullStr.size() <= 0)
		{
		  break;
		}

	      std::stringstream fullStream;
	      fullStream.str(fullStr);

	      if(!checkUser)
		{
		  fullStream >> retweet;

		  fullStream >> tmpStr;
		  retweetCount += retweet;
		  spamCount += spam;
		  tweetId = "0";
		}
	      else
		{

		  fullStream >> userId; // UserId
		  fullStream >> tmpStr; // |||
		  fullStream >> tweetId; // tweetId
		  fullStream >> tmpStr; // |||
		}
	      tweetStr = "";	      
		  
	      if(tweetIdSet.find(tweetId) == tweetIdSet.end() || !checkUser)
		{
		  tweetIdSet.insert(tweetId);
		  addBool = true;
	
		  tmpStr = "";

		  //getline(inStream, tmpStr);
		  
		  while(fullStream >> fullStr)
		    {
		      tmpStr += fullStr + " ";
		    }


		  boost::regex re("^\(.*)\(http://[^\\s]+)\(.*)$");
		  while(boost::regex_search(tmpStr,  re))
		    {
	
		      std::string hyperlink = boost::regex_replace(tmpStr, re, "$2");
		      addHyperlink(hyperlink, &tweetStr);
		      fullStr = tmpStr;
		      tmpStr = boost::regex_replace(fullStr, re, "$1");
		      tmpStr += boost::regex_replace(fullStr, re, "$3");
		      //std::cout << tmpStr << "\n";
		    }


		  std::string username;
		  std::string userInfo = "";
		  if(checkUser)
		    {
		      retweet = 0;
		      spam = 0;

		      re = boost::regex("[Rr][Tt]\\s\\s*@\([A-Za-z0-9_][A-Za-z0-9_]*)\\s\(.*)");

		      Curler curlHelper;
		      if(boost::regex_search(tmpStr,  re))
			{
			  username = boost::regex_replace(tmpStr, re, "$1");
			 
			  if(useCurl)
			    {
			      userXML = curlHelper.getUserInfo(username);
			      tweetXML = curlHelper.getTweetInfo(username, tweetId);
			      tweetDate = getTweetAge(tweetXML);

			      userInfoVec = parseXML(userXML);

			      if(userInfoVec.size() == 0)
				{
				  spam = 1;
				}

			      else{
				spam = 0;
				userInfo += " " + userInfoVec.at(0);
				userInfo += " ||| " + userInfoVec.at(1);
				userInfo += " ||| " + userInfoVec.at(2);
			      }

			    }

			  retweet = 1;
			  retweetCount++;


			}
		      else
			{
			  userXML = curlHelper.getUserInfo(userId);
			  tweetXML = curlHelper.getTweetInfo(username, tweetId);
			  tweetDate = getTweetAge(tweetXML);
			      //std::cout << userXML ;

			  userInfoVec = parseXML(userXML);
			  if(userInfoVec.size() == 0)
			    {
		
			      tmpStr = boost::regex_replace(tmpStr, re, "$2");
			      //inStream >> tmpStr;
			      spam = 1;
			      //goto start;
				 
			    }
			  else{
			    spam = 0;
			    userInfo += " " + userInfoVec.at(0);
			    userInfo += " ||| " + userInfoVec.at(1);
			    userInfo += " ||| " + userInfoVec.at(2);
			  }

			}
		    }


		  re = boost::regex("^\(.*)\\|\\|\\|\(.*\\|\\|\\|.*\\|\\|\\|.*)$");
		  if(boost::regex_search(tmpStr,  re))
		    {
		      //std::cout << tmpStr << "\n";
		      std::string regStr;
		      regStr = boost::regex_replace(tmpStr, re, "$1");
		      if(userInfo.size() == 0)
			{
			  userInfo = boost::regex_replace(tmpStr, re, "$2");
			}
		      tmpStr = regStr;
		      //std::cout << tmpStr << "\n";
		    }



		  //		  std::cout << tmpStr << "\n";

		  tweetStr += tmpStr;

		  percentage = (double)(count / lineNum);

		  percentage = (percentage * 10000);

		  percentage = (int) percentage;
		  percentage /= 100;

		  if(userInfo.size() > 0)
		    {
		      std::string friends, followers, age;
		      std::stringstream userStream;
		      userStream.str(userInfo);
		      userStream >> friends;
		      userStream >> tmpStr;
		      userStream >> followers;
		      userStream >> tmpStr;
		      userStream >> age;

		      std::string userStr = " |Friends " + friends + " |Followers " + followers + " |age " + age;

		      std::cout << "\r" << percentage << "%";


		      //std::cout << retweet << " |tweetWords " << tweetStr << userStr << "\n";
		      outStream << spam << " |tweetWords " << tweetStr << userStr << "\n";
		      

		    }
		  else
		    {
		      std::cout << "\r" << percentage << "%";


		      //std::cout << retweet << " |tweetWords " << tweetStr << "\n";
		      outStream << spam << " |tweetWords " << tweetStr << "\n";
		    }
		  //  getline(inStream, tmpStr);

		}
	

	    }

	  std::cout << "\nRetweet count: " << retweetCount << "\n";

	  outStream.close();
	  inStream.close();

	}
      else
	{
	  std::cout << "Unable to open input file.\n";
	  return 1;

	}

    }
  else
    {
      std::cout << "Unable to open output file.\n";
      return 1;

    }

}
