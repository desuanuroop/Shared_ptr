#include<iostream>
using namespace std;

class Base{
	public:
	int *x;
	Base(){
		x = new int();
	}
	virtual ~Base(){cout<<"In Base destructor"<<endl;delete x;
	}
};
class Derived:public Base{
	public:
	int *y;
	Derived(){
		y = new int();
	}
        ~Derived(){cout<<"In Derived destructor"<<endl;delete y;}
};
int main(){
	Base *b = new Derived();
	Derived *d = dynamic_cast<Derived *>(b);
	delete d;
}
