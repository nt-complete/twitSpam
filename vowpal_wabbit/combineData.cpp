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


  userFile.open("temp_user_data.txt");
  tweetFile.open("temp_tweet_data.txt");
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


      while(!tweetFile.eof())
	{
	  getline(tweetFile,lineStr);
	  std::cout << lineStr << "\n";
	  strStream.clear();
	  strStream << lineStr;
	  
	  strStream >> tmpStr;

	  userId = atol(tmpStr.c_str());


	  //	  std::cout << lineStr << "\n";
	  tweetStr = "";
	  while(strStream >> tmpStr)
	    {
	      tweetStr += " " + tmpStr;
	    }


	  tweetMap.insert(std::pair<long, std::string>(userId, tweetStr));
	}




      /*
            for(std::map<long, std::string>::iterator userIter = userMap.begin(); userIter != userMap.end(); userIter++)
	      {
		std::cout << (*userIter).first << (*userIter).second << "\n";
	      }*/



	    
      /*            for(std::map<long, std::string>::iterator tweetIter = tweetMap.begin(); tweetIter != tweetMap.end(); tweetIter++)
	      {
		std::cout << (*tweetIter).first << (*tweetIter).second << "\n";
		} */
	    




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
