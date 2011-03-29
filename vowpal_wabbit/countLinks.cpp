#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>

int main(int argc, char** argv)
{
  std::ifstream instream;
  std::string fullStr;
  std::multimap<std::string, int> linkCountMap;
  std::vector<int> countVec;

  if(argc < 2)
    {
      std::cout << "Please input file to count links.\n";
      return 1;
    }

  instream.open(argv[1]);


  if(instream.is_open())
    {
      while(getline(instream, fullStr))
	{

      
	  boost::regex re("^\(.*)\(http_//[^\\s]+)\(.*)$");
	    while(boost::regex_search(fullStr, re))
	      {
		std::string urlStr = boost::regex_replace(fullStr, re, "$2");
		std::string tmpStr = boost::regex_replace(fullStr, re, "$3");
		fullStr = boost::regex_replace(fullStr, re, "$1");
		fullStr += " " + tmpStr;
		std::multimap<std::string, int>::iterator it = linkCountMap.find(urlStr);

		if(it != linkCountMap.end())
		  {
		    (*it).second += 1;
	
		  }
		else
		  {
		    linkCountMap.insert(std::pair<std::string, int>(urlStr, 1));
		  }

	      }

	}

	    for(std::multimap<std::string, int>::iterator it = linkCountMap.begin(); it != linkCountMap.end(); it++)
	      {
		countVec.push_back((*it).second);
	      }

	    sort(countVec.begin(), countVec.end());

	    for(std::vector<int>::iterator it = countVec.begin(); it != countVec.end(); it++)
	      {
		std::multimap<std::string, int>::iterator linkIt = linkCountMap.begin();
		while(linkIt != linkCountMap.end() && (*linkIt).second != *it)
		  {
		    linkIt++;
		  }
		if(linkIt != linkCountMap.end())
		  {
		    if((*linkIt).second > 1)
		      {
			std::cout << (*linkIt).second << " - " << (*linkIt).first << "\n";
		      }
		    linkCountMap.erase(linkIt);
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
