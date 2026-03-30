#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

string warr[5] = { "dragon","ninja","iceman","lion","wolf" };
string colorr[2] = { "red","blue" };
string weapon[3] = { "sword","bomb","arrow" };
//int redorder[] = { 2,3,4,1,0 }, blueorder[] = { 3,0,1,2,4 };
int warrior_num[2][5] = { 0 }, total_w_num[2] = { 0 }, loc[2] = { 0 }, dx[2] = { 1,-1 };
int inithp[5] = { 0 }, initatt[5] = { 0 };
int M, N, K, T;
int minute = 0;

string t(int minute);

class weapons;

class warriors {
	static int warnum;
	friend class side;
public:
	bool alive = 1;
	vector<weapons*> w;
	string name;
	int id, clas;
	int hp, col, att, loca;
	warriors(int ord, int sid, int rest_hp) {
		clas = ord;
		loca = loc[sid];
		hp = inithp[ord];
		name = warr[ord];
		att = initatt[ord];
		col = sid;
		total_w_num[sid]++;
		id = total_w_num[sid];
		cout << t(minute) << " " << colorr[sid] << " " << name << " " << id << " born" << endl;
	}
	
	virtual bool run() {
		return false;
	}
	virtual void march() {
		return;
	}
	virtual void seizewep(warriors* opp,int cityid) {
		return;
	}
	virtual void yell(int cityid) {};
};

string t(int minute) {
	int h = minute / 60;
	int m = minute % 60;
	string s = "000:00";
	
	s[0] += h / 100;
	s[1] += (h % 100) / 10;
	s[2] += h % 10;
	s[4] += m / 10;
	s[5] += m % 10;
	return s;
}

//武器部分
class weapons {
public:
	int ord;
	int att;
	int used;
	warriors* user;
	weapons(int od, warriors* me) {
		ord = od;
		user = me;
		att = 0;
		used = 0;
	}
	virtual void use(warriors* oppo) {
		oppo->hp -= att;
		if (oppo->hp < 0)
			oppo->hp = 0;
		used -= 1;
	}
};
bool cmp_use(weapons* w1, weapons* w2) {
	if (w1->ord != w2->ord)
		return w1->ord < w2->ord;
	return w1->used < w2->used;
}

bool cmp_get(weapons* w1, weapons* w2) {
	if (w1->ord != w2->ord)
		return w1->ord < w2->ord;
	return w1->used > w2->used;
}

class sword : public weapons {
public:
	sword(int ord, int current_att, warriors* me) :weapons(ord, me) {
		used = -1;
		att = current_att / 5;
	}
};
class bomb :public weapons {
public:
	bomb(int ord, int current_att, warriors* me) :weapons(ord, me) {
		used = 1;
		att = current_att * 2 / 5;
	}
	void use(warriors* oppo) {
		oppo->hp -= att;
		if (oppo->hp < 0)
			oppo->hp = 0;
		if (user->clas != 1) {
			user->hp -= (att / 2);
			if (user->hp < 0)
				user->hp = 0;
		}
		used -= 1;
	}
};
class arrow :public weapons {
public:
	arrow(int ord, int current_att, warriors* me) :weapons(ord, me) {
		used = 2;
		att = current_att * 3 / 10;
	}
};
weapons* createweapon(int id, int current_att, warriors* me) {
	if (id == 0)
		return new sword(id, current_att, me);
	if (id == 1)
		return new bomb(id, current_att, me);
	if (id == 2)
		return new arrow(id, current_att, me);
}


class dragon :public warriors {
public:
	static int num;
	double morale = 0;
	dragon(int ord, int sid, int rest_hp) :warriors(ord, sid, rest_hp) {
		num++;
		weapons* w0 = createweapon(id % 3, att, this);
		w.push_back(w0);
		morale = 1.0 * rest_hp / inithp[0];
	}
	~dragon() {
		num--;
	}
	void yell(int cityid) {
		cout << t(minute) << " " << colorr[col] << " dragon " << id << " yelled in city " << cityid << endl;
	}
};
int dragon::num = 0;
class ninja :public warriors {
	weapons* w0[2];
public:
	static int num;
	ninja(int ord, int sid, int rest_hp) :warriors(ord, sid, rest_hp) {
		num++;
		w0[0] = createweapon(id % 3, att, this);
		w0[1] = createweapon((id + 1) % 3, att, this);
		w.push_back(w0[0]);
		w.push_back(w0[1]);
	}
	~ninja() {
		num--;
	}
};
int ninja::num = 0;
class iceman :public warriors {
	weapons* w0;
public:
	static int num;
	iceman(int ord, int sid, int rest_hp) :warriors(ord, sid, rest_hp) {
		num++;
		w0 = createweapon(id % 3, att, this);
		w.push_back(w0);
	}
	~iceman() {
		num--;
	}
	void march() {
		hp = hp * 9 / 10;
		if (hp <= 0)
			alive = 0;
	}
};
int iceman::num = 0;

class lion : public warriors {
	int loyalty = 0;
	weapons* w0;
public:
	static int num;

	lion(int ord, int sid, int rest_hp) :warriors(ord, sid, rest_hp) {
		num++;
		w0 = createweapon(id % 3, att, this);
		w.push_back(w0);
		loyalty = rest_hp;
		cout << "Its loyalty is " << loyalty << endl;
	}
	~lion() {
		num--;
	}
	bool run() {
		if (loyalty <= 0 && loca != loc[1 - col])
			return true;
		return false;
	}
	void march() {
		loyalty -= K;
	}
};
int lion::num = 0;

class wolf :public warriors {
public:
	static int num;
	wolf(int ord, int sid, int rest_hp) :warriors(ord, sid, rest_hp) {
		num++;
	};
	~wolf() {
		num--;
	}
	void seizewep(warriors* opp, int cityid) {
		if (opp->clas == clas)
			return;
		if (opp->w.size() > 0) {
			sort(opp->w.begin(), opp->w.end(), cmp_get);
			int miniid = opp->w[0]->ord;
			int p = 0;
			while (w.size()<10 && opp->w.size()>0 && opp->w[0]->ord == miniid) {
				p++;
				w.push_back(opp->w[0]);
				opp->w.erase(opp->w.begin());
			}
			cout << t(minute) << " " << colorr[col] << " wolf " << id << " took " << p << " " << weapon[miniid] << " from " << colorr[1 - col] << " " << opp->name << " " << opp->id << " in city " << cityid << endl;
		}
		return;
	}
};
int wolf::num = 0;
warriors* createwarrior(int ord, int sid, int rest_hp) {
	if (ord == 0)
		return new dragon(ord, sid, rest_hp);
	if (ord == 1)
		return new ninja(ord, sid, rest_hp);
	if (ord == 2)
		return new iceman(ord, sid, rest_hp);
	if (ord == 3)
		return new lion(ord, sid, rest_hp);
	if (ord == 4)
		return new wolf(ord, sid, rest_hp);
}

void getwep(warriors* winner, warriors* loser) {
	if (loser->w.size() > 0) {
		sort(loser->w.begin(), loser->w.end(), cmp_get);
		while (winner->w.size() < 10 && loser->w.size() > 0) {
			winner->w.push_back(loser->w[0]);
			loser->w.erase(loser->w.begin());
		}
	}
}


class cities {
public:
	warriors* war[2];
	cities() {
		war[0] = NULL;
		war[1] = NULL;
	}
};
vector<cities> city(22);

class side { //0为红方，1为蓝方
public:
	int color, totalhp, p;
	string color_name;
	int order[5] = { 0 };


	bool making = 1;
	vector<warriors*> war;
	bool getmaking() {
		return making;
	}
	side(int t, int M) {
		p = 4;
		color = t;
		totalhp = M;
		if (t == 0) {
			color_name = "red";
			order[0] = 2;
			order[1] = 3;
			order[2] = 4;
			order[3] = 1;
			order[4] = 0;
		}
		else {
			color_name = "blue";
			order[0] = 3;
			order[1] = 0;
			order[2] = 1;
			order[3] = 2;
			order[4] = 4;
		}
	}
	void try_to_make() {
		making = 0;
		p = (p + 1) % 5;
		if (inithp[order[p]] <= totalhp) {
			making = 1;
			making_warriors();
		}
		if (making == 0)
			stop_making();
	}

	void making_warriors() {
		warrior_num[color][order[p]]++;
		int od = order[p];
		totalhp -= inithp[od];
		war.push_back(createwarrior(od, color, totalhp));
		city[loc[color]].war[color] = war[war.size() - 1];
	}
	void stop_making() {
		//cout << t(tim, 0) << " " << color_name << " headquarter stops making warriors" << endl;
	}
};

bool ifsomeonedied(warriors* w1, warriors* w2, int cityid);
void battle(warriors* w1, warriors* w2, int cityid) {
	int p1 = 0, p2 = 0;
	sort(w1->w.begin(), w1->w.end(), cmp_use);
	sort(w2->w.begin(), w2->w.end(), cmp_use);
	int last_hp1 = w1->hp, last_hp2 = w2->hp;
	int last_size1 = w1->w.size(), last_size2 = w2->w.size();
	int no_change_count = 0;

	while (w1->hp > 0 && w2->hp > 0 && (w1->w.size() > 0 || w2->w.size() > 0)) {
		bool changed = 0;
		if (w1->w.size() > 0) {
			if (p1 == w1->w.size())
				p1 = 0;
			w1->w[p1]->use(w2);
			if (w2->hp != last_hp2) changed = true;
			if (w1->w[p1]->used == 0)
				w1->w.erase(w1->w.begin() + p1);
			else
				p1++;
			if (ifsomeonedied(w1, w2, cityid)) {
				return;
			}
				
		}
		if (w2->w.size() > 0) {
			if (p2 == w2->w.size())
				p2 = 0;
			w2->w[p2]->use(w1); 
			if (w1->hp != last_hp1) changed = true;

			if (w2->w[p2]->used == 0)
				w2->w.erase(w2->w.begin() + p2);
			else
				p2++;
			if (ifsomeonedied(w1, w2, cityid))
				return;
		}
		if (!changed && w1->hp == last_hp1 && w2->hp == last_hp2 &&
			w1->w.size() == last_size1 && w2->w.size() == last_size2) {
			no_change_count++;
			if (no_change_count >= 2) {  // 连续两轮无变化，判定平局
				break;
			}
		}
		else {
			no_change_count = 0;
			last_hp1 = w1->hp;
			last_hp2 = w2->hp;
			last_size1 = w1->w.size();
			last_size2 = w2->w.size();
		}
	}
	if (w1->hp > 0 && w2->hp > 0) {
		if (w1->col == 0) {
			cout << t(minute) << " both red " << w1->name << " " << w1->id << " and blue " << w2->name << " " << w2->id << " were alive in city " << cityid << endl;
			w1->yell(cityid);
			w2->yell(cityid);
		}
		else {
			cout << t(minute) << " both red " << w2->name << " " << w2->id << " and blue " << w1->name << " " << w1->id << " were alive in city " << cityid << endl;
			w1->yell(cityid);
			w2->yell(cityid);
		}
	}
}

bool ifsomeonedied(warriors* w1, warriors* w2, int cityid) {
	if (w1->hp <= 0 && w2->hp > 0) {
		cout << t(minute) << " " << colorr[w2->col] << " " << w2->name << " " << w2->id << " killed " << colorr[w1->col] << " " << w1->name << " " << w1->id << " in city " << cityid << " remaining " << w2->hp << " elements" << endl;
		getwep(w2, w1);
		w2->yell(cityid);
		w1->alive = 0;
		return 1;
	}
	else if (w1->hp > 0 && w2->hp <= 0) {
		cout << t(minute) << " " << colorr[w1->col] << " " << w1->name << " " << w1->id << " killed " << colorr[w2->col] << " " << w2->name << " " << w2->id << " in city " << cityid << " remaining " << w1->hp << " elements" << endl;
		getwep(w1, w2);
		w1->yell(cityid);
		w2->alive = 0;
		return 1;
	}
	else if (w1->hp <= 0 && w2->hp <= 0) {
		w1->alive = 0;
		w2->alive = 0;
		if (w1->col == 0)
			cout << t(minute) << " both " << colorr[w1->col] << " " << w1->name << " " << w1->id << " and " << colorr[w2->col] << " " << w2->name << " " << w2->id << " died in city " << cityid << endl;
		else
			cout << t(minute) << " both " << colorr[w2->col] << " " << w2->name << " " << w2->id << " and " << colorr[w1->col] << " " << w1->name << " " << w1->id << " died in city " << cityid << endl;
		return 1;
	}
	return 0;
}

int main() {
	int tms;
	cin >> tms;
	for (int _t = 1; _t <= tms; _t++) {
		bool over = 0;
		minute = 0;
		cin >> M >> N >> K >> T;
		for (int i = 0; i <= N + 1; i++)
			city[i] = cities();
		cout << "Case " << _t << ":" << endl;
		
		loc[0] = 0;
		loc[1] = N + 1;
		for (int i = 0; i < 5; i++)
			cin >> inithp[i];
		for (int i = 0; i < 5; i++)
			cin >> initatt[i];
		lion::num = 0; ninja::num = 0; wolf::num = 0; iceman::num = 0; dragon::num = 0;
		memset(warrior_num, 0, sizeof(warrior_num));
		memset(total_w_num, 0, sizeof(total_w_num));
		side s[2] = { side(0, M), side(1, M) };

		while (minute <= T && !over) {
			int mi = minute % 60;
			if (mi == 0) {
				if (s[0].getmaking())
					s[0].try_to_make();
				if (s[1].getmaking())
					s[1].try_to_make();
			}

			if (mi == 5) {
				for (int c = 0; c <= N + 1; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						if (city[c].war[cl] != NULL) {
							if (city[c].war[cl]->alive && city[c].war[cl]->run()) {
								city[c].war[cl]->alive = 0;
								cout << t(minute) << " " << colorr[cl] << " lion " << city[c].war[cl]->id << " ran away" << endl;
								city[c].war[cl] = NULL;
							}
						}
					}
				}
			}

			if (mi == 10) {
				vector<cities> tmpcity(N + 2);
				for (int c = 0; c <= N + 1; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						if (city[c].war[cl] != NULL) {
							city[c].war[cl]->march();
							if (!city[c].war[cl]->alive) {
								city[c].war[cl] = NULL;
								continue;
							}
							city[c].war[cl]->loca += dx[cl];
							
							tmpcity[city[c].war[cl]->loca].war[cl] = city[c].war[cl];
							//cout << t(minute) << " " << colorr[cl] << " " << city[c].war[cl]->name << " " << city[c].war[cl]->id << " marched to city " << city[c].war[cl]->loca << " with " << city[c].war[cl]->hp << " elements and force " << city[c].war[cl]->att << endl;
						}
					}
				}
				/*for (int c = 0; c <= N + 1; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						if (city[c].war[cl] != NULL) {
							if (city[c].war[cl]->loca == loc[1 - cl]) {
								cout << t(minute) << " " << colorr[cl] << " " << city[c].war[cl]->name << " " << city[c].war[cl]->id << " reached " << colorr[1 - cl] << " headquarter with " << city[c].war[cl]->hp << " elements and force " << city[c].war[cl]->att << endl;
								cout << t(minute) << " " << colorr[1 - cl] << " headquarter was taken" << endl;
								over = 1;
								break;
							}
						}
					}
					if (over)
						break;
				}
				if (over)
					break;*/
				if (tmpcity[0].war[1]) {
					cout << t(minute) << " " << colorr[1] << " " << tmpcity[0].war[1]->name << " " << tmpcity[0].war[1]->id << " reached " << colorr[0] << " headquarter with " << tmpcity[0].war[1]->hp << " elements and force " << tmpcity[0].war[1]->att << endl;
					cout << t(minute) << " " << colorr[0] << " headquarter was taken" << endl;
					over = 1;
				}
				for (int c = 0; c <= N + 1; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						city[c].war[cl] = tmpcity[c].war[cl];
						if (city[c].war[cl] && c != 0 && c != N + 1)
							cout << t(minute) << " " << colorr[cl] << " " << city[c].war[cl]->name << " " << city[c].war[cl]->id << " marched to city " << city[c].war[cl]->loca << " with " << city[c].war[cl]->hp << " elements and force " << city[c].war[cl]->att << endl;
					}
				}
				
				if (city[N + 1].war[0]) {
					cout << t(minute) << " " << colorr[0] << " " << city[N+1].war[0]->name << " " << city[N+1].war[0]->id << " reached " << colorr[1] << " headquarter with " << city[N+1].war[0]->hp << " elements and force " << city[N+1].war[0]->att << endl;
					cout << t(minute) << " " << colorr[1] << " headquarter was taken" << endl;
					over = 1;
				}
			}

			if (mi == 35) {
				for (int c = 1; c <= N; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						if (city[c].war[cl] && city[c].war[1 - cl])
							city[c].war[cl]->seizewep(city[c].war[1 - cl], c);
					}
				}
			}

			
			if (mi == 40) {
				for (int c = 1; c <= N; c++) {
					if (city[c].war[0] && city[c].war[1]) {
						if (c % 2 == 1)
							battle(city[c].war[0], city[c].war[1], c);
						else
							battle(city[c].war[1], city[c].war[0], c);
						if (!city[c].war[0]->alive)
							city[c].war[0] = NULL;
						if (!city[c].war[1]->alive)
							city[c].war[1] = NULL;
					}
				}
			}

			if (mi == 50) {
					cout << t(minute) << " " << s[0].totalhp << " elements in red headquarter" << endl;
					cout << t(minute) << " " << s[1].totalhp << " elements in blue headquarter" << endl;
			}

			if (mi == 55) {
				for (int c = 0; c <= N + 1; c++) {
					for (int cl = 0; cl <= 1; cl++) {
						if (city[c].war[cl] && city[c].war[cl]->alive) {
							int sw = 0, bo = 0, ar = 0;
							for (int k = 0; k < city[c].war[cl]->w.size(); k++) {
								if (city[c].war[cl]->w[k]->ord == 0)
									sw++;
								else if (city[c].war[cl]->w[k]->ord == 1)
									bo++;
								else if (city[c].war[cl]->w[k]->ord == 2)
									ar++;
							}
							cout << t(minute) << " " << colorr[cl] << " " << city[c].war[cl]->name << " " << city[c].war[cl]->id << " has " << sw << " sword " << bo << " bomb " << ar << " arrow and " << city[c].war[cl]->hp << " elements" << endl;
						}
					}
				}
			}
			minute += 5;

		}
	}
	return 0;
}