#include <iostream>
#include <functional>
using namespace std;
void func(){
	cout<<"HEYA"<<endl;
}
int main(){
	std::function<void(void)>f = func;
	f();
}
