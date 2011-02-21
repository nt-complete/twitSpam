#include <iostream> 
#include <fstream>
#include <set>
#include <string.h>


void addHyperlink(std::string tmpStr, std::string* tweetStr)
{
  int i = 0;
  while(tmpStr.at(i) != '/')
    {
      i++;
    }
  i += 2;
  if(strncmp(tmpStr.substr(i,4).c_str(), "www.", 4) == 0)
    {
      i += 4;
    }
  
  //  std::cout << "SIZE: " << tmpStr.size() << "\n";
  

  while(i < tmpStr.size())
    {
      while(tmpStr.at(i) != '/' && tmpStr.at(i) != '.' && i < tmpStr.size() - 1)
	{
	  i++;
	}
  
      *tweetStr += " " + tmpStr.substr(0, i);
  
      i++;
    }
    
}



int main(int argv, char** argc)
{
  std::string tmpStr, tweetId, tweetStr;
  bool addBool;

  /*tmpStr = "http://ping.fm/060gb";

  
  addHyperlink(tmpStr, &tweetStr);
  std::cout << tweetStr << "\n";
  
  return 0;*/
  
  


  std::set<std::string> tweetIdSet;
  int retweet = 0;

  std::string outputName = argc[1];
  outputName += ".output";
  std::cout << "Beginning formatting file and outputting as " << outputName << "\n";

  std::ofstream outStream;
  std::ifstream inStream;

  outStream.open(outputName.c_str());

  if(outStream.is_open())
    {
      inStream.open(argc[1]);
      if(inStream.is_open())
	{
	  while(!inStream.eof())
	    {
	      inStream >> tweetId; // tweetId

	      //     std::cout << "tweetId:: " << tweetId << "\n";
	      
	      if(tweetIdSet.find(tweetId) == tweetIdSet.end())
		{
		  tweetIdSet.insert(tweetId);
		  addBool = true;
		  
		  inStream >> tmpStr; // |||
		  inStream >> tmpStr; // UserId
		  inStream >> tmpStr; // |||
		  inStream >> tmpStr; // receiverUserId
		  inStream >> tmpStr; // |||
		  inStream >> tmpStr; // geo info
		  inStream >> tmpStr; // |||
		  do{
		    inStream >> tmpStr; // source
		  }while(strcmp(tmpStr.c_str(), "|||") != 0);

		  inStream >> tmpStr; // tweet date (Epoch Time)
		  inStream >> tmpStr; // |||
		  tmpStr = "";

		  tweetStr = "";
		  retweet = 0;
		  
		  while(strcmp(tmpStr.c_str(), "*|*|*") != 0 && !inStream.eof())
		    {

		      if(strncmp(tmpStr.c_str(), "http", 4) == 0)
			{
			  addHyperlink(tmpStr, &tweetStr);
			}
		      else 
			{
			  
			  for(int i = 0; i < tmpStr.size(); i++)
			    {
			      if(!isascii(tmpStr.at(i))) // checks for non-ASCII characters
				{
				  addBool = false;
				  tmpStr = "";
				  //std::cout << "1. BREAKING BECAUSE OF NON-ASCII CHARACTERS\n";
				  break;
				}
	
			      if(!isalnum(tmpStr.at(i))) // checks for punctuation and replaces them with spaces
				{
				  tmpStr.replace(i,1, " ");
			    
				  //  tmpStr.at(i) = " ";
				}
			
			      tmpStr.at(i) = tolower(tmpStr.at(i)); // makes all characters lowercase
			    }
			
		      
			  if(!addBool)
			    {
			      while(strcmp(tmpStr.c_str(), "*|*|*") != 0)
				{
				  inStream >> tmpStr; // tweet
				}
			      tweetStr = "";
			      //std::cout << "2. BREAKING BECAUSE OF NON-ASCII CHARACTERS\n";
			      break;
			    }
		    
			  if(strcmp(tmpStr.c_str(), "rt") == 0)
			    {
			      inStream >> tmpStr;
			      if(strncmp(tmpStr.c_str(), "@", 1) == 0)
				{
				  retweet = 1;
				}
			  
			    }
			  tweetStr += tmpStr + " ";
			}
		      
		      inStream >> tmpStr; // tweet	  		    
		    }


		  if(tweetStr.size() > 0)
		    {
		      std::cout << "---" << retweet << "--" << tweetStr << "---\n";
		      outStream << retweet << " |features " << tweetStr << "\n";
		    }
		  else
		    {
		      //  std::cout << "***" << retweet << "--" << tweetStr << "---\n";
		    }
		}

	    }

	  outStream.close();
	  inStream.close();

	}
      else
	{
	  std::cout << "Unable to open input file.\n";
	  return 1;

	}

    }
  else
    {
      std::cout << "Unable to open output file.\n";
      return 1;

    }

}
