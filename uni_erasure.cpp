#include <iostream>
#include <functional>
using namespace std;
/*template <typename T>
void delete_deleter( void * p ) {
   delete static_cast<T*>(p);
}

template <typename T>
class my_unique_ptr {
	public:
  std::function< void (void*) > deleter;
  T * p;
  template <typename U>
  my_unique_ptr( U * p, std::function< void(void*) > deleter = &delete_deleter<U> )
     : p(p), deleter(deleter)
  {}
  ~my_unique_ptr() {
     deleter( p );
  }
};

int main() {
   my_unique_ptr<void> p( new double ); // deleter == &delete_deleter<double>
}*/

template<typename T>
void func(void* p){
//	cout<<"used function pointers"<<endl;
	delete static_cast<T*>(p);
}

template<typename T>
class B{
	public:
	T *pt;
//	void (*fun)(void);
	std::function<void(void *)> del;
	template<typename U>
	B(U *pr, std::function<void(void *)> d = &func<U>){
		pt = pr;
		del = d;
	}
	~B(){
		del(pt);
	}
};
class A{
	public:
	A(){}
	~A(){cout<<"A destructor"<<endl;}
};
class c:public A{
	public:
	c(){}
	~c(){cout<<"C destructor"<<endl;}
};
int main(){
	B<A> b(new c);
}
