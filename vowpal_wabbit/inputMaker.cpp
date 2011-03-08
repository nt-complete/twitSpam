#include <iostream> 
#include <fstream>
#include <sstream>
#include <set>
#include <string.h>


void addHyperlink(std::string tmpStr, std::string* tweetStr)
{
  int i = 0;
  while(tmpStr.at(i) != '/')
    {
      if(tmpStr.at(i) == ':')
	{
	  tmpStr.replace(i, 1, "_");
	}
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
	  if(tmpStr.at(i) == ':')
	    {
	      tmpStr.replace(i, 1, "_");
	    }
	  i++;

	}
  
      *tweetStr += " " + tmpStr.substr(0, i);
  
      i++;
    }
    
  *tweetStr += tmpStr.at(tmpStr.size()-1);
  *tweetStr += " ";
}



int main(int argv, char** argc)
{
  std::string tmpStr, tweetId, tweetStr, wordStr;
  std::stringstream strStream;
  bool addBool;

  /*tmpStr = "http://ping.fm/060gb";

  
  addHyperlink(tmpStr, &tweetStr);
  std::cout << tweetStr << "\n";
  
  return 0;*/
  
  


  std::set<std::string> tweetIdSet;
  int retweet = 0;
  int retweetCount = 0;

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
	      inStream >> tmpStr; // UserId
	      inStream >> tmpStr; // |||
	      inStream >> tweetId; // tweetId


	      //     std::cout << "tweetId:: " << tweetId << "\n";
	      
	      if(tweetIdSet.find(tweetId) == tweetIdSet.end())
		{
		  tweetIdSet.insert(tweetId);
		  addBool = true;
		  inStream >> tmpStr; // |||
		  tmpStr = "";

		  tweetStr = "";
		  retweet = 0;
		  



		  while(strcmp(tmpStr.c_str(), "*|*|*") != 0 && !inStream.eof())
		    {
		      strStream.clear();
		      strStream << tmpStr;

		      while(strStream >> wordStr)
			{


			  if(strncmp(wordStr.c_str(), "http://", 7) == 0)
			    {
			      addHyperlink(wordStr, &tweetStr);
			    }
			  else 
			    {

			      for(int i = 0; i < wordStr.size(); i++)
				{
				  if(!isascii(wordStr.at(i))) // checks for non-ASCII characters
				    {
				      addBool = false;
				      wordStr = "";
				      //std::cout << "1. BREAKING BECAUSE OF NON-ASCII CHARACTERS\n";
				      break;
				    }

				  if(wordStr.at(i) == ':')
				    {
				      wordStr.replace(i, 1, "_");
				    }
	
				  if(!isalnum(wordStr.at(i)) && wordStr.at(i) != '@') // checks for punctuation and replaces them with spaces
				    {
				      wordStr.replace(i,1, " ");
			    
				      //  wordStr.at(i) = " ";
				    }
			
				  wordStr.at(i) = tolower(wordStr.at(i)); // makes all characters lowercase
				}
			    }
			}

		      if(!addBool)
			{
			  while(strcmp(tmpStr.c_str(), "*|*|*") != 0)
			    {
			      inStream >> tmpStr; // tweet
			    }
			  tweetStr = "";
			  //  std::cout << "2. BREAKING BECAUSE OF NON-ASCII CHARACTERS\n";
			  break;
			}



		      strStream.clear();
		      strStream << tmpStr;
			  
			  
			  
		      while(strStream >> tmpStr)
			{


			  if(strcmp(tmpStr.c_str(), "rt") == 0)
			    {

			      strStream >> tmpStr;

			      /*	      for(int i = 0; i < tmpStr.size(); i++)
					      {
					      if(tmpStr.at(i) == ':')
					      {
					      tmpStr.replace(i, 1, "_");
					      }
					      } */
			      if(strncmp(tmpStr.c_str(), "@", 1) == 0)
				{
				  retweet = 1;
				  retweetCount++;
				}
				  
			    }

			  if(strncmp(tmpStr.c_str(), "http://", 7) != 0)
			    {
			      tweetStr += tmpStr + " ";
			    }
			}

		      getline(inStream, tmpStr);  //tweet
		      //		      inStream >> tmpStr; 
		    }


		  if(tweetStr.size() > 0)
		    {
		      std::cout << "---" << retweet << "--" << tweetStr << "---\n";
		      outStream << retweet << " |tweetWords " << tweetStr << "\n";
		    }
		  else
		    {
		      //  std::cout << "***" << retweet << "--" << tweetStr << "---\n";
		    }
		}

	    }

	  std::cout << "Retweet count: " << retweetCount << "\n";

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
