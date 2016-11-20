#include <iostream>

using namespace std;
template<typename U>
class helper{
	public:
	int x;
	U* pt;
	int* ref_count;
};
template<typename T>
class SharedPtr:public helper<T>{
	public:
	template<typename U>
	SharedPtr(U* p){
 		x=12;
		pt = p;
	}
	~SharedPtr(){
		delete pt;
//		delete ptr->ref_count;
	}
};
class Base{
	public:
	int *x;
	Base(){
		x = new int();
	}
	~Base(){cout<<"Base d"<<endl;;delete x;}
};
class Derived:public Base{
	public:
	int *y;
	Derived(){
		y = new int();
	}
	~Derived(){
		cout<<"Derive d"<<endl;
		delete y;
	}
};
int main(){
	SharedPtr<Base> sh(new Derived());
}
