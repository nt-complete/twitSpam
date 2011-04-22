#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  std::string tmpStr;
  std::ifstream infile;
  std::ofstream out1, out2, out3, out4, out5, out6, out7, out8;


  if(argc < 3)
    {
      std::cout << "Please input file to split and name to save.\n";
      return 1;

    }
  std::string outStr1, outStr2, outStr3, outStr4;

  outStr1 = argv[2];
  outStr1 += ".txt.part1";

  outStr2 = argv[2];
  outStr2 += ".txt.part2";

  outStr3 = argv[2];
  outStr3 += ".txt.part3";

  outStr4 = argv[2];
  outStr4 += ".txt.part4";

  infile.open(argv[1]);
  out1.open(outStr1.c_str());
  out2.open(outStr2.c_str());
  out3.open(outStr3.c_str());
  out4.open(outStr4.c_str());


  /*  out5.open("split_tweets.txt.part5");
  out6.open("split_tweets.txt.part6");
  out7.open("split_tweets.txt.part7");
  out8.open("split_tweets.txt.part8");*/

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

	      /*	    case 3: out5 << tmpStr << "\n";
	      break;

	    case 2: out6 << tmpStr << "\n";
	      break;

	    case 1: out7 << tmpStr << "\n";
	      break;

	    case 0: out8 << tmpStr << "\n";
	    break;*/


	    }

	  i++;
	}

      out1.close();
      out2.close();
      out3.close();
      out4.close();
      out5.close();
      out6.close();
      out7.close();
      out8.close();
      infile.close();
    }
  else
    {
      std::cout << "Error opening files.\n";
      return 1;
    }

}
