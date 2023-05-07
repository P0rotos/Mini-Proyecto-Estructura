#include<iostream>
#include<cmath>
#include "ListArr.cpp"
using namespace std;
int main(int argc, char const *argv[]){
    ListArr<int> A(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.insert_left(10);
    A.print();
    return 0;
}
