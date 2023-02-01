#define pii pair<int,int>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>


using namespace std;


class CardLib
{
    public:
        CardLib();
        double* checkWinRate(double* ret, int c1[], int c2[], int n);
    private:
        map<string, int> typeMap;
        int checkWin(pair<string, vector<int>> h1, pair<string, vector<int>> h2);
        pair<string, vector<int>> checkType(vector<int>);

};

CardLib::CardLib(){
    this->typeMap={{"FlOr",9}, {"Four",8}, {"FuHo",7}, {"Flus",6}, {"Orde",5}, {"Thre",4}, {"TwPa",3}, {"Pair",2}, {"High",1}};
}

pair<string, vector<int>> CardLib::checkType(vector<int> c1){
    /*
    ordered as: A->12, 2->0
    Type: FlOr, Four, FuHo, Flus, Orde, Thre, TwPa, Pair, High
    */
    vector<int> num(13);
    map<int, vector<int>> memo;
    bool flu=false, ord=false;
    int ord_v=-1, flu_f=-1;


    sort(c1.begin(),c1.end(),
        [](int a, int b){return a%13<b%13; });
    // for(int i=0;i<c1.size();i++) c1[i]--;

    for(int i:c1) num[i%13]++;
    for(int i=0;i<num.size();i++){
        for(int j=num[i];j>0;j--){
            memo[j].push_back(i);
        }
    }

    vector<vector<int>> f_memo(4);
    for(int i=0;i<c1.size();i++){
        int tmp=c1[i]/13;
        f_memo[tmp].push_back(c1[i]);
        if(f_memo[tmp].size()>=5){flu=true;flu_f=tmp;}
    }

    int c=1;
    for(int i=1;i<c1.size();i++){
        int tmp = c1[i]%13-c1[i-1]%13;
        if(tmp == 1) c++;
        else if(tmp==0);
        else c=1;
        if(c>=5) {ord=true; ord_v=c1[i]%13;}
    }
    if(!ord && (num[12]&&num[0]&&num[1]&&num[2]&&num[3])){ord=true;ord_v=3;}

    if(flu && ord){
        bool flu_ord=false;
        for(int i=1;i<c1.size();i++){
            int tmp = c1[i]%13-c1[i-1]%13;
            
            if((tmp==1)&&(c1[i]/13==c1[i-1]/13)) c++;
            else c=1;
            if(c>=5) {flu_ord=true; ord_v=c1[i]%13;}
        }

        if(flu_ord) return {"FlOr", {ord_v}};
    }
    if (memo.find(4)!=memo.end()){
        auto it = std::find(memo[1].begin(), memo[1].end(), memo[4].back());
        if(it!=memo[1].end()) memo[1].erase(it);
        return {"Four",{memo[4].back(), memo[1].back()}}; 
    }
    else if (memo.find(3)!=memo.end()&&(memo.find(2)!=memo.end()&&memo[2].size()>1)){
        auto it = std::find(memo[2].begin(), memo[2].end(), memo[3].back());
        if(it!=memo[2].end()) memo[2].erase(it);

        return {"FuHo", {memo[3].back(), memo[2].back()}}; 
    }
    else if (flu) {
        vector<int> v(f_memo[flu_f].end()-5,f_memo[flu_f].end());
        reverse(v.begin(),v.end());
        return {"Flus", v};
    }
    else if (ord) {return {"Orde", {ord_v}};}
    else if (memo.find(3)!=memo.end()){
        auto it = std::find(memo[1].begin(), memo[1].end(), memo[3].back());
        if(it!=memo[1].end()) memo[1].erase(it);

        return {"Thre",{memo[3].back(), memo[1][memo[1].size()-1], memo[1][memo[1].size()-2]}};
    }
    else if (memo.find(2)!=memo.end()&& memo[2].size()>=2){
        auto it1 = std::find(memo[1].begin(), memo[1].end(), memo[2][memo[2].size()-1]);
        auto it2 = std::find(memo[1].begin(), memo[1].end(), memo[2][memo[2].size()-2]);
        if(it1!=memo[1].end()) memo[1].erase(it1);
        if(it2!=memo[1].end()) memo[1].erase(it2);

        return {"TwPa", {memo[2][memo[2].size()-1], memo[2][memo[2].size()-2], memo[1].back()}};
        }
    else{
        vector<int> ret;ret.reserve(5);

        for(int i=memo[1].size()-1;i>memo[1].size()-6;i--) {ret.push_back(memo[1][i]);}
        ret.pop_back();
        return {"High", ret};
    }
}


double* CardLib::checkWinRate(double* ret, int* in_c1, int* in_c2, int n) {
    vector<int> c1(in_c1, in_c1+n);
    vector<int> c2(in_c2, in_c2+n);
    int tmp, try_max=10000;
    double win=0,draw=0,lose=0;
    cout << "checkWinRate in c++" << endl;

    for(int i=0;i<try_max;i++){
        tmp = checkWin(checkType(c1), checkType(c2));
        if(tmp==1) win+=1;
        else if(tmp==-1) lose+=1;
        else if(tmp==0) draw+=1;
    }
    ret[0]=win/try_max;
    ret[1]=lose/try_max;
    ret[2]=draw/try_max;

    ret[2]=5.23;

    return ret;
}

int CardLib::checkWin(pair<string, vector<int>> h1, pair<string, vector<int>> h2) {
    if(typeMap[h1.first]==typeMap[h2.first]){
        for(int i=0;i<h1.second.size();i++){
            if(h1.second[i]!=h2.second[i]) return h1.second[i]>h2.second[i]?1:-1;
        }
        return 0;
    }else{
        return typeMap[h1.first]>typeMap[h2.first]?1:-1;
    }
}

extern "C" {
    CardLib obj;

    double* checkWinRate(double* ret, int in_c1[], int in_c2[], int n) {
        return obj.checkWinRate(ret, in_c1, in_c2, n);
    }
}
// g++ -o libCard.so -shared -fPIC C_card_lib.cpp