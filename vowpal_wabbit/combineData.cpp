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
	  strStream.str(std::string());
	  strStream << tmpStr;
	  strStream >> tmpStr;
	  userId = atol(tmpStr.c_str());
	  userIdVector.push_back(userId);
	  userStr = "";
	  /*	  while(strStream >> tmpStr)
	    {
	      userStr += " " + tmpStr;
	      }*/
	  userStr = strStream.str();
	  userMap.insert(std::pair<long, std::string>(userId, userStr));
	}


      while(!tweetFile.eof())
	{
	  getline(tweetFile,lineStr);
	  //	  std::cout << lineStr << "\n";
	  if(strcmp(lineStr.c_str(), "*|*|*") != 0 && lineStr.size() > 0)
	    {
	      strStream.str(std::string());
	      strStream << lineStr;
	      tweetStr = strStream.str();	  
	      //std::cout << tweetStr << "\n";
	      strStream >> tmpStr;

	      userId = atol(tmpStr.c_str());

	      /*	      while(strStream >> tmpStr)
		{
		  tweetStr += " " + tmpStr;
		  } */


	      getline(tweetFile, lineStr);
	      tweetMap.insert(std::pair<long, std::string>(userId, tweetStr));
	    }
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


	 
	  while( tweetIter != tweetMap.end())
	    {

	      /*	      strStream.str(std::string());
	      combinedStr = "";
	      userId = (*userIter).first;
	      strStream << userId;
	      strStream >> tmpStr;
	      combinedStr = tmpStr;
	      std::cout << userId << " - " << tmp << "\n";*/


	      combinedStr = (*tweetIter).second + (*userIter).second;
	      

	      combinedFile << combinedStr << "\n";
	      combinedFile << "*|*|*\n";
	      tweetMap.erase(tweetIter);

	       tweetIter = tweetMap.find((*userIter).first);
	    }

	}


      for(std::map<long, std::string>::iterator tweetIter = tweetMap.begin(); tweetIter != tweetMap.end(); tweetIter++)
	{

	  /*	  userId = (*tweetIter).first;
	  combinedStr = "";
	  strStream.str(std::string());
	  strStream << userId;
	  strStream >> combinedStr; */

	  combinedStr = (*tweetIter).second;
	  //std::cout << combinedStr << "\n";
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
