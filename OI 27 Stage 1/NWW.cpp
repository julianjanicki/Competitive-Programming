#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
const ll M = 1e5;
const ll MAX = 1e18;
unordered_map<ll,pair<ll,ll>> mapa;

void ranges()
{
    ll a,b,lcm,pom;
    for(ll i=1; i<=M; ++i)
    {
        a=i;
        lcm=i*(i+1);
        if(mapa[lcm].first != 0)
        {
            //if(mapa[lcm].first == 1 && mapa[lcm].second == 4) cout << lcm;
            if(mapa[lcm].first > i)
                mapa[lcm]= {i,i+1};
            else if(mapa[lcm].first == i && mapa[lcm].second > i+1)
                mapa[lcm]= {i,i+1};
        }
        else
            mapa[lcm]= {i,i+1};
        for(ll j=3; j<=43; ++j)
        {
            b=i+(j-1);
            ll gcd=__gcd(lcm,b);
            ll pom=lcm;
            lcm=pom*(b/gcd);
            //if(a==1855 && b==1860) cout << lcm << endl;
            if(lcm > MAX)
                break;
            if(mapa[lcm].first)
            {
                //if(mapa[lcm].first == 1 && mapa[lcm].second == 4) cout << lcm;
                if(mapa[lcm].first > a)
                    mapa[lcm]= {a,b};
                else if(mapa[lcm].first == a && mapa[lcm].second > b)
                    mapa[lcm]= {a,b};
            }
            else
                mapa[lcm]= {a,b};
            //mapa[lcm]={a,b};
        }
    }
}

pair<ll,ll> p(ll x) // UWAGA - ZLE PIERWAISTKI
{

    double p2=cbrt(2);
    double pnww=cbrt(x);
    ll temp=pnww;

    if(temp%2==0){
        if(temp*(temp+1)*(temp+2)/2 == x)
            return {temp, temp+2};}
    else{
        if(temp*(temp+1)*(temp+2) == x)
            return {temp, temp+2};}
    if((temp-1)%2==0){
        if((temp-1)*temp*(temp+1)/2 == x)
            return {temp-1, temp+1};}
    else{
        if((temp-1)*temp*(temp+1) == x)
            return {temp-1, temp+1};}

    //////////////////////////




    //////////////////////////
    temp=double(pnww)*double(p2);

    if(temp%2==0){
        if(temp*(temp+1)*(temp+2)/2 == x)
            return {temp, temp+2};}
    else{
        if(temp*(temp+1)*(temp+2) == x)
            return {temp, temp+2};}
    if((temp-1)%2==0){
        if((temp-1)*temp*(temp+1)/2 == x)
            return {temp-1, temp+1};}
    else{
        if((temp-1)*temp*(temp+1) == x)
            return {temp-1, temp+1};}
        ////////////////////////

    pair<ll,ll> dwa;
    dwa.first=floor(sqrt(x));
    dwa.second=floor(sqrt(x))+1;
    if(dwa.first*dwa.second == x)
        return dwa;

    return {0,0};



}


ll z,in;
vector<ll> tab;
pair<ll,ll> check;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ranges();
    cin >> z;
    while(z--)
    {
        cin >> in;
        tab.push_back(in);
    }
    for(auto u : tab)
    {
        //cout << mapa[3].first << " " << mapa[3].second << endl;
        //mapa[u]=mapa[u];
        //cout << mapa[12172006427981400].first << " " << mapa[12172006427981400].second << endl;
        //return 0;
        if(mapa[u].first == 0)
        {
            check=p(u);
            //cout << check.first << " " << check.second;
            if(check.first != 0 && check.first!=check.second)
                cout << check.first << " " << check.second << '\n';
            else
                cout << "NIE\n";
        }
        else
        {
            if(mapa[u].first != 0)
                cout << mapa[u].first << " " << mapa[u].second << '\n';
            else
                cout << "NIE\n";
        }
        //cout << mapa[u].first << " " << mapa[u].second << endl;
    }
    //double p2=pow(2,(double)1/3);
    //cout << "#" << p2 <<endl;
    return 0;
}
