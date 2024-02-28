#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int L, Q;

class Query{
    public:
        int cmd, t, x, n;
        string name;

        Query(int cmd, int t, int x, string name, int n){
            this->cmd = cmd;
            this->t = t;
            this->x = x;
            this->name = name;
            this->n = n;
        }
};

vector<Query> queries;

set<string> names;

map<string, vector<Query>> p_queries;

map<string, int> entry_time;

map<string, int> position;

map<string, int> exit_time;

bool cmp(Query q1, Query q2){
    if(q1.t != q2.t){
        return q1.t < q2.t;
    }
    return q1.cmd < q2.cmd;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> L >> Q;
    for(int i = 0; i < Q; i++){
        int cmd = -1;
        int t = -1, x = -1, n = -1;
        string name;
        cin >> cmd;
        if(cmd == 100){
            cin >> t >> x >> name;
        }else if(cmd == 200){
            cin >> t >> x >> name >> n;
        }else{
            cin >> t;
        }

        queries.push_back(Query(cmd, t, x, name, n));

        if(cmd == 100){
            p_queries[name].push_back(Query(cmd, t, x, name, n));
        }else if(cmd == 200){
            names.insert(name);
            entry_time[name] = t;
            position[name] = x;
        }
    }

    for(string name : names){
        exit_time[name] = 0;

        for(Query q: p_queries[name]){
            int time_to_removed = 0;
            if(q.t < entry_time[name]){
                int t_sushi_x = (q.x + (entry_time[name] - q.t)) % L;
                int additional_time = (position[name] - t_sushi_x + L) % L;

                time_to_removed = entry_time[name] + additional_time;
            }else{
                int additional_time = (position[name] - q.x + L) % L;
                time_to_removed = q.t + additional_time;
            }

            exit_time[name] = max(exit_time[name], time_to_removed);

            queries.push_back(Query(111, time_to_removed, -1, name, -1));
        }
    }


    for(string name : names){
        queries.push_back(Query(222, exit_time[name], -1, name, -1));
    }

    sort(queries.begin(), queries.end(), cmp);

    int people_num = 0, sushi_num = 0;
    for(int i = 0; i < (int) queries.size(); i++){
        if(queries[i].cmd == 100){
            sushi_num++;
        }else if(queries[i].cmd == 111){
            sushi_num--;
        }else if(queries[i].cmd == 200){
            people_num++;
        }else if(queries[i].cmd == 222){
            people_num--;
        }else{
            cout << people_num << " " << sushi_num <<"\n";
        }
    }

    return 0;
}