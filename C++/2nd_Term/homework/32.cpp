#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();
    map<int, list<int>> seqs;
    
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "new") {
            int id;
            iss >> id;
            seqs[id] = list<int>();
        } 
        else if (cmd == "add") {
            int id, num;
            iss >> id >> num;
            seqs[id].push_back(num);
        } 
        else if (cmd == "merge") {
            int id1, id2;
            iss >> id1 >> id2;
            if (id1 != id2) {
                seqs[id1].splice(seqs[id1].end(), seqs[id2]);
            }
        } 
        else if (cmd == "unique") {
            int id;
            iss >> id;
            auto& lst = seqs[id];
            if (!lst.empty()) {
                lst.sort();
                lst.unique();
            }
        } 
        else if (cmd == "out") {
            int id;
            iss >> id;
            auto& lst = seqs[id];
            vector<int> v(lst.begin(), lst.end());
            sort(v.begin(), v.end());
            for (size_t j = 0; j < v.size(); ++j) {
                if (j) cout << " ";
                cout << v[j];
            }
            cout << endl;
        }
    }
    return 0;
}