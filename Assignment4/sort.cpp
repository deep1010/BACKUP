#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll maxi(ll a, ll b) {return a>b?a:b;}
ll mini(ll a, ll b) {return a<b?a:b;}
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
	// int cnt=0;
	while(getline(inputstream,line))
	{
		data.push_back(line);
	}
	return data;
}
void create_sub_file(string R,string S,int M)
{
	vector<string> data_r = get_file_data(R);
	vector<string> data_s = get_file_data(S);
	int blocks_r = (data_r.size()+99)/100;
	int blocks_s = (data_s.size()+99)/100;
	int sublists_r = ceil(blocks_r/M);
	int sublists_s = ceil(blocks_s/M);
	int i,j;

	vector<string> record;
	for ( i = 0; i <=sublists_r; i++)
	{
		record.clear();

		for (j = M*100*i; j < M*100*(i+1) && j < data_r.size(); j++)
			record.push_back(data_r[j]);

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

		sort(record.begin(),record.end(),comp_s);

		string fname = "temp_file_s" + to_string(i)+".txt";

		std::ofstream output_file;
		output_file.open(fname);  //use this for appending fstream::app
		std::ostream_iterator<std::string> output_iterator(output_file, "\n");
		std::copy(record.begin(), record.end(), output_iterator);

		output_file.close();
		record.clear();
	}

}
void sort_join(string file_R,string file_S,int M) {
	create_sub_file(file_R,file_S,M);
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
