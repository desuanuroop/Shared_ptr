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
class Derived2:public Foo{
	public:
		virtual ~Derived2(){}
		int y;
};

class Base1 {
	public:
        Base1() : derived_destructor_called(false) {
            printf("Base1::Base1()\n");
        }
        Base1(const Base1 &); // Disallow.
        Base1 &operator=(const Base1 &); // Disallow.
        virtual ~Base1() {
            printf("Base1::~Base1()\n");
            assert(derived_destructor_called);
        }
        bool derived_destructor_called;
};

class Derived : public Base1 {
        friend void basic_tests_1();
    public:
        Derived() {}
        Derived(const Derived &); // Disallow.
        Derived &operator=(const Derived &); // Disallow.
    public:
        ~Derived() {
            printf("Derived::~Derived()\n");
            derived_destructor_called = true;
        }
        int value;
};

int main(){
/*	SharedPtr<Foo> sh;
	Foo *f = new Foo();
	SharedPtr<Foo> sh1(f);
	sh1 = sh1;
	assert(*sh1.ptr->ref_count == 1);
	assert(sh1.ptr->Optr == f);
	SharedPtr<Foo> sh2(sh1);
	assert(*sh1.ptr->ref_count == 2);
	assert(sh1.ptr->Optr == sh2.ptr->Optr);
//	Derived2 *d = new Derived2();
	SharedPtr<Foo> sh3(new Derived2);
	SharedPtr<Foo> sh4(sh3);
	assert(sh3.ptr->Optr == sh4.ptr->Optr);
//	assert(sh3.ptr->Optr == d);

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
	
	SharedPtr<Foo> sh(new Foo);
	sh.get()->x = 100;
	assert(sh.get()->x == 100);
	(*sh).x = 200;
	assert((*sh).x == 200);*/

// Test deleting through original class.
    {
        // Base1 created directly with Derived *.
        {
            SharedPtr<Base1> sp(new Derived);
            {
                // Test copy constructor.
                SharedPtr<Base1> sp2(sp);
            }
        }
        // Base1 assigned from SharedPtr<Derived>.
        {
            SharedPtr<Base1> sp2;
            {
                SharedPtr<Derived> sp(new Derived);
                // Test template copy constructor.
                SharedPtr<Base1> sp3(sp);
                sp2 = sp;
                sp2 = sp2;
            }
        }

    // Test copy constructor and template copy constructor.
    {
        {
            SharedPtr<Derived> sp(new Derived);
            SharedPtr<Derived> sp2(sp);
        }
        {
            SharedPtr<Derived> sp(new Derived);
            SharedPtr<Base1> sp2(sp);
        }
    }

    // Test assignment operator and template assignment operator.
    {
        {
            SharedPtr<Derived> sp(new Derived);
            SharedPtr<Derived> sp2;
            sp2 = sp;
            sp = sp; // Self assignment.
        }
        {
            SharedPtr<Derived> sp(new Derived);
            SharedPtr<Base1> sp2;
            sp2 = sp;
            sp2 = sp2; // Self assignment.
            sp2 = sp;
            sp = sp;
        }
    }
// Test reset.
    {
        {
            SharedPtr<Derived> sp(new Derived);
            SharedPtr<Base1> sp2;
            sp2 = sp;
            sp2 = sp2;
            sp.reset();
            sp.reset(new Derived);
            SharedPtr<Base1> sp3(sp2);
        }
        // Need to make sure that it's the reset that
        // is forcing the object to be deleted, and
        // not the smart pointer destructor.
        {
            SharedPtr<Derived> sp(new Derived);
            char *buf = (char *) ::operator new(sizeof(SharedPtr<Base1>));
            SharedPtr<Base1> &sp2 = *(new (buf) SharedPtr<Base1>());
            sp2 = sp;
            sp2 = sp2;
            sp.reset();
            sp2.reset();
            ::operator delete(buf);
        }
    }

    // Test *.
    {
        SharedPtr<Derived> sp(new Derived);
        (*sp).value = 1234;

        SharedPtr<const Derived> sp2(sp);
        int i = (*sp2).value;
        assert(i == 1234);
        // (*sp2).value = 567; // Should give a syntax error if uncommented.
    }
    // Test get().
    {
        SharedPtr<Derived> sp(new Derived);
        sp.get()->value = 1234;

        SharedPtr<const Derived> sp2(sp);
        int i = sp2.get()->value;
        assert(i == 1234);
    }
    // Test ->.
    {
        SharedPtr<Derived> sp(new Derived);
        sp->value = 1234;

        SharedPtr<const Derived> sp2(sp);
        int i = sp2->value;
        assert(i == 1234);
        // sp2->value = 567; // Should give a syntax error if uncommented.
    }
    // Test bool.
    {
        SharedPtr<Derived> sp(new Derived);
        assert(sp);
        sp.reset();
        assert(!sp);

        SharedPtr<Derived> sp2;

        // int i = sp; // Must give syntax error.
        // delete sp; // Must give syntax error.
    }
    // Test ==.
    {
        SharedPtr<Derived> sp(new Derived);
        SharedPtr<Derived> sp2(sp);
        SharedPtr<Derived> sp3;

        assert(sp2 == sp);
        assert(!(sp2 == sp3));
        sp3.reset(new Derived);
        assert(!(sp2 == sp3));
    }

    }//END OF TEST

}
