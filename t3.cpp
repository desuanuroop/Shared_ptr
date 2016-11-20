#include <iostream>
#include <typeinfo>
using namespace std;

class A{
	public:
	int *x;
	A(int y){
		x = new int(y);
	}
	~A(){}
};
class B:public A{
	public:
	B():A(1000){
//		x = 1;
	}
	~B(){cout<<"Derived"<<endl;delete x;}
};

template<typename T>
class helper{
	public:
	T* Optr;
	int *ref_count;
	template<typename U>
	helper(U *pt){
		Optr = pt;
	}
	~helper(){
		delete Optr;
	}
};
template<typename T>
class SharedPtr:public helper<T>
{
	public:
	template<typename U>
	SharedPtr(U* pt):helper<T>(pt){
//		Optr = pt;
	}
	~SharedPtr(){
	}
};

int main(){
//	SharedPtr<A> sh(new A(10));
//	B<int> *b = new B<int>();
//	cout<<b->x<<endl;
	A *ap = new B();
}
