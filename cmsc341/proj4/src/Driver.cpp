/**
** Class: CMSC341
** Project: Project4
** File: Driver.cpp
** Name: Dong Sun
** Date: 11/18/2014
**/
#include<iostream>
#include "QuadraticProbing.h"
#include "Random.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"
#include <fstream>


int main(int argc, char *argv[]){

 HashTable<int> H;
 Table<int> T;


 ifstream myfile;
 myfile.open(argv[1],ios_base::in);
 int number;
 myfile>>number;
 T.insert(number);
 cout << " \t\t\t Linear Probing Analysis (Table size = "<< T.size()<< ") " <<endl;
 cout << "\t\t\t ---Insert---   ---Probes---   ---Clusters---\n";
 cout << "N\tlamba\tsuccess\tfailed\t\ttotal\tavg\tmax\tnumber\tavg\tmax\t\n";
 for(int i=1; i<=T.size()+1;i++)
 {
     for(int j=1;j<i;j++)
     {
        cout<<i<<"\t"<<i/T.size()<<"\t"<<j<<"\t"<<i-j<<"\t"<<T.size()<<"\t"<<i/T.size()<<"\t"<<i<<"\t"<<endl;
     }
 }
 H.insert(number);
 cout << " \t\t\t Quadratic Probing Analysis (Table size = "<< hash(number)<< ") " <<endl;
 cout << "\t\t\t ---Insert---   ---Probes---   ---Clusters---\n";
 cout << "N\tlamba\tsuccess\tfailed\t\ttotal\tavg\tmax\tnumber\tavg\tmax\t\n";
 for(int i=1; i<=hash(number);i++)
 {
     for(int j=1;j<i;j++)
     {
        cout<<i<<"\t"<<i/hash(number)<<"\t"<<j<<"\t"<<i-j<<"\t"<<hash(number)<<"\t"<<i/hash(number)<<"\t"<<i<<endl;
     }
 }
 H.insert(number);
 cout << " \t\t\t Double Hashing Analysis (Table size = "<< hash(number)<< ") " <<endl;
 cout << "\t\t\t ---Insert---   ---Probes---   ---Clusters---\n";
 cout << "N\tlamba\tsuccess\tfailed\t\ttotal\tavg\tmax\tnumber\tavg\tmax\t\n";
 for(int i=1; i<=hash(number)+1;i++)
 {
     for(int j=1;j<i;j++)
     {
        cout<<i<<"\t"<<i/hash(number)<<"\t"<<j<<"\t"<<i-j<<"\t"<<hash(number)<<"\t"<<i/hash(number)<<"\t"<<i<<endl;
     }
 }


return 0;

}
