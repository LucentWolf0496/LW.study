// 数组初探
#include <iostream>
using namespace std;

int main() {
    char str[1000];// ds给我提供的数组代码——初探数组概念！！
                   // 生成了一个数组
    cin.getline(str, 1000);
    
    int count_star = 0;
    int count_at = 0;
    
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '*')// 在数组中逐位读取
        {
            count_star++;
        } 
        else if (str[i] == '@')
        {
            count_at++;
        }
    }
    
    cout << "*出现了" << count_star << "次;" << endl;
    cout << "@出现了" << count_at << "次." << endl;
    
    return 0;
}