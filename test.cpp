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

using namespace cs540;
using namespace std;
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

        ~Base1() {
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

        ~Derived() {
            printf("Derived::~Derived()\n");
            derived_destructor_called = true;
        }
        int value;
};

class Base_polymorphic {
public:
        Base_polymorphic() {
            printf("Base_polymorphic::Base_polymorphic()\n");
        }

        Base_polymorphic(const Base_polymorphic &); // Disallow.
        Base_polymorphic &operator=(const Base_polymorphic &); // Disallow.
        virtual ~Base_polymorphic() {
            printf("Base_polymorphic::~Base_polymorphic()\n");
        }
};

class Derived_polymorphic : public Base_polymorphic {
        friend void basic_tests_1();
public:
        Derived_polymorphic() {}
        Derived_polymorphic(const Derived_polymorphic &); // Disallow.
        Derived_polymorphic &operator=(const Derived_polymorphic &); // Disallow.
};

class Derived2_polymorphic : public Base_polymorphic {
public:
        Derived2_polymorphic() {}
        Derived2_polymorphic(const Derived2_polymorphic &); // Disallow.
        Derived2_polymorphic &operator=(const Derived2_polymorphic &); // Disallow.
};

class Base2 {
public:
        Base2() : derived_destructor_called(false) {
            printf("Base2::Base2()\n");
        }
public:
        Base2(const Base2 &); // Disallow.
        Base2 &operator=(const Base2 &); // Disallow.
public:
        ~Base2() {
            printf("Base2::~Base2()\n");
            assert(derived_destructor_called);
        }
public:
        bool derived_destructor_called;
};

class Derived_mi : public Base1, public Base2 {
        friend void basic_tests_1();
public:
        Derived_mi() {}
        Derived_mi(const Derived_mi &); // Disallow.
        Derived_mi &operator=(const Derived_mi &); // Disallow.
public:
        ~Derived_mi() {
            printf("Derived_mi::~Derived_mi()\n");
            Base1::derived_destructor_called = true;
            Base2::derived_destructor_called = true;
        }
        int value;
};

class Base1_vi {
public:
        Base1_vi() : derived_destructor_called(false) {
            printf("Base1_vi::Base1_vi()\n");
        }
public:
        Base1_vi(const Base1_vi &); // Disallow.
        Base1_vi &operator=(const Base1_vi &); // Disallow.
public:
        virtual ~Base1_vi() {
            printf("Base1_vi::~Base1_vi()\n");
            assert(derived_destructor_called);
        }
public:
        bool derived_destructor_called;
};

class Base2_vi : public virtual Base1_vi {
public:
        Base2_vi() {
            printf("Base2_vi::Base2_vi()\n");
        }
   public:
        Base2_vi(const Base2_vi &); // Disallow.
        Base2_vi &operator=(const Base2_vi &); // Disallow.
public:
        virtual ~Base2_vi() {
            printf("Base2_vi::~Base2_vi()\n");
            assert(derived_destructor_called);
        }
};

class Derived_vi : public virtual Base1_vi, public Base2_vi {
        friend void basic_tests_1();
public:
        Derived_vi() {}
        Derived_vi(const Derived_vi &); // Disallow.
        Derived_vi &operator=(const Derived_vi &); // Disallow.
    public:
        virtual ~Derived_vi() {
            printf("Derived_vi::~Derived_vi()\n");
            derived_destructor_called = true;
        }
        int value;
};

/* Basic Tests 2 ================================================================================ */

class A {
    public:
	virtual ~A() {
	    //printf("%p deleted\n", (Obj *) this);
	}
};

class B : public A {
    public:
	virtual ~B() {}
};

class C : public A {
    public:
	virtual ~C() {}
};

//Thread


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
/*        {
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
	assert(!(sp2==nullptr));
    }

    // Test static_pointer_cast.
    // Test dynamic_pointer_cast.
    // Test to make sure works with virtual inheritance.
    {
        SharedPtr<Base2_vi> sp2;
        {
            SharedPtr<Base1_vi> sp1;
            {
                SharedPtr<Derived_vi> sp(new Derived_vi);
                sp1 = sp;
                sp2 = sp;
            } // Destructor for sp called.
        } // Destructor for sp1 called.
    } // Destructor for sp2 called.
    // Test const assignment.
    {
        SharedPtr <const Derived> sp_const(new Derived);
        SharedPtr <Derived> sp(new Derived);
        sp_const = sp;
        // sp = sp_const; // Syntax error if uncommented.
    }


    }//END OF TEST 1


	{//T2
		// Test default constructor.
        {
            SharedPtr<A> np;
            assert(!np);
        }

        // Test construction from object.
        {
            A *ap = new A;
            SharedPtr<A> a(ap);
            assert(a.get() == ap);
        }

        // Test construction from another SharedPtr of the same type.
        {
            SharedPtr<A> a(new A);
            SharedPtr<A> a2(a);
        }

        // Test construction from another SharedPtr of a derived type.
        {
            SharedPtr<B> b(new B);
            SharedPtr<A> a(b);
        }

        // Test assignment operator.
        {
            // Same type.
            SharedPtr<A> a1, a2(new A);
            a1 = a2;

            // Derived to base.
            SharedPtr<B> b(new B);
            a1 = b;

            // Object ptr.
            a1.reset(new A);

            // To Null.
            a1.reset();
        }      
	  // More misc tests.
        {
            SharedPtr<B> b(new B);
            SharedPtr<C> c(new C);

            /*
            printf("new B: %p\n", static_cast<Body *>(b.ptr()));
            printf("new C: %p\n", static_cast<Body *>(c.ptr()));

            printf("b: %p\n", &b);
            printf("c: %p\n", &c);
            

            // Initialization from base should not require cast.
            SharedPtr<A> a_base(b);

            // Default initialization and cast to base.
            SharedPtr<A> a_dc(b);
            // Note that this will use the templated constructor to do a conversion.
            // if a templated assignment does not exist.
            a_dc = b;

            // Static cast to base.
            SharedPtr<A> a_b = b;
            SharedPtr<A> a_c = c;
            /*
            printf("a_b: %p\n", &a_b);
            printf("a_c: %p\n", &a_c);
            
	}*/
	}//END T2

}
