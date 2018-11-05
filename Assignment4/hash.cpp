#include<bits/stdc++.h>
#include<string>
 #include <sys/stat.h>
using namespace std;

typedef long long int ll;

ll maxi(ll a, ll b) {return a>b?a:b;}
ll mini(ll a, ll b) {return a<b?a:b;}

map <int,vector < string > > map_for_hashing;

bool file_exists(string filename)
{
	/*
	Function for checking if file exists or not.
	*/
  ifstream ifile(filename);
  return (bool)ifile;
}

ll hash_str(string s,int flag)
{
	/*
	Finding the hash value and determining
	the hash-bucket for the tupple.
	*/
	char str[s.size()] ={0};
	strcpy(str,s.c_str());
    char delim[] = " ";
	char * prev_token;
	char *token = strtok(str,delim);
	if (flag == 0)
		while(token)
		{
			prev_token = token;
			token = strtok(NULL,delim);
		}
	else
		prev_token = token;

	ll h = 37;
	ll A = 54059;
	ll B = 76963;
	ll C = 86969;
	for (int i = 0; i < strlen(prev_token); ++i)
			h = (h * A) ^ ((prev_token[i]) * B)%C;
	return (h%C+C)%C;
}

void open(string filename, int M,int flag)
{
	/*
	Function for breaking down the
	main relation-file into smaller temporary files
	based the hash value
	*/
	ifstream inputstream(filename.c_str());
	string lines;

	while(getline(inputstream,lines))
	{

		int hash_block = (hash_str(lines,flag))%M;
		map_for_hashing[hash_block].push_back(lines);

		if (map_for_hashing[hash_block].size() == 100)
		{
			string fname;

			if (flag==0)
				fname = "temp_file_r" + to_string(hash_block) + ".txt";

			else
				fname = "temp_file_s" + to_string(hash_block) + ".txt";

			vector<string> record;
			record = map_for_hashing[hash_block];

			std::ofstream output_file(fname);
	    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	    std::copy(record.begin(), record.end(), output_iterator);
	    output_file.close();
	    record.clear();
			map_for_hashing[hash_block].clear();
		}

	}
	inputstream.close();

	map<int,vector<string> >::iterator it;

	for (it=map_for_hashing.begin();it!=map_for_hashing.end();it++)
	{
		if (!it->second.empty())
		{
			int num = it->first;
			vector<string> record = it->second;
			string fname;

			if (flag==0)
				fname = "temp_file_r" + to_string(num) + ".txt";
			else
				fname = "temp_file_s" + to_string(num) + ".txt";

			std::ofstream output_file(fname);
	    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	    std::copy(record.begin(), record.end(), output_iterator);

	    output_file.close();
	    record.clear();
	    it->second.clear();
		}
	}
	inputstream.close();
	return;
}

long GetFileSize(string filename)
{
	/*
	Function for finding the size of file
	*/
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

vector<string> getdata(string filename)
{
	/*
	Storing the data of the specified file
	in form of vector of strings.
	*/
	vector<string> ans;
	ifstream inputstream(filename.c_str());
	string lines;
	while(getline(inputstream,lines))
	{
		ans.push_back(lines);
	}
	inputstream.close();
	return ans;
}

vector<string> valid_file_list(int M)
{
	/*
	Get the list of all the files which are valid
	for performing hash-base join
	*/
	vector<string> valid_files;
	string r_fname = "temp_file_r";
	string s_fname = "temp_file_s";
	for (int i = 0; i < M; i++)
	{
		if (file_exists(r_fname + to_string(i)+".txt") && file_exists(s_fname + to_string(i)+".txt"))
		{
			string temp = to_string(i)+".txt";
			valid_files.push_back(temp);
		}
	}
	return valid_files;
}

string merge_tuple(string r, string s)
{
	char str_r[r.size()] = {0};
	strcpy(str_r,r.c_str());
	char str_s[s.size()] = {0};
	strcpy(str_s,s.c_str());
	char delim[] = " ";
	char *token_r;
	char *token_s;
	string ans;
	token_r = strtok(str_r,delim);
	while(token_r)
	{
		std::string temp(token_r);
		ans += temp + " ";
		token_r = strtok(NULL,delim);
	}
	token_s = strtok(str_s,delim);
	token_s = strtok(NULL,delim);
	while(token_s)
	{
		std::string temp(token_s);
		ans += temp + " ";
		token_s = strtok(NULL,delim);
	}
	return ans;
}
bool find_match(string r_string,string s_string)
{
	char str[r_string.size()] ={0};
	strcpy(str,r_string.c_str());
  char delim[] = " ";
	char *token_r;
	char *token_s;
	char *token = strtok(str,delim);

	while(token)
	{
		token_r = token;
		token = strtok(NULL,delim);
	}

	char str_s[s_string.size()] ={0};
	strcpy(str_s,s_string.c_str());
	token_s = strtok(str_s,delim);

	if (strcmp(token_r,token_s)==0)
		return true;
	else
		return false;
}
vector<string> join_files(int M)
{
	vector<string> valid_files;
	vector<string> in_memory;
	vector<string> after_join;
	string r_fname = "temp_file_r";
	string s_fname = "temp_file_s";
	int rf_size,sf_size,flag;

	valid_files = valid_file_list(M);
	for (int i = 0; i < valid_files.size(); i++)
	{
		int flag;
		rf_size = GetFileSize(r_fname+valid_files[i]);
		sf_size = GetFileSize(s_fname+valid_files[i]);
		ifstream inputstream;
		if(rf_size >= sf_size)
		{
			in_memory = getdata(r_fname+valid_files[i]);
			inputstream.open((s_fname+valid_files[i]).c_str());
			flag=0;
		}
		else
		{
			in_memory = getdata(s_fname+valid_files[i]);
			inputstream.open((r_fname+valid_files[i]).c_str());
			flag=1;
		}
		string lines,joined_tuple;
		while(getline(inputstream,lines))
		{
			for (int i = 0; i < in_memory.size(); i++)
			{
				if (flag==0)
				{
					if(find_match(in_memory[i],lines))
					{
						joined_tuple = merge_tuple(in_memory[i],lines);
						after_join.push_back(joined_tuple);
					}
				}
				else
				{
					if(find_match(lines,in_memory[i]))
					{
						joined_tuple = merge_tuple(lines,in_memory[i]);
						after_join.push_back(joined_tuple);
					}
				}
			}
		}
	}
	return after_join;
}
string get_file_name(string r)
{
	char str[r.size()] ={0};
	strcpy(str,r.c_str());
  char delim[] = "/";
	char delim2[] = ".";
	char * prev_token;
	char *token = strtok(str,delim);
	while(token)
	{
		prev_token = token;
		token = strtok(NULL,delim);
	}
	prev_token = strtok(prev_token,delim2);
	string temp(prev_token);
	return temp;
}
void output_to_file(string r,string s,vector<string> record)
{
	string fname;
	fname += get_file_name(r)+"_"+get_file_name(s)+"_join";
	if(file_exists(fname))
	{
		remove(fname.c_str());
		cout<<"Output file already exists. Overwriting it!!\n";
	}
	std::ofstream output_file(fname);
	std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(record.begin(), record.end(), output_iterator);
	output_file.close();
	record.clear();
}
void remove_temp_file(int M)
{
	string r = "temp_file_r";
	string s = "temp_file_s";
	for (int i = 0; i < M; i++)
	{
		if (file_exists(r + to_string(i)+".txt"))
		{
			if(remove((r + to_string(i)+".txt").c_str()))
			{
				cout<<"Error in deleting temporary files\n";
			}
		}
		if (file_exists(s + to_string(i)+".txt"))
		{
			if(remove((s + to_string(i)+".txt").c_str()))
			{
				cout<<"Error in deleting temporary files\n";
			}
		}
	}
}
void hash_join(string file_name_R,string file_name_S,int blocks_allowed)
{
	map_for_hashing.clear();
	open(file_name_R,blocks_allowed,0);
	map_for_hashing.clear();
	open(file_name_S,blocks_allowed,1);
	vector<string> after_join = join_files(blocks_allowed);
	output_to_file(file_name_R,file_name_S,after_join);
	remove_temp_file(blocks_allowed);

}
int main(int argc,char * argv[])
{
	cin.tie(0);cout.tie(0);
	if(argc<4)
	{
		cout<<"Invalid Arguments for Hash\nHow To Use:./a.out <R_filename> <S_filename> <no_of_blocks_allowed>\n";
		exit(0);
	}
	string file_name_R,file_name_S,operation;
	file_name_R = argv[1];
	file_name_S = argv[2];
	int blocks_allowed = atoi(argv[3]);
	hash_join(file_name_R,file_name_S,blocks_allowed);
	return 0;
}
