#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n, m;

int main(){
	cin >> n >> m;
	int qposition[100001] = { 0 };
	bool first[100001] = { 0 };
	vector<vector<int>> friends(n+1);
	struct patient {
		int id;
		int date;
	};
	vector<patient> q;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		friends[x].push_back(y);
		friends[y].push_back(x);
	}
	patient zerop;
	cin >> zerop.id;
	zerop.date = 1;
	q.push_back(zerop);// 这个q数组是记录的感染事件，不用队列而用数组是为了计算感染时间差值3，保留前一次感染数据
	first[zerop.id] = 1;
	int head = 0;
	while (head < q.size()) {// 不再有新的感染事件就停下
		int t = q[head].id;
		for (int i = 0; i < friends[t].size(); i++) {
			int s = friends[t][i];
			if (first[s] == 0 || q[head].date - q[qposition[s]].date >= 3) {// 从未被感染或距上次感染超过3天
				first[s] = 1;// 一旦感染，由first标记不再是从未感染
				patient tmp;
				tmp.id = s;
				tmp.date = q[head].date + 1;
				qposition[s] = q.size();// 将上次感染存放到qposition数组
				q.push_back(tmp);
			}
		}
		head++;
	}
		cout << q[head-1].date;
		return 0;
}