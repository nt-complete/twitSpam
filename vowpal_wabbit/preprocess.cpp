#include <iostream>
#include <fstream>
#include <string.h>

int main(int argc, char **argv)
{
  std::ifstream tweetFile;
  std::ofstream outFile;
  std::string tmpStr, fullStr;


  tweetFile.open(argv[1]);
  outFile.open("nolines_tweet_data.txt");

  if(tweetFile.is_open() && outFile.is_open())
    {
      while(!tweetFile.eof())
	{
	  getline(tweetFile, tmpStr);
	  if(strcmp(tmpStr.c_str(), "*|*|*") == 0)
	    {
	      outFile << fullStr << "\n*|*|*\n";
	      fullStr = "";
	    }
	  else
	    {
	      fullStr += tmpStr + " ";
	    }

	}

    }
  else
    {
      std::cout << "Error opening files.\n";
      return 1;
    }

}
