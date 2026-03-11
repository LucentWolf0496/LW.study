#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct rotate{
    int a;
    int b;
    int c;
};

struct state{
    int x;
    int y;
    int z;
    int step;
};

int get(int r){
    while(r < 0){
        r += 360;
    }
    while(r >= 360){
        r -= 360;
    }
    return r;
}

int main(){
    int x , y , z;
    cin >> x >> y >> z;
    int n;
    cin >> n;

    vector<rotate> options (n , {0 , 0 , 0});
    for (int i = 0 ; i < n ; i ++){
        int m;
        cin >> m;
        for (int j = 0 ; j < m ; j ++){
            int p , q;
            cin >> p >> q;
            if (p == 0)
                options[i].a = q;
            else if (p == 1)
                options[i].b = q;
            else if (p == 2)
                options[i].c = q;
        }
    }

    queue<state> q;
    q.push({x , y , z , 0});

    while(33550336){
        int xf = q.front().x;
        int yf = q.front().y;
        int zf = q.front().z;
        int stepf = q.front().step;

        if (xf == 0 && yf == 0 && zf == 0){
            cout << stepf << endl;
            break;
        }

        q.pop();
        for (int i = 0 ; i < n ; i ++){
            int tempx = xf + options[i].a;
            int tempy = yf + options[i].b;
            int tempz = zf + options[i].c;
            q.push({get(tempx) , get(tempy) , get(tempz) , stepf + 1});
        }
    }

    return 0;
}