//%%writefile sort.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

void pb(vector<int>& a){
    int n=a.size();
    for(int k=0;k<n;k++){
        #pragma omp parallel for
        for(int i=k%2;i<n-1;i+=2)
            if(a[i]>a[i+1]) swap(a[i],a[i+1]);
    }
}

void pm(vector<int>& a){
    int n=a.size(); if(n<2) return;
    vector<int> l(a.begin(),a.begin()+n/2), r(a.begin()+n/2,a.end());
    #pragma omp parallel sections
    {
        #pragma omp section
        pm(l);
        #pragma omp section
        pm(r);
    }
    merge(l.begin(),l.end(),r.begin(),r.end(),a.begin());
}

void show(int op, vector<int> a){
    if(op==1) sort(a.begin(),a.end());
    else if(op==2) pb(a);
    else if(op==3) stable_sort(a.begin(),a.end());
    else if(op==4) pm(a);

    if(op==0) cout<<"Original without sort : ";
    if(op==1) cout<<"Sequential bubble sort : ";
    if(op==2) cout<<"Parallel bubble sort : ";
    if(op==3) cout<<"Sequential merge sort : ";
    if(op==4) cout<<"Parallel merge sort : ";

    for(int i=0;i<a.size();i++) cout<<a[i]<<" ";
    cout<<endl;
}

int main(){
    vector<int> a;
    int t[]={4,2,6,8,1,3,9,5,7};
    for(int i=0;i<9;i++) a.push_back(t[i]);

    for(int i=0;i<5;i++) show(i,a);
}



//!g++ sort.cpp -fopenmp -o sort

//!./sort