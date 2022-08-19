/** 
*@ c(2022), ComplusoryEduFish
*@ Console Vision
*@ Input all subjects data, and the program gives a list of all accessible combinations of subject in demand.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
using namespace std;

struct Time{
    int iWeekBeg, iWeekEnd;
    int iWeekDay;
    int iSecBeg, iSecEnd;
};

struct Item{
    string strName; // 课程名
    string strClass; // 课程开设班级
    vector<Time> vecTime;
    int iLimitNum;
    int iVoteNum;
};

vector <
    pair <string/*课程名*/, vector<Item>/*同名课程的各项*/>
> subjects;
int iSbjNum;
vector<Item> stkTemp;

void input() {
    cout << "input subjects num" << endl;
    cin >> iSbjNum;
    subjects.resize(iSbjNum);

    for (int i = 0; i < iSbjNum; ++ i) {
        cout << "input name of NO." << i+1 << " subject" << endl;
        cin >> subjects[i].first;
        int iItemNum;
        cout << "input item num" << endl;
        cin >> iItemNum;
        subjects[i].second.resize(iItemNum);

        for (int j = 0; j < iItemNum; ++ j) {
            auto& item = subjects[i].second[j];
            item.strName = subjects[i].first;
            cout << "input the class of NO." << j+1 << " item" << endl;
            cin >> item.strClass;
            cout << "input limit popularity of item" << endl;
            cin >> item.iLimitNum;
            cout << "input voter num of item" << endl;
            cin >> item.iVoteNum;
            int iTimeNum;
            cout << "input time gap num" << endl;
            cin >> iTimeNum;
            item.vecTime.resize(iTimeNum);

            for (int k = 0; k < iTimeNum; ++ k) {
                auto& time = item.vecTime;
                cout << "As for No." << k+1 << " time gap" << endl;
                cout << "input start week" << endl;
                cin >> time[k].iWeekBeg;
                cout << "input end week" << endl;
                cin >> time[k].iWeekEnd;
                cout << "input weekday" << endl;
                cin >> time[k].iWeekDay;
                cout << "input start section" << endl;
                cin >> time[k].iSecBeg;
                cout << "input end section" << endl;
                cin >> time[k].iSecEnd;
            }
        }
    }
}

void outStk() {
    cout << "Solution" << endl;
    for (auto& it : stkTemp) {
        cout << it.strName << ' ' << it.strClass << endl;
    }
}

bool overlayyer(int sbjCur, int itemCur) {
    auto& item = subjects[sbjCur].second[itemCur];
    for (auto& time : item.vecTime) {
        for (auto& itemTemp : stkTemp) {
            for (auto& stkTime : itemTemp.vecTime) {
                if (time.iWeekBeg > stkTime.iWeekEnd || time.iWeekEnd < stkTime.iWeekBeg)
                    ;
                else if (time.iWeekDay != stkTime.iWeekDay)
                    ;
                else if (time.iSecBeg > stkTime.iSecEnd || time.iSecEnd < stkTime.iSecBeg)
                    ;
                else
                    return true;
            }
        }
    }
    return false;
}

void dfs(int step) {
    if (step >= iSbjNum) {
        outStk();
        return ;
    }
    
    for (int i = 0; i < subjects[step].second.size(); ++ i) {
        if (!overlayyer(step, i)) {
            stkTemp.push_back(subjects[step].second[i]);
            dfs(step+1);
            stkTemp.pop_back();
        }
    }
}

int main() {
    input();
    dfs(0);
    return 0;
}
