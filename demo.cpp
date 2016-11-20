#include "SharedPtr.hpp"
#include <new>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <errno.h>
#include <assert.h>
#include <memory>

using namespace std;

class Base{
	public:
	int x;
	Base(){ x= 99;
	}
	~Base(){cout<<"In Base destructor"<<endl;;
	}
};
class Derived:public Base{
	public:
	int *y, x;
	Derived(){
		x = 100;
		y = new int();
	}
        ~Derived(){cout<<"In Derived destructor"<<endl;delete y;}
};
int main(){
/*	decltype(b) c;
	decltype(*b) cc = *b;
	cout<<"type b: "<<typeid(c).name()<<endl;
	cout<<"type b*: "<<typeid(cc).name()<<endl;
	delete b;*/

//	std::shared_ptr<Base> p(new Derived());
	Derived d;
	cout<<d.x<<endl;
}
