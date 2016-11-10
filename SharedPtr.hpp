#include <iostream>
namespace cs540{
using namespace std;
	template<typename T>
	class SharedPtr{
		class ObjPtr{
			public:
			T *Optr;
			int *ref_count;
		};
		public:
		ObjPtr *ptr = NULL; //Member
		//Default constructors
		SharedPtr(){
			ptr=NULL;
		}

		//Construct a SharedPtr pointing to given object
		template<typename U>
		explicit SharedPtr(U *ptd){
 	               if(ptr == NULL){
        	                ptr = new ObjPtr();
                	        ptr->Optr = ptd;
                        	ptr->ref_count = new int(1);
                	}
		}

		//copy constructor
		SharedPtr(const SharedPtr &p){//copy Constructor
			if(p.ptr != NULL)
                        	(*p.ptr->ref_count)++;
	                ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
		}

		//copy constructor with Change of Type
		template<typename U>
		SharedPtr(const SharedPtr<U> &p){
			if(p.ptr != NULL)
				(*p.ptr->ref_count)++;
	                ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
		}

		//Move reference
		SharedPtr(SharedPtr &&p){
//			cout<<"HI"<<endl;
			ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
			delete p.ptr;
			p.ptr = NULL;
		}

		//Move reference with Change of Type
		template<typename U>
		SharedPtr(SharedPtr<U> &&p){
			ptr = new ObjPtr();	
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
			delete p.ptr;
			p.ptr = NULL;
		}

		//Assignment operator
		SharedPtr &operator=(const SharedPtr &from){
//			cout<<"HI 2"<<endl;
			if(ptr){
				if(ptr == from.ptr)
					return *this;
				else if(*ptr->ref_count == 1)
					delet(ptr);
				else
					(*ptr->ref_count)--;
			}
			delete ptr; //Doubt it.
			ptr = new ObjPtr();
			ptr->Optr = from.ptr->Optr;
			ptr->ref_count = from.ptr->ref_count;
			(*ptr->ref_count)++;
			return *this;
		}

		//Assignment operator with Change of Type
		template<typename U>
		SharedPtr &operator=(const SharedPtr<U> &from){
			cout<<"HI 3"<<endl;
			if(ptr){
				if(ptr->Optr == from.ptr->Optr)
					return *this;
				else if(*ptr->ref_count == 1)
					delet(ptr);
				else
					(*ptr->ref_count)--;
			}
			delete ptr; //Doubt it.
			ptr = new ObjPtr();
			ptr->Optr = from.ptr->Optr;
			ptr->ref_count = from.ptr->ref_count;
			(*ptr->ref_count)++;			
			return *this;
		}

		//Assignment operator with Move
		SharedPtr &operator=(SharedPtr &&p){
			cout<<"HI 4"<<endl;
			if(ptr){
				if(*ptr->ref_count == 1)
					delet(ptr);
				else
					(*ptr->ref_count)--;
			}
			delete ptr;
			ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
			delete p.ptr;
			p.ptr = NULL;
			return *this;
		}

		//Assignment opeartor with Move Change of Type
		template<typename U>
		SharedPtr &operator=(SharedPtr<U> &&p){
			if(ptr){
				if(*ptr->ref_count == 1)
					delet(ptr);
				else
					(*ptr->ref_count)--;
			}
			delete ptr;
			ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
			delete p.ptr;
			p.ptr = NULL;
			return *this;
		}

		//get
		T* get() const{
			if(ptr)
				return ptr->Optr;
			return NULL;
		}

		//Delete if only one reference
		void delet(SharedPtr<T>::ObjPtr *ptr){
			if(!ptr)
				return;
			if((*ptr->ref_count) == 1){
				delete ptr->Optr;
				delete ptr->ref_count;
			}else
				(*ptr->ref_count)--;
			delete ptr;
		}
		//Reset
		void reset(){
			delet(ptr);
			ptr = NULL; 
		}
		
		//Reset to another pointer
		template<typename U>
		void reset(U *p){
			delet(ptr);
			ptr = new ObjPtr();
			ptr->Optr = p;
			ptr->ref_count = new int(1);
		}
		//Destructor
		~SharedPtr(){
			delet(ptr);
		}
	};
}//End of namespace
