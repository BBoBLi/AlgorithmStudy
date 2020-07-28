#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;
vector<bool> check(9, false);
	
void Answer(int toPick, int lastPick)
{
	if(toPick==0)
	{
		for(auto p:arr)
			cout<<p<<' ';
		cout<<'\n';
		return;
	}
	
	for(int i=lastPick+1; i<=n; i++)
	{
		if(check[i]) continue;
		
		check[i]=true;
		arr.push_back(i);
		Answer(toPick-1, i);
		arr.pop_back();
		check[i]=false;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin>>n>>m;
	
	Answer(m, 0);
	
	return 0;
}
