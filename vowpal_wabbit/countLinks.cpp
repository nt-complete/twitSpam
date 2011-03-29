#include <map>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

int main()
{
  std::ifstream instream;
  std::string fullStr;
  std::multimap<std::string, int> linkCountMap;


  instream.open("retweets_tweets.txt");
  if(instream.is_open())
    {
      getline(instream, fullStr);
      
      boost::regex re("\(http_//[^ ]+)");
      while(boost::regex_search(fullStr, re))
	{
	  std::string urlStr = boost::regex_replace(fullStr, re, "$1");
	  std::multimap<std::string, int>::iterator it = linkCountMap.find(urlStr);

	  if(it != linkCountMap.end())
	    {
	      (*it).second++;

	    }
	  else
	    {
	      linkCountMap.insert(std::pair<std::string, int>(urlStr, 1));
	    }

	}





    }
  else
    {
      std::cout << "Error opening file.\n";
      return 1;

    }

  return 0;
}
