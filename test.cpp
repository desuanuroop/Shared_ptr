#include "SharedPtr.hpp"
#include <assert.h>
#include <iostream>
using namespace cs540;
class Foo {
	public:
//     Foo() { std::cout << "Foo...\n"; }
       virtual ~Foo() {}
	int x;
};
class Derived:public Foo{
	public:
		virtual ~Derived(){}
		int y;
};
int main(){
	SharedPtr<Foo> sh;
	Foo *f = new Foo();
	SharedPtr<Foo> sh1(f);
	sh1 = sh1;
	assert(*sh1.ptr->ref_count == 1);
	assert(sh1.ptr->Optr == f);
	SharedPtr<Foo> sh2(sh1);
	assert(*sh1.ptr->ref_count == 2);
	assert(sh1.ptr->Optr == sh2.ptr->Optr);
	Derived *d = new Derived();
	SharedPtr<Foo> sh3(d);
	SharedPtr<Foo> sh4(sh3);
	assert(sh3.ptr->Optr == sh4.ptr->Optr);
	assert(sh3.ptr->Optr == d);

	assert(*sh3.ptr->ref_count == 2);
	SharedPtr<Foo> sh5(std::move(sh3));
	assert(*sh5.ptr->ref_count == 2);
	assert(sh3.ptr == NULL);

	sh3 = sh5;
	assert(sh3.ptr != NULL);
	assert(*sh3.ptr->ref_count == 3);

	sh1 = sh5;
	assert(sh1.ptr->Optr == sh5.ptr->Optr);
	assert(*sh2.ptr->ref_count == 1);

	sh1 = std::move(sh2);
	
	sh1.reset();
	Foo *f1 = new Foo();
	sh1.reset(f1);
	sh1.get()->x = 100;
	int x = sh1.get()->x;
	assert(x == 100);

	{
            SharedPtr<Foo> sp2;
            {
                SharedPtr<Derived> sp(new Derived);
                // Test template copy constructor.
                SharedPtr<Foo> sp3(sp);
                sp2 = sp;
                sp2 = sp2;
            }
        }
}
