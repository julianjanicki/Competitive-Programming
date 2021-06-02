#include <bits/stdc++.h>
using namespace std;

vector<pair<pair<int,int>,pair<int,int>>> graf;
bool odw[1005][1005],zamiana=false;
int n,m,k,xd,yd,xg,yg,path,znak;

bool parzysta(int x){
    if(x%2 == 0)
        return 1;
    return 0;
}

void min_parzysta(){
    int a,b;

    /* POZIOMO */
    a=n/2;
    b=1;
    while(b < m){
        graf.push_back({{a,b},{a,b+1}});
        odw[a][b]=1;
        b++;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY

    /* PIONOWO W DOL */
    a=n/2;
    b=1;
    while(a < n){
        graf.push_back({{a,b},{a+1,b}});
        odw[a][b]=1;
        a++;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY
    xd=a,yd=b+1;

    /* PIONOWO W GORE */
    a=n/2;
    b=m;
    while(a > 1){
        graf.push_back({{a-1,b},{a,b}});
        odw[a][b]=1;
        a--;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY
    graf.push_back({{a,b},{a,b-1}});
    odw[a][b-1]=1;
    xg=a,yg=b-2;
}

void min_nieparzysta(){
    int a,b;
    if(parzysta(n)){
        swap(n,m);
        zamiana=true;
    }

    /* POZIOMO */
    a=n/2+1;
    b=1;
    while(b < m){
        graf.push_back({{a,b},{a,b+1}});
        odw[a][b]=1;
        b++;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY

    /* PIONOWO W DOL */
    a=n/2+1;
    b=1;
    while(a < n){
        graf.push_back({{a,b},{a+1,b}});
        odw[a][b]=1;
        a++;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY
    xd=a,yd=b+1;

    /* PIONOWO W GORE */
    a=n/2+1;
    b=m;
    while(a > 1){
        graf.push_back({{a-1,b},{a,b}});
        odw[a][b]=1;
        a--;
    }
    odw[a][b]=1; // -> BRAKUJACE DOLACZAMY
    xg=a,yg=b-1;
}

void max_path(){
    /* GORA */
    znak=-1;
    while(true){
        if(graf.size() == k)
            break;
        else if(odw[xg][yg] && znak == 1){
            yg--;
            if(odw[xg+1][yg])
                break;
            else{
                xg++;
                odw[xg][yg]=1;
                graf.push_back({{xg,yg},{xg-1,yg}});
                znak=-znak;
            }
        }
        else if(yg < 1 && znak == -1){
            yg++;
            if(odw[xg+1][yg])
                break;
            else{
                xg++;
                odw[xg][yg]=1;
                graf.push_back({{xg,yg},{xg-1,yg}});
                znak=-znak;
            }
        }
        else{
            odw[xg][yg]=1;
            if(znak == -1)
                graf.push_back({{xg,yg},{xg,yg+1}});
            else
                graf.push_back({{xg,yg},{xg,yg-1}});
        }
        yg+=znak;
    }
    /* DOL */
    znak=1;
    while(true){
        if(graf.size() == k)
            break;
        else if(odw[xd][yd] && znak == -1){
            yd++;
            if(odw[xd-1][yd])
                break;
            else{
                xd--;
                odw[xd][yd]=1;
                graf.push_back({{xd,yd},{xd+1,yd}});
                znak=-znak;
            }
        }
        else if(yd > m && znak == 1){
            yd--;
            if(odw[xd-1][yd])
                break;
            else{
                xd--;
                odw[xd][yd]=1;
                graf.push_back({{xd,yd},{xd+1,yd}});
                znak=-znak;
            }
        }
        else{
            odw[xd][yd]=1;
            if(znak == -1)
                graf.push_back({{xd,yd},{xd,yd+1}});
            else
                graf.push_back({{xd,yd},{xd,yd-1}});
        }
        yd+=znak;
    }
}

void one(){
    if(n == 1){
        if(k != m-1)
            cout << "NIE";
        else{
            cout << "TAK\n";
            for(int i=1; i<m; i++){
                cout << n << " " << i << " " << n << " " << i+1 << '\n';
            }
        }
    }
    else if(m == 1){
        if(k != n-1)
            cout << "NIE";
        else{
            cout << "TAK\n";
            for(int i=1; i<n; i++){
                cout << i << " " << m << " " << i+1 << " " << m << '\n';
            }
        }
    }
}

void widly(int x){
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(!odw[j][i]){
                if(j < x){
                    graf.push_back({{j,i},{j+1,i}});
                }
                if(j > x){
                    graf.push_back({{j,i},{j-1,i}});
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    if(n == 1 || m == 1){
        one();
        return 0;
    }
    else if(n == 2 && m == 2){
        if(k == 3)
            cout << "TAK\n1 1 2 1\n1 1 1 2\n1 2 2 2"; 
        else
            cout << "NIE";
        return 0;
    }
    else if(n == 2 && parzysta(m)){
        swap(n,m);
        zamiana=1;
        min_parzysta();
        max_path();
        widly(n/2);
    }
    else if(parzysta(n) && parzysta(m)){
        if(k < n+m-1 || k > m*n-1){
            cout << "NIE";
            return 0;
        }
        min_parzysta();
        max_path();
        widly(n/2);
    }
    else if(!parzysta(n) || !parzysta(m)){
        if(k < n+m-2 || k > m*n-1){
            cout << "NIE";
            return 0;
        }
        min_nieparzysta();
        max_path();
        widly(n/2+1);
    }
    cout << "TAK\n";
    if(zamiana){
        for(auto u : graf){
            cout << u.first.second << " " << u.first.first << " " << u.second.second << " " << u.second.first << '\n';
        }
    }
    else{
        for(auto u : graf){
            cout << u.first.first << " " << u.first.second << " " << u.second.first << " " << u.second.second << '\n';
        }
    }
    /*for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cout << odw[i][j] << " ";
        }
        cout << "\n";
    }*/
        
    return 0;
}
