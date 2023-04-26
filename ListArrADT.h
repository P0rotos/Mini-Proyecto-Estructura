#ifndef QueueADT_H
#define QueueADT_H
#include<iostream>
using namespace std;
template<typename T>
class QueueADT{
	virtual int size() = 0;
	virtual void insert_left(T v) = 0;
	virtual void insert_right(T v) = 0;
	virtual void insert(T v, int i) = 0;
	virtual void print() = 0;
	virtual bool find(T v) = 0;
    virtual T delete_left() = 0;
    virtual T delete_right() = 0;
};
#endif