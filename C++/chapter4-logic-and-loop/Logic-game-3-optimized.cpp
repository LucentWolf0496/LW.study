#include <iostream>
using namespace std;

int main() {
    for (int a_val = 1; a_val <= 3; a_val++) {
        for (int b_val = 1; b_val <= 3; b_val++) {
            if (a_val == b_val) continue;
            for (int c_val = 1; c_val <= 3; c_val++) {
                if (c_val == a_val || c_val == b_val) continue;
                
                int countA = (b_val > a_val) + (c_val == a_val);
                int countB = (a_val > b_val) + (a_val > c_val);
                int countC = (c_val > b_val) + (b_val > a_val);
                
                if (a_val < b_val) {
                    if (countA <= countB) continue;
                } else {
                    if (countA >= countB) continue;
                }
                if (a_val < c_val) {
                    if (countA <= countC) continue;
                } else {
                    if (countA >= countC) continue;
                }
                if (b_val < c_val) {
                    if (countB <= countC) continue;
                } else {
                    if (countB >= countC) continue;
                }
                
                char first, second, third;
                if (a_val == 3) first = 'A';
                else if (b_val == 3) first = 'B';
                else if (c_val == 3) first = 'C';
                
                if (a_val == 2) second = 'A';
                else if (b_val == 2) second = 'B';
                else if (c_val == 2) second = 'C';
                
                if (a_val == 1) third = 'A';
                else if (b_val == 1) third = 'B';
                else if (c_val == 1) third = 'C';
                
                cout << first << " > " << second << " > " << third << endl;
                return 0;
            }
        }
    }
    cout << "No answer." << endl;
    return 0;
}