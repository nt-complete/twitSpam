#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdlib.h>



int main()
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
  std::vector<long> userIdVector, tweetIdVector;
  std::string tmpStr, tweetStr, userStr, combinedStr;
  std::stringstream strStream;
  std::multimap<long, std::string> userMap, tweetMap;
  long userId;


  userFile.open("formatted_user_data.txt");
  tweetFile.open("formatted_tweet_data.txt");
  combinedFile.open("combined_tweet_info.txt");


  if(userFile.is_open() && tweetFile.is_open() && combinedFile.is_open())
    {

      while(getline(userFile,tmpStr))
	{
	  strStream.clear();
	  strStream << tmpStr;
	  strStream >> tmpStr;
	  userId = atol(tmpStr.c_str());
	  userIdVector.push_back(userId);
	  userStr = "";
  while(strStream >> tmpStr)
	    {
	      userStr += " " + tmpStr;
	    }
	  userMap.insert(std::pair<long, std::string>(userId, userStr));
	}


      while(getline(tweetFile,tmpStr))
	{
	  strStream.clear();
	  strStream << tmpStr;
	  
	  strStream >> tmpStr;

	  userId = atol(tmpStr.c_str());
	  tweetStr = "";
	  while(strStream >> tmpStr)
	    {
	      tweetStr += " " + tmpStr;
	    }
	
	  tweetMap.insert(std::pair<long, std::string>(userId, tweetStr));
	}
      
      for(std::map<long, std::string>::iterator userIter = userMap.begin(); userIter != userMap.end(); userIter++)
	{
	  std::map<long, std::string>::iterator tweetIter = tweetMap.find((*userIter).first);

	  if( tweetIter != tweetMap.end())
	    {
	      strStream.clear();
	      userId = (*userIter).first;
	      strStream << userId;
	      strStream >> combinedStr;
	      combinedStr += (*userIter).second + (*tweetIter).second;
	      //	      std::cout << combinedStr << "\n";
	      combinedFile << combinedStr << "\n";
	      combinedFile << "*|*|*\n";
	      tweetMap.erase(tweetIter);
	    }

	}


      for(std::map<long, std::string>::iterator tweetIter = tweetMap.begin(); tweetIter != tweetMap.end(); tweetIter++)
	{

	  userId = (*tweetIter).first;
	  strStream.clear();
	  strStream << userId;

	  strStream >> combinedStr;

	  combinedStr += " ||| 0 ||| 0 ||| 0" + (*tweetIter).second;

	  combinedFile << combinedStr << "\n";
	  combinedFile << "*|*|*\n";

	}


    }
  else
    {
      std::cout << "Problem opening files. Debug this!\n";
      return 1;
    }


}
