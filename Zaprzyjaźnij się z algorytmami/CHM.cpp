#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll M = 5e5,R = 524288;
ll n,tab[M+5],tree[2*R+5],q,a,b;

ll query(ll x, ll y){
    x+=R-1;
    y+=R-1;
    if(x == y)
        return tree[x];
    ll wyn=min(tree[x],tree[y]);
    while(x/2 != y/2){
        if(x%2 == 0){
            wyn=min(wyn,tree[x+1]);
        }
        if(y%2 == 1){
            wyn=min(wyn,tree[y-1]);
        }
        x/=2;
        y/=2;
    }
    return wyn;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for(int i=0; i<n; i++){
        cin >> tab[i];
        tree[i+R]=tab[i];
    }
    for(int i=R-1; i>=1; i--){
        tree[i]=min(tree[i*2], tree[i*2+1]);
    }
    while(q--){
        cin >> a >> b;
        cout << query(a,b) << '\n';
    }
    return 0;
}
