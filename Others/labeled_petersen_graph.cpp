#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

// Peterse Graph を文字列に変換する
string get_str(int e[30]){
    string ret = "";
    int a, b, c;
    for(int i=0; i<10; i++){
        a = e[3*i];
        b = e[3*i + 1];
        c = e[3*i + 2];

        ret += 'a' + min({a, b, c});
        ret += 'a' + a + b + c - max({a, b, c}) - min({a, b, c});
        ret += 'a' + max({a, b, c});
    }

    return ret;
}

// Petersen Graph の辺を得る
void get_edge(int v[10], int e[30]){
    int pos = 0;
    for(int i=0; i<10; i++){
        if(i % 2){
            for(int j=0; j<3; j++){
                //e[pos++] = v[(i+j+4) % 10];
                e[3*v[i]+j] = v[(i+j+4) % 10];
            }
        }
        else{
            for(int j=0; j<3; j++){
                //e[pos++] = v[(i+2+3*j) % 10];
                e[3*v[i]+j] = v[(i+2+3*j) % 10];
            }
        }
    }
}

// Petersen Graph を列挙する
vector<string> enum_petersen(){
    vector<string> pet; // 列挙結果を文字列として格納数する
    int v[10] = {0}, e[30] = {0}; // 現在の Petersen Graph の頂点と辺
    string s;

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    do{
        for(int i=0; i<9; i++){
            v[i+1] = vec[i];
        }
        get_edge(v, e);
        s = get_str(e);
        pet.push_back(s);
    }while(next_permutation(vec.begin(), vec.end()));

    //cout<<pet[0]<<endl;

    sort(pet.begin(), pet.end());
    vector<string> ret;

    ret.push_back(pet[0]);
    for(int i=1; i<pet.size(); i++){
        if(pet[i-1] != pet[i]){
            ret.push_back(pet[i]);
        }
    }

    return ret;
}

bool is_disjoint(string s, string t){
    

    // fi と辺素な場合は true, そうでない場合は false を返す
    for(int i=0; i<s.size(); i++){
        for(int j=0; j<3; j++){
            if(t[i/3*3+j] == s[i]){
                return false;
            }
        }
    }
    return true;
}

vector<string> get_candidates(vector<string> pet){
    vector<string> ret;
    string fi = "cfifghaehhijcgjabjbeibcdadgdef";
    for(auto itr=pet.begin(); itr!=pet.end(); itr++){
        if(is_disjoint(*itr, fi)){
            ret.push_back(*itr);
        }
    }
    return ret;
}

signed main(){

    // K_{10} を辺素な 3 つの Petersen Graph に分解できないことを示す
    vector<string> pet, cnd;
    pet = enum_petersen();
    cnd = get_candidates(pet);

    for(int i=0; i<cnd.size(); i++){
        //cout<<cnd[i]<<endl;
        for(int j=i+1; j<cnd.size(); j++){
            if(is_disjoint(cnd[i], cnd[j])){
                cout<<cnd[i]<<" "<<cnd[j]<<endl;
            }
        }
    }

    return 0;
}