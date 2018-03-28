#ifndef __ITERATOR_H__
#define __ITERATOR_H__


template <class T>
class Iterator
{
public:
	Iterator() = default;
	virtual void Next() = 0;
	virtual void Reset() = 0;
	virtual T & Data() = 0;
	virtual int End_List() const;
protected:
	int iteration_complete{};
};

template <class T>
int Iterator<T>::End_List() const
{
	return iteration_complete;
}

template <class T>
class List_Iterator : public Iterator<T>
{
public:
	List_Iterator(List<T> &);
	virtual void Next();
	virtual void Reset();
	virtual T & Data();
	void Set_List(List<T> &);
private:
	List<T> * plist{};
	Node<T> * prev{}, * curr{};
};

template <class T>
List_Iterator<T>::List_Iterator(List<T> & obj) : Iterator<T>(), plist(&obj)
{
	iteration_complete = plist->list_empty();
	Reset();
}

template <class T>
void List_Iterator<T>::Next()
{
	if (curr == nullptr)
	{
		return;
	}
	prev = curr;
	curr = curr->next;
	if (curr == nullptr)
	{
		iteration_complete = 1;
	}
}

template <class T>
void List_Iterator<T>::Reset()
{
	iteration_complete = plist->list_empty();
	if (plist->head == nullptr)
	{
		return;
	}
	prev = nullptr;
	curr = plist->head;
}

template <class T>
T & List_Iterator<T>::Data()
{
	if (curr == nullptr || plist->size_list() == 0)
	{
		exit(1);
	}
	return curr->data;
}

template <class T>
void List_Iterator<T>::Set_List(List<T> & obj)
{
	plist = &obj;
	Reset();
}

#endif // !__ITERATOR_H__
