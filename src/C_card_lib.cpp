#define pii pair<int,int>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include "C_utils_lib.h"

using namespace std;


class CardLib
{
    public:
        CardLib();
        double* checkWinRate(double* , int[], int[], int );
    private:
        map<string, int> typeMap;
        int cardsMax=7;
        int checkWin(const pair<string, vector<int>>& , const pair<string, vector<int>>& );
        pair<string, vector<int>> checkType(vector<int>);
        void getFullHand(vector<int>& ,vector<int>& , int , set<int>& );

};

CardLib::CardLib(){
    srand((unsigned)time(NULL)); 
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
        f_memo[tmp].push_back(c1[i]%13);
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
    else if (memo.find(2)!=memo.end()&& memo[2].size()>=1){
        auto it = std::find(memo[1].begin(), memo[1].end(), memo[2].back());
        if(it!=memo[1].end()) memo[1].erase(it);

        return {"Pair", {memo[2].back(), memo[1][memo[1].size()-1], memo[1][memo[1].size()-2], memo[1][memo[1].size()-3]}};
        }
    else{
        vector<int> ret;ret.reserve(5);

        for(int i=memo[1].size()-1;i>memo[1].size()-6;i--) {ret.push_back(memo[1][i]);}
        ret.pop_back();
        return {"High", ret};
    }
}

void CardLib::getFullHand(vector<int>& c1,vector<int>& c2, int addNum, set<int>& handCards){
    int tmp;
    while(addNum>0){
        tmp=rand()%52;
        if(handCards.find(tmp)!=handCards.end()) continue;
        c1[cardsMax-addNum]=tmp;c2[cardsMax-addNum]=tmp;
        addNum--;
    }
}


double* CardLib::checkWinRate(double* ret, int* in_c1, int* in_c2, int n) {
    set<int> handCards;
    vector<int> c1(cardsMax, -1); for(int i=0;i<n;i++){ c1[i]=in_c1[i];handCards.insert(in_c1[i]);}
    vector<int> c2(cardsMax, -1); for(int i=0;i<n;i++){ c2[i]=in_c2[i];handCards.insert(in_c2[i]);}


    int tmp, try_max=10000;
    double win=0,draw=0,lose=0;
    // cout << "checkWinRate in c++" << endl;

    for(int i=0;i<try_max;i++){
        getFullHand(c1,c2,cardsMax-n,handCards);
        // readablePrint(c1);
        // readablePrint(c2);

        tmp = checkWin(checkType(c1), checkType(c2));
        // cout<<tmp<<endl;
        // cout<<"============"<<endl;
        if(tmp==1) win+=1;
        else if(tmp==-1) lose+=1;
        else if(tmp==0) draw+=1;
    }
    ret[0]=win/try_max;
    ret[1]=lose/try_max;
    ret[2]=draw/try_max;

    return ret;
}

int CardLib::checkWin(const pair<string, vector<int>>& h1, const pair<string, vector<int>>& h2) {
    // cout<<h1.first<<' ';for(int i:h1.second) cout<<i<<' ';
    // cout<<endl;
    // cout<<h2.first;for(int i:h2.second) cout<<i<<' ';
    // cout<<endl;

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