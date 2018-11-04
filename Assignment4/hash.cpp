#include<bits/stdc++.h>
#include<string>
using namespace std;
typedef long long int ll;
ll maxi(ll a, ll b) {return a>b?a:b;}
ll mini(ll a, ll b) {return a<b?a:b;}
map <int,vector < string > > map_for_hashing;
ll hash_str(string s,int flag)
{
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
	cout<<(h%C+C)%C<<endl;
	return (h%C+C)%C;
}
void open(string filename, int M,int flag)
{
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
void hash_join(string file_name_R,string file_name_S,int blocks_allowed)
{
	map_for_hashing.clear();
	open(file_name_R,blocks_allowed,0);
	map_for_hashing.clear();
	open(file_name_S,blocks_allowed,1);
}
int main(int argc,char * argv[])
{
	cin.tie(0);cout.tie(0);
	if(argc<4)
	{
		cout<<"Invalid Arguments for Hash\n";
		exit(0);
	}
	string file_name_R,file_name_S,operation;
	file_name_R = argv[1];
	file_name_S = argv[2];
	int blocks_allowed = atoi(argv[3]);
	hash_join(file_name_R,file_name_S,blocks_allowed);
	return 0;
}
