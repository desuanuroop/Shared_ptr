#include <iostream>
namespace cs540{
using namespace std;
	template<typename T>
	class SharedPtr{
		class ObjPtr{
			public:
			T *Optr;
			int ref_count;
		};
		public:
		ObjPtr *ptr = NULL; //Member
		//constructors
		SharedPtr();
		explicit SharedPtr(T *);
		SharedPtr(const SharedPtr &p);//copy Constructor

		//Destructor
		~SharedPtr(){
			cout<<"Destructor"<<endl;
			if(ptr != NULL){
				if(ptr->ref_count == 1){
					delete ptr->Optr;
					delete ptr;
				}else
					ptr->ref_count--;
			}
		}
	};
	template<typename T>
	SharedPtr<T>::SharedPtr(){//Default Constructor pointing to NULL with ref_count =0
		ptr = NULL;
	}
	template<typename T>
	SharedPtr<T>::SharedPtr(T *ptd){
		if(ptr == NULL){
			ptr = new ObjPtr();
			ptr->Optr = ptd;
			ptr->ref_count = 1;
		}
	}
	template<typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr &p){
		if(p.ptr != NULL)
			p.ptr->ref_count++;
		ptr = p.ptr;
	}
}//End of namespace
