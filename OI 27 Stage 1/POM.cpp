#include <bits/stdc++.h> 
using namespace std;

string as,bs;
vector<int>wyn,a,b;
int z,ile,rowne;
int start=-1;

void fast(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
}

int main() 
{
    fast();
    cin >> z;
    while(z--){
        cin >> as >> bs >> ile;
        a.clear();
        b.clear();
        for(auto u : as)
            a.push_back(u-48);
        for(auto u : bs)
            b.push_back(u-48);
        rowne=0;
        wyn.clear();
        for(int i=0; i<b.size(); i++){
            wyn.push_back(b[i]);
            //cout << b.size() << endl;
            if(b[i] != a[i])
                rowne++;
        }
        //cout << wyn;
        start=-1;
 
        for(int i=b.size()-1; i>=0; i--){
            if(!(b[i] == a[i]))
                rowne--;

            if(b[i]){
                //cout << ile << " " << rowne << endl;;
               if((b[i] > a[i] && ile == rowne) || (ile > rowne)){
                    if(i-rowne <= b.size()-ile){
                        //cout << b.size() << endl;
                        ile=ile-rowne;
                        start=i;
                        if(!ile)
                            wyn[i]=a[i];
                        else{
                            if(a[i]+1 != b[i]){
                                ile-=1;
                                wyn[i]=b[i]-1;
                            }
                            else if(a[i]+1 == b[i]){
                                if(b.size()-i != ile)
                                    wyn[i]=a[i];
                                else{
                                    if(!a[i] && b[i] == 1){
                                        ile=ile+rowne;
                                        start=-1;
                                        continue;
                                    }
                                    ile-=1;
                                    wyn[i]=b[i]-2;
                                }
                            }
                        }
                        break;
                    }
                } 
            } 
        }

        if(start == -1)
            cout << start << '\n';
        else{
            start+=1;
            for(start; start < b.size(); start++){
                if(!ile)
                    wyn[start]=a[start];
                else{
                    wyn[start]=9;
                    if(wyn[start] != a[start])
                        ile-=1;
                    else if(b.size()-start == ile && a[start] == 9){
                        ile-=1;
                        wyn[start]=8;
                    }
                }
            }
            for(auto u : wyn)
                cout << u;
            cout << '\n';
        }
    }

    return 0; 
}
