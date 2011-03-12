#include <iostream> 
#include <fstream>
#include <sstream>
#include <set>
#include <boost/regex.hpp>
#include <stdlib.h>
#include <string.h>


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
  
  //  std::cout << "SIZE: " << tmpStr.size() << "\n";
  

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



int main(int argv, char** argc)
{
  std::string tmpStr, tweetId, tweetStr, wordStr;
  std::stringstream strStream;
  bool addBool, rtname, retweetCounted;
  
  /*tmpStr = "http://ping.fm/060gb";

  
  addHyperlink(tmpStr, &tweetStr);
  std::cout << tweetStr << "\n";
  
  return 0;*/
  
  


  std::set<std::string> tweetIdSet;
  int retweet = 0;
  int retweetCount = 0;

  std::string outputName = argc[1];
  outputName += ".output";
  std::cout << "Beginning formatting file and outputting as " << outputName << "\n";

  std::ofstream outStream;
  std::ifstream inStream;

  outStream.open(outputName.c_str());

  if(outStream.is_open())
    {
      inStream.open(argc[1]);
      if(inStream.is_open())
	{
	  while(!inStream.eof())
	    {
	    beginning:

	      inStream >> tmpStr; // UserId
	     
	      inStream >> tmpStr; // |||
	     

	      inStream >> tweetId; // tweetId


	      //	      std::cout << "tweetId:: " << tweetId << "\n";


	      tweetStr = "";	      

		  
	      if(tweetIdSet.find(tweetId) == tweetIdSet.end())
		{
	

		  tweetIdSet.insert(tweetId);
		  addBool = true;
		  inStream >> tmpStr; // |||
		  tmpStr = "";

		  getline(inStream, tmpStr);

		  for(int i = 0; i < tmpStr.size(); i++)
		    {
		      if(!isascii(tmpStr.at(i)))
			{
			  goto beginning;
			}

		      if(tmpStr.at(i) == ':')
			{
			  tmpStr.replace(i, 1, "_");
			}
	
		      if(!isalnum(tmpStr.at(i)) && tmpStr.at(i) != '@' && tmpStr.at(i) != '|' && tmpStr.at(i) != '_') // checks for punctuation and replaces them with spaces
			{
			  tmpStr.replace(i,1, " ");
			    
			  //  tmpStr.at(i) = " ";
			}
		      tmpStr.at(i) = tolower(tmpStr.at(i)); // makes all characters lowercase


		    }


		  retweet = 0;
		  
		  retweetCounted = false;
		  rtname = false;

		  boost::regex re(".*\(http://[^\\s]+).*");

		    {
		      
		      std::string hyperlink = boost::regex_replace(tmpStr, re, "$1");
		      addHyperlink(hyperlink, &tweetStr);

		    }
		  std::string username;
		  re = boost::regex(".*[Rr][Tt]\\s+@\([A-Za-z0-9_]+)\\s+\(.*)");

		  
		  if(boost::regex_search(tmpStr,  re))
		    {
		      username = boost::regex_replace(tmpStr, re, "$1");
		      tmpStr = boost::regex_replace(tmpStr, re, "$2");
		      retweet = 1;
		      retweetCount++;
		    }

		  std::string userInfo;
		  re = boost::regex("\(.*)\\|\\|\\|\(.*\\|\\|\\|.*\\|\\|\\|.*)$");
		  if(boost::regex_search(tmpStr,  re))
		    {
		      tmpStr = boost::regex_replace(tmpStr, re, "$1");
		      userInfo = boost::regex_replace(tmpStr, re, "$2");
		    }



		  

		  if(tweetStr.size() > 0)
		    {
		      std::cout << "---" << retweet << "--" << tweetStr << "---\n";
		      outStream << retweet << " |tweetWords " << tweetStr << "\n";
		    }
		  else
		    {
		      //  std::cout << "***" << retweet << "--" << tweetStr << "---\n";
		    }
		}
	

	    }

	  std::cout << "Retweet count: " << retweetCount << "\n";

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
