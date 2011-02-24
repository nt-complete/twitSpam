#include <iostream> 
#include <fstream>
#include <set>
#include <stdlib.h>

int main()
{
  std::ifstream inStream;
  std::string perc;
  std::set<double> percents;
  double percDbl;

  int i = 0;
  inStream.open("results.txt");

  if(inStream.is_open())
    {
      while(!inStream.eof())
	{
	  inStream >> perc;
	  percDbl = strtod(perc.c_str(), NULL);
	  percents.insert(percDbl);
	  i++;
	}

    }

  std::cout << "Count: " << i << "\n";

std::set<double>::iterator it = percents.end();

  it--;
  it--;

  std::cout << "Upper bound: " << *it << "\n";

  it = percents.begin();
  std::cout << "Lower bound: " << *it << "\n";
  
}
