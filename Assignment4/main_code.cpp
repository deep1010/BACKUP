#include <bits/stdc++.h>
using namespace std;
bool file_exists(string filename)
{
  ifstream ifile(filename);
  return (bool)ifile;
}

int main(int argc,char * argv[])
{
	if(argc<5)
	{
		cout<<"How to use:\n./20161010.sh <path of R file> <path of S file> <sort/hash> <M>";
		exit(0);
	}
	else
	{
		string file_name_R,file_name_P,operation;
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
		if (operation == "sort")
		{
			cout<<"INSIDE SORT\n";
			system("g++ -std=c++11 -o sort sort.cpp");
			string arguments = "./sort ";
			arguments += file_name_R + " ";
			arguments += file_name_S + " ";
			arguments += operation + " ";
			arguments += to_string(blocks_allowed);
			system(arguments.c_str());

		}
		else if (operation == "hash")
		{
			cout<<"INSIDE HASH\n";
			system("g++ -std=c++11 -o hash hash.cpp");
			string arguments = "./hash ";
			arguments += file_name_R + " ";
			arguments += file_name_S + " ";
			arguments += to_string(blocks_allowed);
			system(arguments.c_str());
		}
		else
		{
			cout<<"Invalid Operation type:" + operation + "\n" +"How to use:\n./20161010.sh <path of R file> <path of S file> <sort/hash> <M>\n";
			exit(0);
		}
	}
	return 0;
}
