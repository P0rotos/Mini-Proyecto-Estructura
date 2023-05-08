#include<iostream>
#include<cmath>
#include "ListArr.cpp"
using namespace std;
int main(int argc, char const *argv[]){
    ListArr<int> A(10);
    A.insert_left(1);
    A.insert_left(2);
    A.insert_left(3);
    A.insert_left(4);
    A.insert_left(5);
    A.insert_left(6);
    A.insert_left(7);
    A.insert_left(8);
    A.insert_left(9);
    A.insert_left(11);
    A.insert_right(0);
    A.insert(10, 1);
    cout << A.find(0);
    cout << A.find(13);
    cout << A.delete_left();
    cout << A.delete_right();
    cout << A.delete_left();
    cout << A.delete_left();
    cout << "size: " << A.size() << endl;
    A.print();
    return 0;
}
