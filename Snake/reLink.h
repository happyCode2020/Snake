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
	void addData(T data);//ͷ��
	T getItHead();//��ȡͷ�ڵ�
	T getItEnd();//β�ڵ�
	Link<T>* getHeadP();//��ȡͷָ��
	Link<T>* getEndP();//��ȡβָ��
	void moveFrontP();//ͷβָ��ǰ��
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
	while (Head != End) {//ѭ������û�п�ָ��ֱ���пղ��е�
		p = Head;
		Head = Head->next;
		delete p;
	}
	delete End;//����������Բ����ǿյ�
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
