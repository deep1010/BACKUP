#include <bits/stdc++.h>
using namespace std;
bool file_exists(string filename)
{
  ifstream ifile(filename);
  return (bool)ifile;
}
int count_lines(string fname)
{
  ifstream inputstream(fname.c_str());
  string line;
  int line_count=0;
  while(getline(inputstream,line))
  {
    line_count++;
  }
  return line_count;
}
bool check_block_overflow(string r,string s,int M)
{
  int r_count = (count_lines(r)+99)/100;
  int s_count = (count_lines(s)+99)/100;
  if(r_count + s_count < M*M)
    return false;
  else
    return true;
}
int main(int argc,char * argv[])
{
	if(argc<5)
	{
		cout<<"How to use:\n./20161010.sh <path of R file> <path of S file> <sort/hash> <M>\n";
		exit(0);
	}
	else
	{
		string file_name_R,file_name_S,operation;
		file_name_R = argv[1];
		file_name_S = argv[2];
		operation = argv[3];
		int blocks_allowed = atoi(argv[4]);
		if(!file_exists(file_name_R))
		{
			cout<<file_name_R + "not found\n";
			exit(0);
		}
		if(!file_exists(file_name_S))
		{
			cout<<file_name_S + "not found\n";
			exit(0);
		}
    if (check_block_overflow(file_name_R,file_name_S,blocks_allowed)){
      cout<<"Memory Allocated is insufficient\n";
      exit(0);
    }
		if (operation == "sort")
		{
			// cout<<"INSIDE SORT\n";
			system("g++ -std=c++11 -o _sort_ sort.cpp");
			string arguments = "./_sort_ ";
			arguments += file_name_R + " ";
			arguments += file_name_S + " ";
			arguments += to_string(blocks_allowed);
			system(arguments.c_str());
      system("rm _sort_");
		}
		else if (operation == "hash")
		{
			// cout<<"INSIDE HASH\n";
			system("g++ -std=c++11 -o _hash_ hash.cpp");
			string arguments = "./_hash_ ";
			arguments += file_name_R + " ";
			arguments += file_name_S + " ";
			arguments += to_string(blocks_allowed);
			system(arguments.c_str());
      system("rm _hash_");
		}
		else
		{
			cout<<"Invalid Operation type:" + operation + "\n" +"How to use:\n./20161010.sh <path of R file> <path of S file> <sort/hash> <M>\n";
			exit(0);
		}
	}
	return 0;
}
