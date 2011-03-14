#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  std::string tmpStr;
  std::ifstream infile;
  std::ofstream out1, out2, out3, out4;


  if(argc < 2)
    {
      std::cout << "Please use input as argument.\n";
      return 1;

    }


  infile.open(argv[1]);
  out1.open("split_tweets.txt.part1");
  out2.open("split_tweets.txt.part2");
  out3.open("split_tweets.txt.part3");
  out4.open("split_tweets.txt.part4");

  if(infile.is_open() && out1.is_open() && out2.is_open() && out3.is_open() && out4.is_open())
    {
      int i = 1;
      while(getline(infile, tmpStr))
	{
	  switch(i % 4)
	    {
	    case 3: out1 << tmpStr << "\n";
	      break;

	    case 2: out2 << tmpStr << "\n";
	      break;

	    case 1: out3 << tmpStr << "\n";
	      break;

	    case 0: out4 << tmpStr << "\n";
	      break;

	    }

	  i++;
	}

      out1.close();
      out2.close();
      out3.close();
      out4.close();
      infile.close();
    }
  else
    {
      std::cout << "Error opening files.\n";
      return 1;
    }

}
