#include <iostream>
#include <functional>
namespace cs540{
using namespace std;
	template<typename T>
	void deleter(const void *p){
		delete static_cast<const T *>(p);
	}
	template<typename T>
	class SharedPtr{
		class ObjPtr{
			public:
			T *Optr=NULL;
			int *ref_count;
			std::function<void(const void *)> del;
		};
		public:
		ObjPtr *ptr = NULL; //Member
		//Default constructors
		SharedPtr(){
			ptr=NULL;
		}

		//Construct a SharedPtr pointing to given object
		template<typename U>
		explicit SharedPtr(U *ptd, std::function<void(const void *)>d = &deleter<U>){
 	               if(ptr == NULL){
        	                ptr = new ObjPtr();
                	        ptr->Optr = ptd;
                        	ptr->ref_count = new int(1);
				ptr->del = d;
                	}
		}

		//cast constructors
		template<typename U>
		explicit SharedPtr(const SharedPtr<U> &sp, int){ //1 for static, 0 for dynamic.
			//static
				ptr = new ObjPtr();
				ptr->Optr = static_cast<T*>(sp.ptr->Optr);
				ptr->ref_count = sp.ptr->ref_count;
				std::function<void(const void *)>d = &deleter<T>;
				ptr->del = d;
				(*ptr->ref_count)++;
		}

		//dyanmic cast constructor
		template<typename U>
		explicit SharedPtr(const SharedPtr<U> &sp, double ){
			T* temp;
			if((temp = dynamic_cast<T*>(sp.ptr->Optr))){
				ptr = new ObjPtr();
				ptr->Optr = temp;
				ptr->ref_count = sp.ptr->ref_count;
				std::function<void(const void *)>d = &deleter<T>;
				ptr->del = d;
				(*ptr->ref_count)++;
			}else{
				ptr = NULL;
			}
		}
		void allocate(const SharedPtr &from){
			if(from.ptr){
			        ptr = new ObjPtr();
				ptr->Optr = from.ptr->Optr;
				ptr->ref_count = from.ptr->ref_count;
				ptr->del = from.ptr->del;
			}else
				ptr = NULL;
		}

		//copy constructor
		SharedPtr(const SharedPtr &p){//copy Constructor
			if(p.ptr != NULL)
                        	(*p.ptr->ref_count)++;
			allocate(p);
		}

		//copy constructor with Change of Type
		template<typename U>
		SharedPtr(const SharedPtr<U> &p){
			if(p.ptr != NULL)
				(*p.ptr->ref_count)++;
	                ptr = new ObjPtr();
			ptr->Optr = p.ptr->Optr;
			ptr->ref_count = p.ptr->ref_count;
			ptr->del = p.ptr->del;
		}

		//Move reference
		SharedPtr(SharedPtr &&p){
//			cout<<"HI"<<endl;
			allocate(p);
			delete p.ptr;
			p.ptr = NULL;
		}

		//Move reference with Change of Type
		template<typename U>
		SharedPtr(SharedPtr<U> &&p){
			allocate(p);
			delete p.ptr;
			p.ptr = NULL;
		}

		//Assignment operator
		SharedPtr &operator=(const SharedPtr &from){
//			cout<<"HI 2"<<endl;
			if(ptr){
				if(ptr == from.ptr)
					return *this;
				else if(*ptr->ref_count == 1){
					delet(ptr);
					ptr=NULL;
				}
				else{
					(*ptr->ref_count)--;
					delete ptr;
					ptr=NULL;
				}
			}
//			delete ptr; //Doubt it.
			allocate(from);
			if(ptr)
				if(ptr->ref_count)
					(*ptr->ref_count)++;
			return *this;
		}

		//Assignment operator with Change of Type
		template<typename U>
		SharedPtr &operator=(const SharedPtr<U> &from){
//			cout<<"HI 3"<<endl;
			if(ptr){
				if(ptr->Optr == from.ptr->Optr)
					return *this;
				else if(*ptr->ref_count == 1){
					delet(ptr);
					ptr=NULL;
				}
				else{
					(*ptr->ref_count)--;
					delete ptr;
					ptr=NULL;
				}
			}
//			delete ptr; //Doubt it.
			allocate(from);
			if(ptr)
				if(ptr->ref_count)
					(*ptr->ref_count)++;
			return *this;
		}

		//Assignment operator with Move
		SharedPtr &operator=(SharedPtr &&p){
			cout<<"HI 4"<<endl;
			if(ptr){
				if(*ptr->ref_count == 1){
					delet(ptr);
					ptr=NULL;
				}
				else{
					(*ptr->ref_count)--;
					delete ptr;
					ptr=NULL;
				}
			}
//			delete ptr;
			allocate(p);
			delete p.ptr;
			p.ptr = NULL;
			return *this;
		}

		//Assignment opeartor with Move Change of Type
		template<typename U>
		SharedPtr &operator=(SharedPtr<U> &&p){
			if(ptr){
				if(*ptr->ref_count == 1){
					delet(ptr);
					ptr=NULL;
				}
				else{
					(*ptr->ref_count)--;
					delete ptr;
					ptr=NULL;
				}
			}
//			delete ptr;
			allocate(p);
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

		T &operator*() const{
			return *get();
		}
		T* operator->(){
			if(ptr)
				return ptr->Optr;
			return NULL;
		}

		operator bool(){
			if(ptr)
				return true;
			return false;
		}
		//Delete if only one reference
		void delet(SharedPtr<T>::ObjPtr *ptr){
			if(!ptr)
				return;
			if(!ptr->ref_count)
				return;
			if((*ptr->ref_count) == 1){
//				decltype(ptr->Optr) r = ptr->Optr;
				ptr->del(ptr->Optr);
//				delete ptr->Optr;
				delete ptr->ref_count;
				ptr->ref_count = NULL;
			}else
				(*ptr->ref_count)--;
			delete ptr;
			ptr=NULL;
		}
		//Reset
		void reset(){
			delet(ptr);
			ptr = NULL;
		}

		//Reset to another pointer
		template<typename U>
		void reset(U *p, std::function<void(const void *)> d = &deleter<U>){
			delet(ptr);
			ptr = new ObjPtr();
			ptr->Optr = p;
			ptr->ref_count = new int(1);
			ptr->del = d;
		}
		//Destructor
		~SharedPtr(){
			delet(ptr);
		}

		//cast
	};

	template<typename T1, typename T2>
	bool operator==(const SharedPtr<T1> &s1, const SharedPtr<T2> &s2){
		if(s1.ptr && s2.ptr)
			return (s1.ptr->Optr == s2.ptr->Optr);
		if(!s1.ptr && !s2.ptr)
			return true;
		return false;
	}

	template<typename T1>
	bool operator==(const SharedPtr<T1> &s1, std::nullptr_t t){
		return(s1.ptr->Optr == t);
	}

	template<typename T1>
	bool operator==(std::nullptr_t t, const SharedPtr<T1> &s1){
		return(s1.ptr->Optr == t);
	}

	template<typename T1, typename T2>
	bool operator!=(const SharedPtr<T1> &s1, const SharedPtr<T2> &s2){
		if(s1.ptr && s2.ptr)
			return (s1.ptr->Optr != s2.ptr->Optr);
		if((s1.ptr && !s2.ptr) || (!s1.ptr && s2.ptr))
			return true;
		return false;
	}
	template<typename T, typename U>
	SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp){
		return SharedPtr<T>(sp, 1);
	}
	template<typename T, typename U>
	SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp){
		return SharedPtr<T>(sp, 1.1);
	}
}//End of namespace
