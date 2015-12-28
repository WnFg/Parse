#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <string>
#include <map>
using namespace std;

bool comp(const string& s1, const string& s2, int ii){      // 检查s1是否为字符串s2[ii]~s2[s2.size()]的前缀
	int i, j;
	if(ii + s1.size() > s2.size()) return false;
	//cout << "sdfgwert" << endl;
	for(i = 0, j = ii; i < s1.size(); i++, j++){
		if(s1[i] != s2[j])
			return false;
	}
	return true;
}

struct CFG
{
	string S;
	vector<string> NT, T;
	vector<string> P, spt;
	map< string, vector<string> > mp;
	
	CFG(){
		cout << "输入非结束符,以0结束：" << endl;
		string str;
		while(cin >> str && str != "0"){
			NT.push_back(str);	
		}

		cout << "输入结束符，以0结束：" << endl;
		while(cin>> str && str != "0"){
			T.push_back(str);
		}

		cout << "输入开始符，以0结束：" << endl;
		while(cin >> str && str != "0"){
			S = str;
		}

		cout << "输入表达式，每行为一条表达式，以0结束：" << endl;
		while(cin >> str && str != "0"){
			P.push_back(str);
		}
	}

	void split(const string& str){
		int mark;
		bool ok;
		for(mark = 0; mark < NT.size(); mark++){
			if( comp(NT[mark], str, 0) ){
				mp[NT[mark]] = spt;	
				break;
			}
		}

		for(int i = NT[mark].size(); i < str.size(); i++)
		{
			ok = false;
			for(int j = 0; !ok && j < NT.size(); j++)
			{
				if( comp(NT[j], str, i) )
				{
				//	cout << "dsfgwer" << endl;
					mp[NT[mark]].push_back(NT[j] + "`");
					ok = true;
					i += NT[j].size() - 1;
				}	
			}
	//		cout << "sdfwer" << endl;
			for(int j = 0; !ok && j < T.size(); j++)
			{
				if( comp(T[j], str, i) ){
				//	cout << "sdfee" << endl;
					mp[NT[mark]].push_back(T[j]);
					ok = true;
					i += T[j].size() - 1;
				}
			}
		}
	}

	void analysis_P(){
		for(int i = 0; i < P.size(); i++){
			split(P[i]);		
		}
	}
	
};
CFG *cfg = new CFG;
int main()
{
//	init();
	cfg->analysis_P();
//	cout << "sdfsdf" << endl;
	for(int i = 0; i < cfg->NT.size(); i++){
		vector<string> &tt = cfg->mp[ cfg->NT[i] ];
		for(int j = 0; j < tt.size(); j++){
			cout << tt[j] << endl;
		}
	}
	return 0;
}
