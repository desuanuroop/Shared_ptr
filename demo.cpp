#include<iostream>
class Base{
	public:
	class b{
		int a;
	};
	int x;
};
class Derived: public Base{
	public:
	class d{
		int d;
	};
		int y;
};
int main(){
	Base::b *b;
	int *p;
	p = new int(1);
	(*p)++;
	std::cout<<*p<<std::endl;
}
