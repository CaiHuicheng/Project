#include<bits/stdc++.h>
using namespace std;
//根据k的不同进行计算
double ff(double a,double b,int k){
    //cout<<"ff"<<endl;
    if (k == 0){
        return a+b;}
    if (k == 1){
        return a-b;}
    if (k == 2){
        return a*b;}
    if (k == 3){
        return a/b;}
}
//根据k的不同进行符号打印
string fff(int k){
    if (k == 0){
        return "+";}
    if (k == 1){
        return "-";}
    if (k == 2){
        return "*";}
    if (k == 3){
        return "/";}
}
//根据不同数字翻译牌的字符
string zz(int k){
    if (k == 13){
        return "K";}
    if (k == 12){
        return "Q";}
    if (k == 11){
        return "J";}
    if (k == 1){
        return "A";}
    else{
        return to_string(k);}
}
//计算=24的可能数字
vector<int> helper(int a,int b,int c,int d){
    //cout<<"!!"<<endl;
    for (int i=0;i<4;i++){
        //cout<<"!!!"<<endl;
        for (int j=0;j<4;j++){
            for (int k=0;k<4;k++){

                double tmp = ff(ff(ff(double(a),double(b),k),double(c),j),double(d),i);
                //cout<<i<<" "<<j<<" "<<k<<" "<<tmp<<endl;
                if (abs(tmp - 24)<0.0001)
                    return {k,j,i};

            }}}
    return {};
}
//回溯情况，这里可以优化重复情况，但是a了就算了
vector<vector<int>> pl(vector<int> &nums){
    if (nums.size()==1){
        return {{nums[0]}};}
    vector<vector<int>> tmp ;
    for (int i=0;i<nums.size();i++){
        vector<int> tt;
        for (int j=0;j<i;j++){
            tt.push_back(nums[j]);
        }
        for (int j=i+1;j<nums.size();j++){
            tt.push_back(nums[j]);
        }
        //cout<<"tt.size()"<<tt.size()<<endl;
        auto t = pl(tt);
        for (auto j: t){
            j.insert(j.begin(),nums[i]);
            tmp.push_back(j);
        }
    }
    return tmp;

}

int main(){
    vector<string> a(4,"");
    for (int i=0;i<4;i++){
        cin>>a[i];
    }
    vector<int> aa(4,0);
    int ok = 1;
    int ii = -1;
    for (auto i:a){
        ii++;
        if (i == "J"){
            aa[ii] = 11;
        }
        else if(i == "Q"){
            aa[ii] = 12;
        }
        else if(i == "K"){
            aa[ii] = 13;
        }
        else if(i == "A"){
            aa[ii] = 1;
        }
        else if(i == "joker" || i == "JOKER"){
            cout<<"ERROR";
            ok = 0;
        }
        else{
            aa[ii] = stod(i);
        }
    }

    auto pailie = pl(aa);
    int chenggong=0;
    if (ok==1){
        for (auto i:pailie){
            auto ans= helper(i[0],i[1],i[2],i[3]);
            if (ans.size()>0){
                cout<<zz(i[0])+fff(ans[0])+zz(i[1])+fff(ans[1])+zz(i[2])+fff(ans[2])+zz(i[3])<<endl;
                chenggong = 1;
                break;

            }
        }

    if (chenggong == 0){
        cout<<"NONE"<<endl;
    }
    }

}
