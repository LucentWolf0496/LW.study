#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    string temp;
    vector<string> list;
    while(cin >> temp){
        list.push_back(temp);
    }

    int n = list.size();
    for (int i = 0; i < n; i++) {
        string word = list[i];
        cout << word << " ";
        
        // 尝试从长度1到单词完整长度的前缀
        for (int prefix_len = 1; prefix_len <= word.length(); prefix_len++) {
            string prefix = word.substr(0, prefix_len);
            bool is_unique = true;
            
            // 检查这个前缀在其他单词中是否唯一
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    // 如果其他单词的前缀长度至少和当前前缀一样长，且前缀匹配
                    if (list[j].length() >= prefix_len && 
                        list[j].substr(0, prefix_len) == prefix) {
                        is_unique = false;
                        break;
                    }
                }
            }
            
            // 如果找到了唯一的前缀，输出并跳出循环
            if (is_unique) {
                cout << prefix;
                break;
            }
            
            // 如果到了单词末尾还没找到唯一前缀，就输出整个单词
            if (prefix_len == word.length()) {
                cout << word;
                break;
            }
        }
        cout << endl;
    }

    return 0;
}