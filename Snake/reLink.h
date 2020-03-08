#pragma once
template<typename T>
struct Link {
	T data;
	Link<T>* next;
public:
	Link() {
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
	void addData(T data);//ͷ��
	T getItHead();//��ȡͷ�ڵ�
	T getItEnd();//β�ڵ�
	Link<T>* getHeadP();//��ȡͷָ��
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
	while (Head!=nullptr&&Head!=End) {
		p = Head;
		Head = Head->next;
		delete p;
	}
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
		p->next = Head;
		Head = p;
	}
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
