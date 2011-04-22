#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <set>


int main(int argc, char ** argv)
{
  std::ifstream resultStream;
  std::ifstream inputStream;

  std::ofstream outputStream, thresholdStream;
  std::string result, inputStr, tmpStr;
  double truePos, posGuess, resultDbl, bothCount;
  double precision, recall;
  //  double perc = 21.6874;
  int bothTrue;
  int i = 1;


  if(argc < 4)
    {
      std::cout << "Expected input:\nOriginal_file results_file name_to_append_to_resultsToPlot.\n";
      return 1;

    }
  resultStream.open(argv[2]);
  std::string resultsName;
  resultsName = argv[3] ;
  resultsName += "_resultsToPlot.txt";
  outputStream.open(resultsName.c_str());
  std::cout << resultsName << "\n";
  resultsName = argv[3] ;
  resultsName += "_thresholdPlot.txt";
  thresholdStream.open(resultsName.c_str());
  std::cout << resultsName << "\n";


  if(!outputStream.is_open())
    {
      std::cout << "Problem opening output file. Exiting...\n";
      return 1;
    }

  outputStream << "# Precision\n";
  outputStream << "# Recall\n";


  if(resultStream.is_open())
    {
      inputStream.open(argv[1]);
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

		  /*		  if(inputStr.size() == 0)
				  break; */
		  if(inputStr.size() <= 0)
		    break;
		  resultDbl = atof(result.c_str());
		  if(resultDbl >= perc)
		    {
		      posGuess++;
		      bothTrue++;
		    }
		  //		  std::cout << "_" << inputStr << "_\n";
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

	      if( posGuess > 0.0 && truePos > 0.0 )
		{
		  outputStream << 100*recall << "\t" << 100*precision << "\n";
		  thresholdStream << 100*precision << "\t" << perc*100 << "\n";
		  //outputStream << 100*precision << "\t" << 100*recall << "\n";
		}


	      inputStream.clear();
	      inputStream.seekg(0);

	      resultStream.clear();
	      resultStream.seekg(0);

	    }
	}

      inputStream.close();
      resultStream.close();
      outputStream.close();
      thresholdStream.close();
    }
  else
    {
      std::cout << "Problem opening results.txt.\n";
      return 1;
    }
}
