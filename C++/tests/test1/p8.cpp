#include <iostream>
#include <vector>
using namespace std;



int main(){
    do {
        int n = 0;
        cin >> n;
        if (n == 0)
            return 0; 

        vector<pair<int , int>> list;
        for (int i = 0 ; i < n ; i ++){
            int a , b;
            cin >> a >> b;
            list.push_back ({a , b});
        }

        int xmin = 0 , xmax = 0 , ymin = 0 , ymax = 0;
        for (int i = 0 ; i < n ; i ++){
            if (list[i].first > xmax)
                xmax = list[i].first;
            if (list[i].first < xmin)
                xmin = list[i].first;
            if (list[i].second > ymax)
                ymax = list[i].second;
            if (list[i].second < ymin)
                ymin = list[i].second;
        }
        
        for (int i = 0 ; i < n - 1 ; i ++){
            if (list[i].first == list[i + 1].first && list[i].second < list[i + 1].second){
                if (list[i].first > xmin)
                    xmin = list[i].first;
            }
            if (list[i].first == list[i + 1].first && list[i].second > list[i + 1].second){
                if (list[i].first < xmax)
                    xmax = list[i].first;
            }
            if (list[i].second == list[i + 1].second && list[i].first < list[i + 1].first){
                if (list[i].second < ymax)
                    ymax = list[i].second;
            }
            if (list[i].second == list[i + 1].second && list[i].first > list[i + 1].first){
                if (list[i].second > ymin)
                    ymin = list[i].second;
            }
        }

        if (xmin <= xmax && ymin <= ymax)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
            
    }while(1);
}