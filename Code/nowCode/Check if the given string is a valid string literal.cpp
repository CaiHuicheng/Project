#include<iostream>
#include<string>

using namespace std;

int function(int state,char c){
    if(state == 0&&c == '"') return 1;
    else if(state == 1&&c == '\\') return 3;
    else if(state == 1&&c !='"') return 1;
    else if(state == 1&&c =='"')return 2;
    else if(state == 3){
        return 1;
    }
    return -1;
}

int main(){
    string str;
    cin>>str;
    int state = 0;
    for(auto c:str){
        state = function(state,c);
    }
    if(state == 2){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    return 0;
}