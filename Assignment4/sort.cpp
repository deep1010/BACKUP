#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll maxi(ll a, ll b) {return a>b?a:b;}
ll mini(ll a, ll b) {return a<b?a:b;}
bool file_exists(string filename)
{
	/*
	Function for checking if file exists or not.
	*/
  ifstream ifile(filename);
  return (bool)ifile;
}
string get_attr_key(string a, int flag)
{
	char str_a[a.size()] ={0};
	strcpy(str_a,a.c_str());
  char delim[] = " ";
	char* prev_token;
	char* token = strtok(str_a,delim);
	if(flag==0)
	{
		while(token)
		{
			prev_token = token;
			token = strtok(NULL,delim);
		}
	}
	else
	{
		prev_token = token;
	}
	string temp(prev_token);
	return temp;
}
bool comp_r(string a,string b)
{
	string x,y;
	x = get_attr_key(a,0);
	y = get_attr_key(b,0);
	return x < y;
}
bool comp_s(string a,string b)
{
	string x,y;
	x = get_attr_key(a,1);
	y = get_attr_key(b,1);
	return x < y;
}
vector<string> get_file_data(string R)
{
	ifstream inputstream(R.c_str());
	string line;
	vector<string> data;
	while(getline(inputstream,line))
		data.push_back(line);

	return data;
}
vector<int> create_sub_file(string R,string S,int M)
{
	vector<string> data_r = get_file_data(R);
	vector<string> data_s = get_file_data(S);
	int blocks_r = (data_r.size()+99)/100;
	int blocks_s = (data_s.size()+99)/100;
	int sublists_r = ceil(blocks_r/M);
	int sublists_s = ceil(blocks_s/M);
	int i,j;
	vector<string> record;
	vector<int> sub_data;
	for ( i = 0; i <=sublists_r; i++)
	{
		record.clear();

		for (j = M*100*i; j < M*100*(i+1) && j < data_r.size(); j++)
			record.push_back(data_r[j]);
		if(record.empty())
		{
			sublists_r--;
			continue;
		}
		sort(record.begin(),record.end(),comp_r);

		string fname = "temp_file_r" + to_string(i)+".txt";

		std::ofstream output_file;
		output_file.open(fname);  //use this for appending fstream::app
		std::ostream_iterator<std::string> output_iterator(output_file, "\n");
		std::copy(record.begin(), record.end(), output_iterator);

		output_file.close();
		record.clear();
	}

	for ( i = 0; i <=sublists_s; i++)
	{
		record.clear();

		for (j = M*100*i; j < M*100*(i+1) && j < data_s.size(); j++)
			record.push_back(data_s[j]);
		if(record.empty())
		{
			sublists_s--;
			continue;
		}
		sort(record.begin(),record.end(),comp_s);

		string fname = "temp_file_s" + to_string(i)+".txt";

		std::ofstream output_file;
		output_file.open(fname);  //use this for appending fstream::app
		std::ostream_iterator<std::string> output_iterator(output_file, "\n");
		std::copy(record.begin(), record.end(), output_iterator);

		output_file.close();
		record.clear();
	}
	sub_data.push_back(sublists_r);
	sub_data.push_back(sublists_s);
	return sub_data;
}
int get_min_r(vector<string>::iterator itr[],vector<string>::iterator end[],int n)
{
	int flag;
	for (int i = 0; i <= n; ++i)
	{
		if (itr[i]!=end[i])
		{
			flag =i;
			break;
		}
	}
	for (int i = 0; i <=n; ++i)
	{
		if( itr[i]!=end[i] && comp_r( *itr[i],*itr[flag]))
			flag = i;
	}
	return flag;
}
int get_min_s(vector<string>::iterator itr[],vector<string>::iterator end[],int n)
{
	int flag;
	for (int i = 0; i <= n; ++i)
	{
		if (itr[i]!=end[i])
		{
			flag =i;
			break;
		}
	}
	for (int i = 0; i <=n; ++i)
	{
		if( itr[i]!=end[i] && comp_s( *itr[i],*itr[flag]))
			flag = i;
	}
	return flag;
}
bool check_end(vector<string>::iterator itr[],vector<string>::iterator end[],int n)
{
	// cout<<"entering check_end\n";
	for (int i = 0; i <= n; ++i)
	{
		if (itr[i] < end[i])
		{
			// cout<<"exiting check_end\n";
			return false;
		}
	}
	// cout<<"exiting check_end\n";
	return true;
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
vector<string> merge_file(vector<int> data,int M)
{
	int sublists_r = data[0];
	int sublists_s = data[1];
	vector<string> after_merge;
	vector<string> data_r[sublists_r+1];
	vector<string> data_s[sublists_s+1];
	vector<string>::iterator it_r[sublists_r+1];
	vector<string>::iterator it_s[sublists_s+1];
	vector<string>::iterator end_r[sublists_r+1];
	vector<string>::iterator end_s[sublists_s+1];
	for (int i = 0; i <= sublists_r; ++i)
	{
		string fname = "temp_file_r"+to_string(i)+".txt";
		data_r[i] = get_file_data(fname);
	}
	for (int i = 0; i <= sublists_s; ++i)
	{
		string fname = "temp_file_s"+to_string(i)+".txt";
		data_s[i] = get_file_data(fname);
	}
	for (int i = 0; i <= sublists_r; ++i)
	{
		it_r[i] = data_r[i].begin();
		end_r[i] = data_r[i].end();
	}
	for (int i = 0; i <= sublists_s; ++i)
	{
		it_s[i] = data_s[i].begin();
		end_s[i] = data_s[i].end();
	}
	while(1)
	{
		if(check_end(it_r,end_r,sublists_r) || check_end(it_s,end_s,sublists_s))
		{
			break;
		}
		int idr = get_min_r(it_r,end_r,sublists_r);
		int ids = get_min_s(it_s,end_s,sublists_s);
		string x = *(it_r[idr]);
		string y = *(it_s[ids]);
		if(find_match(x,y))
		{
			after_merge.push_back(merge_tuple(x,y));
			it_s[ids]++;
		}
		else
		{
			it_r[idr]++;
		}
	}
	return after_merge;
}
void print(vector<string>::iterator b,vector<string>::iterator e)
{
	vector<string>::iterator it;
	for (it = b; it !=e; ++it)
	{
		cout<<*it<<endl;
	}
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
void remove_temp_file(int r_size,int s_size)
{
	string r = "temp_file_r";
	string s = "temp_file_s";
	for (int i = 0; i <=r_size; i++)
	{
		if (file_exists(r + to_string(i)+".txt"))
		{
			if(remove((r + to_string(i)+".txt").c_str()))
			{
				cout<<"Error in deleting temporary files\n";
			}
		}
	}
	for (int i = 0; i <=s_size; ++i)
	{
		if (file_exists(s + to_string(i)+".txt"))
		{
			if(remove((s + to_string(i)+".txt").c_str()))
			{
				cout<<"Error in deleting temporary files\n";
			}
		}
	}
}
void sort_join(string file_R,string file_S,int M) {
	vector<int> get_sub_data = create_sub_file(file_R,file_S,M);
	vector<string> data = merge_file(get_sub_data,M);
	output_to_file(file_R,file_S,data);
	remove_temp_file(get_sub_data[0],get_sub_data[1]);
}
int main(int argc, char* argv[])
{
	cin.tie(0);cout.tie(0);
	if(argc<4)
	{
		cout<<"Invalid Arguments for Sort\nHow To Use:./a.out <R_filename> <S_filename> <no_of_blocks_allowed>\n";
		exit(0);
	}
	string file_name_R,file_name_S;
	file_name_R = argv[1];
	file_name_S = argv[2];
	int blocks_allowed = atoi(argv[3]);
	sort_join(file_name_R,file_name_S,blocks_allowed);
	return 0;
}
