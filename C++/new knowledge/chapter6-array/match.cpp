#include <iostream>
#include <cstring>
using namespace std;

char a[50], b[50];
int la, lb, count;

void input_data()
{
    cin >> a;
    cin >> b;
}

void solve()
{
    bool match;
    la = strlen(a);
    lb = strlen(b);
    count = 0;
    for (int i = 0 ; i <= lb - la ; i ++)
    {
        match = true;
        for (int j = 0 ; j < la ; j ++)
        {
            if (a[j] != b[i + j])
            {
                match = false;
                break;
            }
        }
        if (match)
            count ++;
    }
}

void output_data ()
{
    if (count == 0)
        cout << "a不是b的子串"  << endl;
    else
        cout << "a在b中出现了" << count << "次" << endl;
}

int main()
{
    input_data();
    solve();
    output_data();
}