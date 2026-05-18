//Practical: Implement Min, Max, Sum and Average operations using Parallel Reduction.
//%%writefile red.cpp
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <omp.h>
using namespace std;

int findMin(vector<int>& a){
    int m=numeric_limits<int>::max();
    #pragma omp parallel for reduction(min:m)
    for(int i=0;i<a.size();i++) if(a[i]<m) m=a[i];
    return m;
}

int findMax(vector<int>& a){
    int m=numeric_limits<int>::min();
    #pragma omp parallel for reduction(max:m)
    for(int i=0;i<a.size();i++) if(a[i]>m) m=a[i];
    return m;
}

int findSum(vector<int>& a){
    int s=0;
    #pragma omp parallel for reduction(+:s)
    for(int i=0;i<a.size();i++) s+=a[i];
    return s;
}

double findAvg(vector<int>& a){
    double s=0;
    #pragma omp parallel for reduction(+:s)
    for(int i=0;i<a.size();i++) s+=a[i];
    return s/a.size();
}

int main(){
    vector<int> a(100);
    for(int i=0;i<100;i++) a[i]=rand()%100;

    cout<<"Data :"<<endl;
    for(int i=0;i<100;i++){
        cout<<" "<<a[i];
        if((i+1)%10==0) cout<<endl;
    }

    cout<<"\nMinimum : "<<findMin(a)<<endl;
    cout<<"Maximum : "<<findMax(a)<<endl;
    cout<<"Sum : "<<findSum(a)<<endl;
    cout<<"Average : "<<findAvg(a)<<endl;
}

//!g++ red.cpp -fopenmp -o red
//!./red