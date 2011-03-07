#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int main()
{
  std::ifstream userFile, tweetFile;
  std::ofstream combinedFile;
  std::vector<long> userIds, tweetIds;
  std::string tmpStr;
  
  std::multimap<long, std::string> userMap, tweetMap;


  userFile.open("sorted_user_data.txt");
  tweetFile.open("sorted_tweet_data.txt");
  combinedFile.open("combined_tweet_info.txt");


  if(userFile.is_open() && tweetFile.is_open() && combinedFile.is_open())
    {
      



    }
  else
    {
      std::cout << "Problem opening files. Debug this!\n";
      return 1;
    }


}
