#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <set>


int main()
{
  std::ifstream resultStream;
  std::ifstream inputStream;

  std::ofstream outputStream;
  std::string result, inputStr, tmpStr;
  double truePos, posGuess, resultDbl, bothCount, perc;
  double precision, recall;
  int bothTrue;

  
  resultStream.open("results.txt");
  outputStream.open("resultsToPlot.txt");
  if(!outputStream.is_open())
    {
      std::cout << "Problem opening output file. Exiting...\n";
      return 1;
    }

  // outputStream << "# Accuracy\n";
  // outputStream << "# Certainty\n";

  if(resultStream.is_open())
    {
      

      inputStream.open("fixed_tweet_data.txt.output");
      if(inputStream.is_open())
	{

	  double base, cap;
	  base = 0.0;
	  cap = 1.0;


	  for( int i = 0; i < 20; i++)
	    {

	      perc = (base + cap) / 2;

	      truePos = posGuess = 0.0;
	      bothTrue = bothCount = 0;

	      while(!inputStream.eof() && !resultStream.eof())
		{
		  bothTrue = 0;
		  resultStream >> result;
		  getline(inputStream, inputStr);
		  //		  std::cout << inputStr << "\n";
		  //		  std::cin >> tmpStr;


		  resultDbl = atof(result.c_str());
		  if(resultDbl >= perc)
		    {
		      posGuess++;
		      bothTrue++;
		    }

		  if(inputStr.at(0) == '1')
		    {
		      truePos++;
		      bothTrue++;
		    }

		  if(bothTrue == 2)
		    bothCount++;


		}
	      //	      std::cout << perc << ": " << truePos << "/" << posGuess << " = " << (truePos/posGuess) << " \t\tBOTH: " << bothCount << "/" << posGuess << " = " << (bothCount/posGuess)<< "\n";
	      
	      double accuracy = (bothCount/posGuess);
	      if(accuracy > .500001)
		{
		  cap = perc;
		  perc = (base + cap) / 2;

		}

	      if(accuracy < .500001)
		{
		  base = perc;
		  perc = (base + cap) / 2;

		}



	      // outputStream << perc << "\t" << accuracy << "\n";
	      


	      inputStream.clear();
	      inputStream.seekg(0);

	      resultStream.clear();
	      resultStream.seekg(0);

	    }
		  std::cout << perc << "\n";
	}

      inputStream.close();
      resultStream.close();
      outputStream.close();

    }
  else
    {
      std::cout << "Problem opening results.txt.\n";
      return 1;
    }
}
