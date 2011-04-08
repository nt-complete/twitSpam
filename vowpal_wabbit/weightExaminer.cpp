#include <iostream>
#include <fstream>
#include <map>
#include <boost/regex.hpp>
#include <set>

int main(int argc, char** argv)
{
  std::multimap<double, std::string> tweetWordsMap;
  std::map<std::string, int> wordCounterMap;
  std::ifstream inputStream;
  std::string fullStr;
  std::set<std::string> wordSet;

  if(argc < 2)
    {
      std::cout << "Please input weight file to analyze.\n";
      return 1;
    }

  inputStream.open(argv[1]);
  if(inputStream.is_open())
    {
      while(!inputStream.eof())
	{
	  getline(inputStream, fullStr);
	  getline(inputStream, fullStr);

	  boost::regex re("\\s+tweetWords\\^\([^:]+):[0-9]+:[0-9]+:\([^\\s]+)\(.*)$");
	  while(boost::regex_search(fullStr, re))
	    {
	      std::string wordStr = boost::regex_replace(fullStr, re, "$1");
	      std::string valueStr = boost::regex_replace(fullStr, re, "$2");
	      double value = atof(valueStr.c_str());
	      fullStr = boost::regex_replace(fullStr, re, "$3");
	      //std::cout << wordStr << " - " << value << "\n";

	      if(wordSet.find(wordStr) == wordSet.end())
		{
		  wordSet.insert(wordStr);
		  tweetWordsMap.insert(std::pair<double, std::string>(value, wordStr));
		  wordCounterMap.insert(std::pair<std::string, int>(wordStr, 1));
		}
	      else
		{
		  std::map<std::string, int>::iterator it = wordCounterMap.find(wordStr);
		  (*it).second++;
		}

	    }

	}

      for(std::multimap<double, std::string >::iterator it = tweetWordsMap.begin(); it != tweetWordsMap.end(); it++)
	{
	  std::map<std::string, int>::iterator iter = wordCounterMap.find((*it).second);
	  if((*iter).second > 10)
	    std::cout << (*it).second << " - " << (*it).first << " - " << (*iter).second << "\n";

	}


    }
  else
    {
      std::cout << "Problem opening file.\n";
      return 1;
    }


  return 0;
}
