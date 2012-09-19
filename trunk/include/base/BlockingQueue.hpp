// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __BASE_BLOCKING_QUEUE_HPP__
#define __BASE_BLOCKING_QUEUE_HPP__

//#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace{
	typedef struct Node{
		Node* _next;
		void* _value;
		Node() : _next(NULL), _value(NULL){ }
		Node(Node* next, void* value) : _next(next), _value(value){ }
	} Node;
}

namespace CCTool{

#ifdef _WIN32
#define CAS InterlockedCompareExchange
#define ADD(Addend) InterlockedExchangeAdd(Addend,1)
#define SUB(Subend) InterlockedExchangeAdd(Subend,-1)
	//#else
	//#define CAS atomic_compare_exchange_weak
	//#define ADD(Addend) atomic_add(Addend)
	//#define SUB(Subend) atomic_sub(Subend)
	//because i don't kown what's the unix api
#endif

	template<class Ty>
	class BlockingQueue
	{
	public:
		BlockingQueue()
		{
			head = new Node;
			tail = head;
			count = 0;
		}
		~BlockingQueue()
		{
			volatile Node* p = head;
			Node* tmp;
			do
			{
				tmp = p->_next;
				delete p;
				p = tmp;
			}while (p != NULL);
		}

		int size() const
		{
			return count;
		}

		bool isEmpty() const
		{
			return (head->_next == NULL);
		}

		void push(const Ty &t)
		{
			Ty *t_copy = new Ty(t);
			Node* p = new Node(NULL, (void*)t_copy);

			EnQueue(p);
		}

		Ty pop()
		{
			Node* p = DeQueue();

			return *((Ty*)(p->_value));
		}

	protected:
		//noncopyable
		BlockingQueue(const BlockingQueue&);
		BlockingQueue& operator = (const BlockingQueue&);

		void EnQueue(Node* q) 
		{
			volatile Node* p;
			do {

				p = tail;
				while (p->_next != NULL)
					p = p->_next; 
#ifdef _WIN32
#pragma   warning(disable   :   4311)
#endif
			}while(CAS((volatile LONG*)(&(p->_next)), (LONG)q, NULL) != (LONG)NULL); 			
			tail = q;

			ADD((volatile LONG*)&count);
		}

		Node* DeQueue()
		{
			volatile Node* p;
			do{
				p = head;
#ifdef _WIN32
#pragma   warning(disable   :   4311)
#endif
			}while(CAS((volatile LONG*)&head, (LONG)p->_next, (LONG)p) != (LONG)p);

			SUB((volatile LONG*)&count);

			Node* ret = p->_next;
			delete p->_value;
			delete p;

			return ret;
		}


//		LONG CAS(LONG volatile *Target,
//			LONG Exchange,
//			LONG Comperand)
//		{
//#ifdef _WIN32
//			return InterlockedCompareExchange (Target,
//				Exchange,
//				Comperand);
//#endif
//		}
//
//		LONG ADD(LONG volatile *Addend)
//		{
//#ifdef _WIN32
//			return InterlockedExchangeAdd (Addend, 1);
//#endif
//		}
//
//		LONG SUB(LONG volatile *Subend)
//		{
//#ifdef _WIN32
//			return InterlockedExchangeAdd (Subend, -1);
//#endif
//		}

	private:
		volatile Node* head;
		volatile Node* tail;
		volatile int count;
	};

}

//int main()
//{
//	CCTool::BlockingQueue<int> bq;
//
//	std::cout << bq.size() << std::endl;
//	bq.push(1);
//	bq.push(2);
//	bq.push(3);
//	bq.push(4);
//	bq.push(5);
//	bq.push(6);
//
//	std::cout << bq.size() << std::endl;
//	while (!bq.isEmpty())
//	{
//		std::cout << bq.pop() << std::endl;
//	}
//	std::cout << bq.size() << std::endl;
//}


#endif