//
//  main.cpp
//  Move Semantics
//
//  Created by Alan Weide on 9/25/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#include <iostream>
#include <memory>
#include <stack>

#include "CleanStack.hpp"
#include "BoundedMovingStack.cpp"
#include "LinkedStack.cpp"

#include "CleanQueue.hpp"
#include "BoundedQueue.cpp"
#include "LinkedQueue.cpp"

#include "CleanList.hpp"
#include "ListWithCursor.cpp"

using namespace std;

class MoveArrInt {
	int* m_a;
public:
	MoveArrInt(int*&& arr) {
		m_a = arr;
		arr = nullptr;
	}
	MoveArrInt(const MoveArrInt& m_arr) = delete;
	MoveArrInt(MoveArrInt&& m_arr) {
		m_a = m_arr.m_a;
		m_arr.m_a = new int[0];
	}
	MoveArrInt& operator=(const MoveArrInt& m_arr) = delete;
	MoveArrInt& operator=(MoveArrInt&& m_arr) {
		if (&m_arr == this)
			return *this;
		delete[] m_a;
		m_a = m_arr.m_a;
		m_arr.m_a = new int[0];
		return *this;
	}
	int& operator[](std::size_t idx) { return m_a[idx]; }
};

class Resource_forHidden
{
private:
	
	int i_ = 100;
	
public:
	Resource_forHidden(const Resource_forHidden& other) = delete;
	//		Resource_forHidden(const Resource_forHidden& other)
	//		{
	//			i_ = other.i_;
	//			std::cout << "Resource_H " << i_ << " copied\n";
	//		}
	Resource_forHidden(Resource_forHidden&& other)
	{
		i_ = other.i_;
		other.clear(); // modifies other
		
		std::cout << "Resource_H " << i_ << " moved, leaving Resource_H " << other.i_ << "\n";
	}
	
	Resource_forHidden& operator=(const Resource_forHidden& other) = delete;
	//	Resource_forHidden& operator=(const Resource_forHidden& other)
	//	{
	//		if (&other == this) {
	//			return *this;
	//		}
	//		i_ = other.i_;
	//		std::cout << "Resource_H " << i_ << " copied\n";
	//		return *this;
	//
	//	}
	Resource_forHidden& operator=(Resource_forHidden&& other)
	{
		if (&other == this) {
			return *this;
		}
		i_ = other.i_;
		other.clear();
		
		std::cout << "Resource_H " << i_ << " assigned, leaving Resource_H " << other.i_ << "\n";
		return *this;
	}
	
	Resource_forHidden()
	{
		i_ = 100;
		std::cout << "Resource_H " << i_ << " acquired\n";
	}
	
	Resource_forHidden(int i)
	{
		i_ = i;
		std::cout << "Resource_H " << i_ << " acquired\n";
	}
	
	~Resource_forHidden()
	{
		std::cout << "Resource_H " << i_ << " destroyed\n";
	}
	
	void clear() {
		//		i_ = 0; is probably what we want here
		i_ *= -1; // To keep identity information around
	}
	
	void swap(Resource_forHidden& other) {
		int i_t = other.i_;
		other.i_ = i_;
		i_ = i_t;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Resource_forHidden& r)
	{
		out << r.i_;
		return out;
	}
	
};

class Resource_forExplicit
{
private:
	int i_ = 200;
public:
	Resource_forExplicit()
	{
		//		std::cout << "Resource_E " << i_ << " acquired\n";
	}
	
	Resource_forExplicit(int i)
	{
		i_ = i;
		//		std::cout << "Resource_E " << i_ << " acquired\n";
	}
	
	~Resource_forExplicit()
	{
		//		std::cout << "Resource_E " << i_ << " destroyed\n";
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Resource_forExplicit& r)
	{
		out << r.i_;
		return out;
	}
	
};

class SwappableResource
{
private:
	
	int i = 100;
	
	void clear() {
		//		this->i = 0; is probably what we want here
		this->i *= -1; // To keep identity information around
	}
public:
	SwappableResource(const SwappableResource& other) = delete;
	
	SwappableResource(SwappableResource&& other)
	{
		this->i = other.i;
		other.clear(); // modifies other
		
		std::cout << "Resource_H " << this->i << " moved, leaving Resource_H " << other.i << "\n";
	}
	
	SwappableResource& operator=(const SwappableResource& other) = delete;
	
	SwappableResource& operator=(SwappableResource&& other)
	{
		if (&other == this) {
			return *this;
		}
		this->i = other.i;
		other.clear();
		
		std::cout << "Resource_H " << this->i << " assigned, leaving Resource_H " << other.i << "\n";
		return *this;
	}
	
	SwappableResource()
	{
		this->i = 100;
		std::cout << "Resource_H " << this->i << " acquired\n";
	}
	
	SwappableResource(int i)
	{
		this->i = i;
		std::cout << "Resource_H " << this->i << " acquired\n";
	}
	
	~SwappableResource()
	{
		std::cout << "Resource_H " << this->i << " destroyed\n";
	}
	
	friend std::ostream& operator<<(std::ostream& out, const SwappableResource& r)
	{
		out << r.i;
		return out;
	}
	
};
void swap(SwappableResource& r1, SwappableResource& r2)
{
	cout << "Swapping resources " << r1 << " and " << r2 << "\n";
	
	SwappableResource temp = std::move(r1);
	r1 = std::move(r2);
	r2 = std::move(temp);
}

template<typename T> std::ostream& operator<<(std::ostream& out, std::stack<T>& s) {
	if (!s.empty()) {
		auto r_u = std::move(s.top());
		s.pop();
		out << r_u;
		if (!s.empty()) {
			out << ", " << s;
		}
		s.push(std::move(r_u));
	}
	return out;
};

template<typename T>
class Auto_ptr
{
	T* m_ptr;
public:
	Auto_ptr(T* ptr = nullptr)
	:m_ptr(ptr) { }
	~Auto_ptr() { delete m_ptr; }
	
	// Copy constructor
	Auto_ptr(const Auto_ptr& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}
	// Move constructor
	Auto_ptr(Auto_ptr&& a)
	: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr;
	}

	// Copy assignment
	Auto_ptr& operator=(const Auto_ptr& a)
	{
		if (&a == this)
			return *this;
		delete m_ptr;
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
		return *this;
	}
	// Move assignment operator
	Auto_ptr& operator=(Auto_ptr&& a)
	{
		if (&a == this)
			return *this;
		delete m_ptr;
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
private:
	class Contents
	{
	public:
		Contents() { std::cout << "Contents created\n"; }
		~Contents() { std::cout << "Contents destroyed\n"; }
	};
	
	Contents* contents_;
public:
	Resource(Contents* con = nullptr)
	:contents_(con) { }
	
	~Resource() { delete contents_; }

	// Copy constructor
	Resource(const Resource& a)
	{
		contents_ = new Contents;
		*contents_ = *a.contents_;
	}
	// Move constructor
	Resource(Resource&& a)
	: contents_(a.contents_)
	{
		a.contents_ = nullptr;
	}
	
	// Copy assignment
	Resource& operator=(const Resource& a)
	{
		if (&a == this)
			return *this;
		delete contents_;
		contents_ = new Contents;
		*contents_ = *a.contents_;
		return *this;
	}
	// Move assignment operator
//	Resource& operator=(Resource&& a)
//	{
//		if (&a == this)
//			return *this;
//		delete contents_;
//		contents_ = a.contents_;
//		a.contents_ = nullptr;
//		return *this;
//	}

	friend Resource generateResource();
};

Resource generateResource() {
	Resource mainRes(new Resource::Contents);
	return mainRes;
}
int main(int argc, const char *argv[])
{
	Resource mainres;
	mainres = generateResource();
	
	//	int a[] = { 1, 2, 3 };
	//	int* b = a;
	//	b[1] = 4;
	//	printf("a (%p) = {%d, %d, %d}\n", &a, a[0], a[1], a[2]);
	//	printf("b (%p) = {%d, %d, %d}\n", &b, b[0], b[1], b[2]);
	//
	//	int foo[] = { 1, 2, 3 };
	//	printf("foo (%p) = {%d, %d, %d}\n", &foo, foo[0], foo[1], foo[2]);
	//	MoveArrInt am(foo);
	//	printf("foo (%p) = {%d, %d, %d}\n", &foo, foo[0], foo[1], foo[2]);
	//	MoveArrInt bm = std::move(am);
	//	bm[1] = 4; // modify array b
	//	printf("am (%p) = {%d, %d, %d}\n", &am, am[0], am[1], am[2]);
	//	printf("bm (%p) = {%d, %d, %d}\n", &bm, bm[0], bm[1], bm[2]);
	
//	cout << "------ BEGIN S_H ------\n\n";
//
//	cleanpp::bounded_stack<Resource_forHidden> s_h;
//
//	//	SwappableResource r1(1);
//	//	SwappableResource r2(2);
//	//	SwappableResource r3(3);
//	//	SwappableResource r4{4};
//
//	Resource_forHidden r1(1);
//	Resource_forHidden r2(2);
//	Resource_forHidden r3(3);
//	Resource_forHidden r4{4};
//
//	//	Resource_forHidden* r_ptr = new Resource_forHidden(21);
//	//	std::unique_ptr<Resource_forHidden> r_ptr_u(r_ptr);
//	//	std::unique_ptr<Resource_forHidden> r_ptr_m_u = std::make_unique<Resource_forHidden>(*r_ptr);
//	//	std::shared_ptr<Resource_forHidden> r_ptr_s = std::move(r_ptr_u);
//	//
//	//	cout << "r_ptr = " << *r_ptr << " (" << r_ptr << ")\n";
//	//	cout << "r_ptr_u = "<< *r_ptr_u << " (" << r_ptr_u << ")\n";
//	//	cout << "r_ptr_m_u = " << *r_ptr_m_u << " (" << r_ptr_m_u << ")\n";
//
//	cout << "\ns_h = " << s_h << "\n\n";
//	cout << "r1  = " << r1 << "\n";
//	cout << "r2  = " << r2 << "\n";
//	cout << "r3  = " << r3 << "\n";
//	cout << "r4  = " << r4 << "\n\n";
//
//	s_h.push(r1);
//	s_h.push(r2);
//	s_h.push(r3);
//	s_h.push(r4);
//
//	cout << "\ns_h = " << s_h << "\n";
//	cout << "r1  = " << r1 << "\n";
//	cout << "r2  = " << r2 << "\n";
//	cout << "r3  = " << r3 << "\n";
//	cout << "r4  = " << r4 << "\n";
//
//	cout << "\n";
//
//	s_h.pop(r4);
//	s_h.pop(r3);
//	s_h.pop(r2);
//	s_h.pop(r1);
//
//	cout << "\ns_h = " << s_h << "\n\n";
//	cout << "r1  = " << r1 << "\n";
//	cout << "r2  = " << r2 << "\n";
//	cout << "r3  = " << r3 << "\n";
//	cout << "r4  = " << r4 << "\n";
//
//	cout << "\n";
//
//	cout << "\n------  END S_H  ------\n";
	
	//	cout << "------ BEGIN S_E ------\n\n";
	//
	//	BoundedMovingStack_Explicit<Resource_forExplicit> s_e;
	//
	//	auto r5_u = std::make_unique<Resource_forExplicit>(5);
	//	auto r6_u = std::make_unique<Resource_forExplicit>(6);
	//	auto r7_u = std::make_unique<Resource_forExplicit>(7);
	//	auto r8_u = std::make_unique<Resource_forExplicit>(8);
	//
	//	cout << "\ns_e  = " << s_e << "\n\n";
	//	cout << "r5_u  = " << *r5_u << "\n";
	//	cout << "r6_u  = " << *r6_u << "\n";
	//	cout << "r7_u  = " << *r7_u << "\n";
	//	cout << "r8_u  = " << *r8_u << "\n\n";
	//
	//	s_e.push(r5_u);
	//	s_e.push(r6_u);
	//	s_e.push(r7_u);
	//	s_e.push(r8_u);
	//
	//	cout << "\ns_e  = " << s_e << "\n\n";
	//	cout << "r5_u = " << *r5_u << "\n";
	//	cout << "r6_u = " << *r6_u << "\n";
	//	cout << "r7_u = " << *r7_u << "\n";
	//	cout << "r8_u = " << *r8_u << "\n\n";
	//
	//	s_e.pop(r8_u);
	//	s_e.pop(r7_u);
	//	s_e.pop(r6_u);
	//	s_e.pop(r5_u);
	//
	//	cout << "\ns_e  = " << s_e << "\n\n";
	//	cout << "r5_u = " << *r5_u << "\n";
	//	cout << "r6_u = " << *r6_u << "\n";
	//	cout << "r7_u = " << *r7_u << "\n";
	//	cout << "r8_u = " << *r8_u << "\n\n";
	//
	//	cout << "\n------  END S_E  ------\n";
	
	//	cout << "------ BEGIN S_C ------\n\n";
	//
	//	cleanpp::clean_stack<Resource_forHidden>* s_c = new cleanpp::linked_stack<Resource_forHidden>{ };
	//
	//	Resource_forHidden r9(9);
	//	Resource_forHidden r10(10);
	//	Resource_forHidden r11(11);
	//	Resource_forHidden r12(12);
	//
	//	cout << "\ns_c  = " << *s_c << "\n\n";
	//	cout << "r9    = " << r9 << "\n";
	//	cout << "r10   = " << r10 << "\n";
	//	cout << "r11   = " << r11 << "\n";
	//	cout << "r12   = " << r12 << "\n\n";
	//
	//	s_c->push(r9);
	//	s_c->push(r10);
	//	s_c->push(r11);
	//	s_c->push(r12);
	//
	//	cout << "\ns_c  = " << *s_c << "\n\n";
	//	cout << "r9    = " << r9 << "\n";
	//	cout << "r10   = " << r10 << "\n";
	//	cout << "r11   = " << r11 << "\n";
	//	cout << "r12   = " << r12 << "\n\n";
	//
	//	s_c->pop(r12);
	//	s_c->pop(r11);
	//	s_c->pop(r10);
	//	s_c->pop(r9);
	//
	//	cout << "\ns_c  = " << *s_c << "\n\n";
	//	cout << "r9    = " << r9 << "\n";
	//	cout << "r10   = " << r10 << "\n";
	//	cout << "r11   = " << r11 << "\n";
	//	cout << "r12   = " << r12 << "\n\n";
	//
	//	cout << "\n------  END S_C  ------\n";
	//
	//	cout << "------ BEGIN L_C ------\n\n";
	//
	//	cleanpp::list<Resource_forHidden>* l_c = new cleanpp::clean_list<Resource_forHidden>{ };
	//
	//	Resource_forHidden r13(13);
	//	Resource_forHidden r14(14);
	//	Resource_forHidden r15(15);
	//	Resource_forHidden r16(16);
	//
	//	cout << "\nl_c  = " << *l_c << "\n\n";
	//	cout << "r13   = " << r13 << "\n";
	//	cout << "r14   = " << r14 << "\n";
	//	cout << "r15   = " << r15 << "\n";
	//	cout << "r16   = " << r16 << "\n";
	//
	//	l_c->insert(r13);
	//	l_c->insert(r14);
	//	l_c->insert(r15);
	//	l_c->insert(r16);
	//
	//	cout << "\nl_c  = " << *l_c << "\n\n";
	//	cout << "r13   = " << r13 << "\n";
	//	cout << "r14   = " << r14 << "\n";
	//	cout << "r15   = " << r15 << "\n";
	//	cout << "r16   = " << r16 << "\n";
	//
	//	l_c->retreat();
	//	cout << "\nl_c  = " << *l_c << "\n";
	//
	//	l_c->retreat();
	//	cout << "\nl_c  = " << *l_c << "\n";
	//
	//	l_c->remove(r14);
	//	l_c->remove(r13);
	//
	//	cout << "\nl_c  = " << *l_c << "\n\n";
	//	cout << "r13   = " << r13 << "\n";
	//	cout << "r14   = " << r14 << "\n";
	//	cout << "r15   = " << r15 << "\n";
	//	cout << "r16   = " << r16 << "\n";
	//
	//	l_c->advance();
	//	l_c->advance();
	//
	//	l_c->remove(r16);
	//	l_c->remove(r15);
	//
	//	cout << "\nl_c  = " << *l_c << "\n\n";
	//	cout << "r13   = " << r13 << "\n";
	//	cout << "r14   = " << r14 << "\n";
	//	cout << "r15   = " << r15 << "\n";
	//	cout << "r16   = " << r16 << "\n";
	//	cout << "\n------  END L_C  ------\n";
	
	//	cout << "\n------ BEGIN L_Q ------\n";
	//
	//	std::unique_ptr<cleanpp::clean_queue<Resource_forHidden>> l_q = std::make_unique<cleanpp::linked_queue<Resource_forHidden>>();
	//
	//	std::unique_ptr<Resource_forHidden> r17 = std::make_unique<Resource_forHidden>(17);
	//	std::unique_ptr<Resource_forHidden> r18 = std::make_unique<Resource_forHidden>(18);
	//	std::unique_ptr<Resource_forHidden> r19 = std::make_unique<Resource_forHidden>(19);
	//	std::unique_ptr<Resource_forHidden> r20 = std::make_unique<Resource_forHidden>(20);
	//
	//	cout << "\nl_q  = " << *l_q << "\n\n";
	//	cout << "r17   = " << *r17 << "\n";
	//	cout << "r18   = " << *r18 << "\n";
	//	cout << "r19   = " << *r19 << "\n";
	//	cout << "r20   = " << *r20 << "\n";
	//
	//	l_q->enqueue(r17);
	//	l_q->enqueue(r18);
	//	l_q->enqueue(r19);
	//	l_q->enqueue(r20);
	//
	//	cout << "\nl_q  = " << *l_q << "\n\n";
	//	cout << "r17   = " << *r17 << "\n";
	//	cout << "r18   = " << *r18 << "\n";
	//	cout << "r19   = " << *r19 << "\n";
	//	cout << "r20   = " << *r20 << "\n";
	//
	//	l_q->dequeue(r17);
	//	l_q->dequeue(r18);
	//	l_q->dequeue(r19);
	//	l_q->dequeue(r20);
	//
	//	cout << "\nl_q  = " << *l_q << "\n\n";
	//	cout << "r17   = " << *r17 << "\n";
	//	cout << "r18   = " << *r18 << "\n";
	//	cout << "r19   = " << *r19 << "\n";
	//	cout << "r20   = " << *r20 << "\n";
	//
	//	cout << "\n------  END L_Q ------\n";
	
	//	cout << "\n------ BEGIN B_Q ------\n";
	//
	//	cleanpp::clean_queue<Resource_forHidden>* b_q = new cleanpp::bounded_queue<Resource_forHidden>{ };
	//
	//	Resource_forHidden r21(21);
	//	Resource_forHidden r22(22);
	//	Resource_forHidden r23(23);
	//	Resource_forHidden r24{24};
	//
	//	cout << "\nb_q  = " << *b_q << "\n\n";
	//	cout << "r21   = " << r21 << "\n";
	//	cout << "r22   = " << r22 << "\n";
	//	cout << "r23   = " << r23 << "\n";
	//	cout << "r24   = " << r24 << "\n";
	//
	//	b_q->enqueue(r21);
	//	b_q->enqueue(r22);
	//	b_q->enqueue(r23);
	//	b_q->enqueue(r24);
	//
	//	cout << "\nb_q  = " << *b_q << "\n\n";
	//	cout << "r21   = " << r21 << "\n";
	//	cout << "r22   = " << r22 << "\n";
	//	cout << "r23   = " << r23 << "\n";
	//	cout << "r24   = " << r24 << "\n";
	//
	//	b_q->dequeue(r21);
	//	b_q->dequeue(r21);
	//	b_q->dequeue(r21);
	//	b_q->dequeue(r21);
	//
	//	cout << "\nb_q  = " << *b_q << "\n\n";
	//	cout << "r21   = " << r21 << "\n";
	//	cout << "r22   = " << r22 << "\n";
	//	cout << "r23   = " << r23 << "\n";
	//	cout << "r24   = " << r24 << "\n";
	//
	//	cout << "\n------  END B_Q ------\n";
	
	return 0;
}
