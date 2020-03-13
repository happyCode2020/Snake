#pragma once
template<typename T>
struct Link {
	T data;
	Link<T>* front;
	Link<T>* next;
public:
	Link() {
		front = nullptr;
		next = nullptr;
	}
};
template<typename T>
class ReLink {
	Link<T>* Head;
	Link<T>* End;
public:
	ReLink();
	~ReLink();
	void addData(T data);//头插
	T getItHead();//获取头节点
	T getItEnd();//尾节点
	Link<T>* getHeadP();//获取头指针
	Link<T>* getEndP();//获取尾指针
	void moveFrontP();//头尾指针前移
};

template<typename T>
inline ReLink<T>::ReLink()
{
	End = nullptr;
	Head = nullptr;
}

template<typename T>
inline ReLink<T>::~ReLink()
{
	Link<T>* p;
	if (Head == nullptr) return;
	while (Head != End) {//循环链表没有空指针直接判空不行的
		p = Head;
		Head = Head->next;
		delete p;
	}
	delete End;//到了这里绝对不会是空的
	return;
}

template<typename T>
inline void ReLink<T>::addData(T data)
{
	Link<T>* p =new Link<T>;
	p->data = data;
	if (Head==nullptr) {
		Head = p;
		End = Head;
	}
	else
	{
		Head->front = p;
		p->next = Head;
		Head = p;
	}
	Head->front = End;
	End->next = Head;
}

template<typename T>
inline T ReLink<T>::getItHead()
{
	return Head->data;
}

template<typename T>
inline T ReLink<T>::getItEnd()
{
	return End->data;
}

template<typename T>
inline Link<T>* ReLink<T>::getHeadP()
{
	return Head;
}
template<typename T>
inline Link<T>* ReLink<T>::getEndP()
{
	return End;
}

template<typename T>
inline void ReLink<T>::moveFrontP()
{
	Head = Head->front;
	End = End->front;
}
