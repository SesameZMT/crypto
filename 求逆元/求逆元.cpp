#include<iostream>

int a;
int b;

void sn(int s1,int s2,int q,int r1,int r2,int num){
    if(r2 == 0){
        std::cout<<s2<<std::endl;
    }
    else{
        sn(s2,s1-s2*q,r1/r2,r2,r1%r2,num++);
    }
}

void tn(int t1,int t2,int q,int r1,int r2,int num){
    if(r2 == 0){
        if(t2 < 0)
        {
            std::cout<<t2+b;
        }
        else
        {
            std::cout<<t2;
        }
    }
    else{
        tn(t2,t1-t2*q,r1/r2,r2,r1%r2,num++);
    }
}

int main()
{
    std::cin>>a>>b;
    tn(0,1,b/a,a,b%a,1);
}