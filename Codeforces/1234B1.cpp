// https://codeforces.com/contest/1234/problem/B1
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll M = 200;
ll n,k,t[M+5];
queue<ll> s;
unordered_map<ll,bool> mapa;
vector<ll> v;
int main()
{
	cin >> n >> k;
	for(ll i=1; i<=n; i++)
	{
		cin >> t[i];
	}
 
	for(ll i=1; i<=n; i++)
	{
		if(mapa[t[i]]) continue;
		else if(s.size() == k)
		{
			mapa[(ll)s.front()]=0;
			s.pop();
			s.push(t[i]);
			mapa[t[i]]=1;	
		}
		else
		{
			s.push(t[i]);
			mapa[t[i]]=1;
		}
	}
 
	while(!s.empty())
	{
		v.push_back(s.front());
		s.pop();
	}
 
	cout << v.size() << endl;
 
	//sort(v.begin(), v.end(), greater<ll>());
 
	for(ll i=v.size()-1; i>=0; i--)
		cout << v[i] << " ";
	return 0;
}
