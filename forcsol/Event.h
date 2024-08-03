#pragma once
#include <functional>
#include<forward_list>
using namespace std;
template<typename _T, typename ...Pram>
class Event {
public:
	Event() : FunsList() {}
	~Event() {
		forward_list<function<_T>>().swap(FunsList);
		FunsList.clear();
	}
	void operator() (Pram... P) noexcept {
		for (auto i : FunsList)
			i(P...);
	}
	auto operator+= (function<_T> Funs)noexcept {
		FunsList.push_front(Funs);
	}
private:
	forward_list<function<_T>>FunsList;
};

template<typename _T>
auto Make_Function(_T _Ptr) noexcept {
	return std::function(_Ptr);
}

template<typename ..._T, typename _P>
auto Make_Function(_P _Ptr, _T... BindClass) noexcept {
	return std::bind(_Ptr, BindClass...);
}