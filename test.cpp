#include "SharedPtr.hpp"
#include <assert.h>
#include <iostream>
using namespace cs540;
struct Foo {
     Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
int main(){
	SharedPtr<Foo> sh;
	Foo *f = new Foo();
	SharedPtr<Foo> sh1(f);
	assert(sh1.ptr->Optr == f);
	SharedPtr<Foo> sh2(sh1);
	assert(sh1.ptr->ref_count == 2);
	assert(sh1.ptr == sh2.ptr);
}
