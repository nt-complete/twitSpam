#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
<<<<<<< HEAD
#include <algorithm>
#include <stdlib.h>

=======
>>>>>>> 7ce17b8e75e4fa8cd95f865c91cd9f8ba8b3d79e

int main()
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
<<<<<<< HEAD
  std::vector<long> userIdVector, tweetIdVector;
  std::string tmpStr, tweetStr, userStr, combinedStr;
  std::stringstream strStream;
=======
  std::vector<long> userIds, tweetIds;
  std::string tmpStr;
  std::sstream strStream;
>>>>>>> 7ce17b8e75e4fa8cd95f865c91cd9f8ba8b3d79e
  std::multimap<long, std::string> userMap, tweetMap;
  long userId;

<<<<<<< HEAD
  userFile.open("formatted_user_data.txt");
  tweetFile.open("smaller_tweet_data.txt");
=======

  userFile.open("sorted_user_data.txt");
  tweetFile.open("ordered_tweet_data.txt");
>>>>>>> 7ce17b8e75e4fa8cd95f865c91cd9f8ba8b3d79e
  combinedFile.open("combined_tweet_info.txt");


  if(userFile.is_open() && tweetFile.is_open() && combinedFile.is_open())
    {
<<<<<<< HEAD
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
=======
      while(getline(userFile, tmpStr))
	{
	  strStream << tmpStr;
	  
	}
>>>>>>> 7ce17b8e75e4fa8cd95f865c91cd9f8ba8b3d79e

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
	    }

	}

    }
  else
    {
      std::cout << "Problem opening files. Debug this!\n";
      return 1;
    }


}
