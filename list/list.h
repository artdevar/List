#ifndef __LIST_H__
#define __LIST_H__

#define NULL 0

template <class T>
struct Node
{
	T data{};
	Node<T> *next{};
	Node() = default;
	Node(const T & item) : data(item) {}
};

template <class T>
class List
{	
public:
	List() = default;
	List(const List<T> &);
	~List();
	// push methods
	void add_front(const T &);
	void add_front(Node<T> *);
	void add_node(const T &);
	void add_node(Node<T> *);
	// clear
	void clear_list();
	// pop methods
	auto delete_index(const int);
	auto delete_key(const T &);
	// output, size, take element by index 
	void print() const;
	const auto & size_list() const;
	T & operator[](const int);
	// merge
	void merge(List<T> &);
	// sorts
	List<T> sort();
	List<T> reverse();
	// other
	List<T> & operator=(const List<T> &);
	bool list_empty() const;
	// iterator
	template <class T>
	class Iterator
	{
	public:
		Iterator(List<T> & obj) : plist(&obj) 
		{
			Reset();
		}
		void Next()
		{
			prev = curr;
			curr = curr->next;
		}
		void Reset()
		{
			prev = nullptr;
			curr = plist->head;
		}
		T & Data()
		{
			return curr->data;
		}
		bool End_List() const
		{
			return curr == nullptr;
		}
	private:
		List<T> *plist{};
		Node<T> *prev{}, *curr{};
	};
private:
	Node<T> *head{};
	size_t size{};
};

// --- //

template <class T>
List<T>::List(const List<T> & obj)
{
	Node<T> *p = obj.head;
	this->head = new Node<T>(p->data);
	Node<T> *k = this->head;
	p = p->next;
	while (p)
	{
		k->next = new Node<T>{};
		k = k->next;
		k->data = p->data;
		p = p->next;
	}
	this->size = obj.size;
}

template <class T>
List<T>::~List()
{
	this->clear_list();
}

template <class T>
void List<T>::add_front(const T & item)
{
	Node<T> * p = new Node<T>(item);
	size++;
	if (!head)
	{
		head = p;
		return;
	}
	p->next = head;
	head = p;
}

template <class T>
void List<T>::add_front(Node<T> * obj)
{
	size++;
	if (!head)
	{
		head = obj;
		return;
	}
	obj->next = head;
	head = obj;
}

template <class T>
void List<T>::add_node(const T & item)
{
	Node<T> * p{};
	if (size == NULL)
	{
		p = new Node<T>(item);
		head = p;
	}
	else
	{
		p = head;
		while (p->next)
		{
			p = p->next;
		}
		p->next = new Node<T>(item);
		p = p->next;
	}
	size++;
}

template <class T>
void List<T>::add_node(Node<T> * obj)
{
	size++;
	if (!head)
	{
		head = obj;
	}
	Node<T> *p = head;
	while (p->next)
	{
		p = p->next;
	}
	p->next = obj;
}

template <class T>
void List<T>::clear_list()
{
	while (head)
	{
		Node<T> * t = head->next;
		delete head;
		head = t;
	}
	size = 0;
}

template <class T>
auto List<T>::delete_index(const int index)
{
	if (size == NULL || index < 0 || index >= size)
	{
		return NULL;
	}
	Node<T> * t{};
	if (index == 0)
	{
		t = head->next;
		T temp = head->data;
		delete head;
		head = t;
		size--;
		return temp;
	}
	int j(1);
	t = head;
	while (j != index)
	{
		t = t->next;
		j++;
	}
	Node<T> *t1 = t->next->next;
	delete t->next;
	t->next = t1;
	size--;
}

template <class T>
auto List<T>::delete_key(const T & key)
{
	if (size == NULL)
	{
		return NULL;
	}
	Node<T> *t = head;
	if (t->data == key)
	{
		t = head->next;
		T temp = head->data;
		delete head;
		head = t;
		size--;
		return temp;
	}
	Node<T> * t1 = t->next;
	while (t1)
	{
		if (t1->data == key)
		{
			break;
		}
		t = t->next;
		t1 = t1->next;
	}
	if (t1 == nullptr)
	{
		return NULL;
	}
	T temp = t1->data;
	t->next = t1->next;
	delete t1;
	size--;
	return temp;
}

template <class T>
void List<T>::print() const
{
	if (size == NULL)
	{
		return;
	}
	Node<T> *t = head;
	while (t)
	{
		cout << t->data << " -> ";
		t = t->next;
	}
	cout << "NULL" << endl;
}

template <class T>
const auto & List<T>::size_list() const
{
	return size;
}

template <class T>
T & List<T>::operator[](const int index)
{
	if (size == NULL || index < 0 || index >= size)
	{
		exit(1);
	}
	Node<T> *p = head;
	int j(0);
	while (index != j)
	{
		p = p->next;
		j++;
	}
	return p->data;
}

template <class T>
void List<T>::merge(List<T> & obj)
{
	Node<T> *p = head;
	while (p->next)
	{
		p = p->next;
	}
	while (obj.head)
	{
		p->next = obj.head;
		obj.head = obj.head->next;
		p = p->next;
	}
	this->size += obj.size;
}


template <class T>
List<T> List<T>::sort()
{
	List<T> Res;
	T min{};
	int resize = this->size;
	while (resize)
	{
		Node<T> * j = head;
		min = head->data;
		int index = 0;
		int count = 0;
		while (j)
		{
			if (min > j->data)
			{
				min = j->data;
				index = count;
			}
			j = j->next;
			count++;
		}
		this->delete_index(index);
		Res.add_node(min);
		resize--;
	}
	this->clear_list();
	return Res;
}

template <class T>
List<T> List<T>::reverse()
{
	List<T> Res;
	Node<T> * p = head;
	while (p)
	{
		Res.add_front(p->data);
		p = p->next;
	}
	return Res;
}

template <class T>
List<T> & List<T>::operator=(const List<T> & obj)
{
	if (obj.head)
	{
		Node<T> *p = obj.head;
		this->head = new Node<T>{};
		this->head->data = p->data;
		Node<T> *k = this->head;
		p = p->next;
		while (p)
		{
			k->next = new Node<T>{};
			k = k->next;
			k->data = p->data;
			p = p->next;
		}
		this->size = obj.size;
		return *this;
	}
}

template <class T>
bool List<T>::list_empty() const
{
	return size == 0;
}

#endif // __LIST_H__
