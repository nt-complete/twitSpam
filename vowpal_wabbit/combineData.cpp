#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
  std::vector<long> userIdVector, tweetIdVector;
  std::string tmpStr, tweetStr, userStr, combinedStr, lineStr;
  std::stringstream strStream;
  std::multimap<long, std::string> userMap, tweetMap;
  long userId;

  if(argc < 4)
    {
      std::cout << "Please input the tweet file, user file, and output file.\n";
      return 1;

    }

  userFile.open(argv[2]);
  tweetFile.open(argv[1]);
  combinedFile.open(argv[3]);
  std::cout << "Outputting to: " << argv[3] << ".\n";

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


      int count = 0;
      while(!tweetFile.eof())
	{
	  getline(tweetFile,lineStr);
	  //	  std::cout << lineStr << "\n";
	  if(strcmp(lineStr.c_str(), "*|*|*") != 0 && lineStr.size() > 0)
	    {
	      std::stringstream tweetStream;
	      tweetStream.str(lineStr);
	      tweetStr = tweetStream.str();	  
	      tweetStream >> tmpStr;
	      tweetStream >> tmpStr;
	      tweetStream >> userId;
	      std::cout << "UserId: " << userId << "\n";
	      tweetMap.insert(std::pair<long, std::string>(userId, lineStr));
	    }
	  count++;
	}
      std::cout << "Count: " << count << "\n";
      std::cout << "Tweetsize: " << tweetMap.size() << " Usersize: " << userMap.size() << "\n";

      for(std::map<long, std::string>::iterator userIter = userMap.begin(); userIter != userMap.end(); userIter++)
	{
	  std::map<long, std::string>::iterator tweetIter = tweetMap.find((*userIter).first);
	 
	  while( tweetIter != tweetMap.end())
	    {
	      combinedStr = (*tweetIter).second + (*userIter).second;
	      
	      combinedFile << combinedStr << "\n";
	      //std::cout << combinedStr << "\n";
	      tweetMap.erase(tweetIter);

	      tweetIter = tweetMap.find((*userIter).first);
	    }
	}

      for(std::map<long, std::string>::iterator tweetIter = tweetMap.begin(); tweetIter != tweetMap.end(); tweetIter++)
	{

	  combinedStr = (*tweetIter).second;
	  //std::cout << combinedStr << "\n";
	  combinedFile << combinedStr << "\n";
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
