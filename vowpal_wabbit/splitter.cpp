#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  std::string tmpStr;
  std::ifstream infile;
  std::ofstream out1, out2, out3, out4, out5, out6, out7, out8;


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
  out5.open("split_tweets.txt.part5");
  out6.open("split_tweets.txt.part6");
  out7.open("split_tweets.txt.part7");
  out8.open("split_tweets.txt.part8");

  if(infile.is_open() && out1.is_open() && out2.is_open() && out3.is_open() && out4.is_open())
    {
      int i = 1;
      while(getline(infile, tmpStr))
	{
	  switch(i % 8)
	    {
	    case 7: out1 << tmpStr << "\n";
	      break;

	    case 6: out2 << tmpStr << "\n";
	      break;

	    case 5: out3 << tmpStr << "\n";
	      break;

	    case 4: out4 << tmpStr << "\n";
	      break;

	    case 3: out5 << tmpStr << "\n";
	      break;

	    case 2: out6 << tmpStr << "\n";
	      break;

	    case 1: out7 << tmpStr << "\n";
	      break;

	    case 0: out8 << tmpStr << "\n";
	      break;

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
