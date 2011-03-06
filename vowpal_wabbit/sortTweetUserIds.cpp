#include <iostream>
#include <iostream> 
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  std::ofstream outStream;
  std::ifstream inStream;
  std::string tweetLine, userIdStr, tweetStr, tmpStr;
  long userId;
  std::stringstream sstream;
  std::map<long, std::string> tweetMap;
  std::vector<long> tweetVector;
  bool usersBool;

  usersBool = (strcmp(argv[1],"-u") == 0);



  if(usersBool)
    {
      std::cout << argv[2] << "\n";
      inStream.open(argv[2]);
      outStream.open("sorted_user_data.txt");
    }
  else
    {
      inStream.open(argv[1]);
      outStream.open("sorted_tweet_data.txt");
    }



  if(inStream.is_open() && outStream.is_open())
    {

      while(getline(inStream, tweetLine))
	{
	  tweetStr = "";
	  sstream.clear();
	  sstream << tweetLine;

	  if(usersBool)
	    {
	      sstream >> userIdStr;
	      userId = atol(userIdStr.c_str());
	      
	      while(sstream >> tmpStr)
		{
		  tweetStr += " " + tmpStr;
		}

	    }
	  else
	    {


	      sstream >> userIdStr;
	      userId = atol(userIdStr.c_str());
	  
	      sstream >> tmpStr; // |||

	      while(sstream >> tmpStr)
		{
		  tweetStr += " " + tmpStr;
		}


	      getline(inStream, tweetLine);
	      while(tweetLine != "*|*|*")
		{
		  tweetStr += tweetLine;
		  getline(inStream, tweetLine);
	      
		}
	    }
	  tweetMap[userId] = tweetStr;
	  tweetVector.push_back(userId);



	}

      sort(tweetVector.begin(), tweetVector.end());

      for(std::vector<long>::iterator it = tweetVector.begin(); it != tweetVector.end(); it++)
	{
	  std::cout << *it << " |||" << tweetMap[*it] << "\n";
	  outStream << *it << " |||" << tweetMap[*it] << "\n";
	}



      inStream.close();
      outStream.close();
    }
  else
    {
      std::cout << "Problem with opening the files. You should debug that.\n";
      return 1;
    }
  




}
