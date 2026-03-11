#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int n = 0 , count = -1 , step = 0;// 强制转-1从而确保后续0/visit的+2可以通用，小技巧
    cin >> n;
    vector<int> game(n + 2 , 0);
    vector<int> visit(n + 2 , 0);
    for (int i = 1 ; i <= n ; i ++){
        cin >> game[i];
    }

    visit[0] = 1;
    while(visit[n + 1] == 0){
        if (game[step] == 0 || visit[step] >= 2){
            count ++;
            count ++;
            step ++;
            visit[step] += 1;
        }
        else{
            if (step + game[step] >= n + 1){
                count ++;
                step = n + 1;
                visit[step] += 1;
            }
            else if (step + game[step] <= 0){
                count ++;
                step = 0;
                visit[step] += 1;
            }
            else{
                count ++;
                step += game[step];
                visit[step] += 1;
            }
        }
    }

    cout << count << endl;
}