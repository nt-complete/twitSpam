#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>


int main()
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
  std::vector<long> userIdVector, tweetIdVector;
  std::string tmpStr, tweetStr, userStr, combinedStr, lineStr;
  std::stringstream strStream;
  std::multimap<long, std::string> userMap, tweetMap;
  long userId;


  userFile.open("formatted_user_data.txt");
  tweetFile.open("nolines_tweet_data.txt");
  combinedFile.open("combined_tweet_info.txt");


  if(userFile.is_open() && tweetFile.is_open() && combinedFile.is_open())
    {

      while(getline(userFile,tmpStr))
	{
	  std::stringstream userStream;
	  userStream.str(tmpStr);
	  userStream >> userId;
	  userStr = "";

	  while(userStream >> tmpStr)
	    {
	      userStr += " " + tmpStr;
	    }

	  userMap.insert(std::pair<long, std::string>(userId, userStr));
	}


      /*      for(std::map<long, std::string>::iterator userIter = userMap.begin(); userIter != userMap.end(); userIter++)
	{
	  std::cout << (*userIter).first << "\n";
	  } */



      while(!tweetFile.eof())
	{
	  getline(tweetFile,lineStr);
	  //	  std::cout << lineStr << "\n";
	  if(strcmp(lineStr.c_str(), "*|*|*") != 0 && lineStr.size() > 0)
	    {
	      std::stringstream tweetStream;
	      tweetStream.str(lineStr);
	      tweetStr = tweetStream.str();	  
	      tweetStream >> userId;

	      getline(tweetFile, lineStr);
	      tweetMap.insert(std::pair<long, std::string>(userId, tweetStr));
	    }
	}




      for(std::map<long, std::string>::iterator userIter = userMap.begin(); userIter != userMap.end(); userIter++)
	{
	  std::map<long, std::string>::iterator tweetIter = tweetMap.find((*userIter).first);
	 
	  while( tweetIter != tweetMap.end())
	    {
	      combinedStr = (*tweetIter).second + (*userIter).second;
	      
	      combinedFile << combinedStr << "\n";
	      combinedFile << "*|*|*\n";
	      tweetMap.erase(tweetIter);

	      tweetIter = tweetMap.find((*userIter).first);
	    }
	}

      for(std::map<long, std::string>::iterator tweetIter = tweetMap.begin(); tweetIter != tweetMap.end(); tweetIter++)
	{

	  combinedStr = (*tweetIter).second;
	  combinedFile << combinedStr << "\n";
	  combinedFile << "*|*|*\n";
	}
      tweetFile.close();
      combinedFile.close();
      userFile.close();

    }
  else
    {
      std::cout << "Problem opening files. Debug this!\n";
      return 1;
    }


}
