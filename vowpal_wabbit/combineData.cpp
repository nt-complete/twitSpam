#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

int main()
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
  std::vector<long> userIds, tweetIds;
  std::string tmpStr;
  std::sstream strStream;
  std::multimap<long, std::string> userMap, tweetMap;


  userFile.open("sorted_user_data.txt");
  tweetFile.open("ordered_tweet_data.txt");
  combinedFile.open("combined_tweet_info.txt");


  if(userFile.is_open() && tweetFile.is_open() && combinedFile.is_open())
    {
      while(getline(userFile, tmpStr))
	{
	  strStream << tmpStr;
	  
	}



    }
  else
    {
      std::cout << "Problem opening files. Debug this!\n";
      return 1;
    }


}
