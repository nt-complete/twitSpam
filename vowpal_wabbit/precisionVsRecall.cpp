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
  double truePos, posGuess, resultDbl, bothCount;
  double precision, recall;
  //  double perc = 21.6874;
  int bothTrue;


  resultStream.open("results.txt");
  outputStream.open("resultsToPlot.txt");
  if(!outputStream.is_open())
    {
      std::cout << "Problem opening output file. Exiting...\n";
      return 1;
    }

  outputStream << "# Precision\n";
  outputStream << "# Recall\n";

  if(resultStream.is_open())
    {
      

      inputStream.open("fixed_tweet_data.txt.output");
      if(inputStream.is_open())
	{
	  for(double perc = 0.01; perc < 1.0; perc += 0.01)
	    {

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

	      precision = (bothCount / posGuess);
	      recall = (bothCount / truePos);

	      //	      std::cout << perc << ": " << truePos << "/" << posGuess << " = " << (truePos/posGuess) << " \t\tBOTH: " << bothCount << "/" << posGuess << " = " << (bothCount/posGuess)<< "\n";
	      std::cout << "Precision: " << bothCount << "/" << posGuess << " = " << precision;
	      std::cout << "  Recall: " << bothCount << "/" << truePos << " = " << recall << "\n";

	      /*	      if(accuracy > .5)
		{
		  std::cout << perc << "\n";
		  }*/


	      outputStream << 100*recall << "\t" << 100*precision << "\n";
	      


	      inputStream.clear();
	      inputStream.seekg(0);

	      resultStream.clear();
	      resultStream.seekg(0);

	    }
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
