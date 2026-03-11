#include<iostream>
#include<vector>
using namespace std;

struct nut{
    int x;
    int y;
    int sum;
};

int main(){
    int epoch = 0;
    cin >> epoch;
    for (int i = 0 ; i < epoch ; i ++){
        int m = 0 , n = 0 , k = 0;
        cin >> m >> n >> k;
        vector<vector<int>> table(m , vector<int>(n));
        for (int i = 0 ; i < m ; i ++){
            for (int j = 0 ; j < n ; j ++){
                cin >> table[i][j];
            }
        }

        vector<nut> record;
        for (int i = 0 ; i < m ; i ++){
            for (int j = 0 ; j < n ; j ++){
                record.push_back({i , j , table[i][j]});
            }
        }
        for (int i = 1 ; i < m * n ; i ++){
            for (int j = 0 ; j < m * n - i ; j ++){
                if (record[j].sum < record[j + 1].sum){
                    nut temp = record[j];
                    record[j] = record[j + 1];
                    record[j + 1] = temp;
                }
            }
        }

        if (k < record[0].x * 2 + 2 + 1){
            cout << 0 << endl;
        }

        else{
            int step = 0;
            int time = record[0].x + 1 + 1;
            int result = record[0].sum;
            bool check = false;
            while (step < record.size() - 1){
                time += abs(record[step].x - record[step + 1].x) + abs(record[step].y - record[step + 1].y) + 1 + record[step + 1].x + 1;

                if (time > k){
                    cout << result << endl;
                    check = true;
                    break;
                }

                result += record[step + 1].sum;
                time -= record[step + 1].x + 1;
                step ++;
            }
            if (!check)
                cout << result << endl;
        }
    }
    return 0;
}