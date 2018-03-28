#ifndef __DD_LIST__
#define __DD_LIST__

template <class T>
struct Unit
{
	T data{};
	Unit<T> *prev{}, *next{};
	Unit() = default;
	Unit(const T & item) : data(item) {}
};

template <class T>
class DoubleList
{
public:
	DoubleList() = default;
	~DoubleList()
	{
		while (tail)
		{
			Unit<T> * temp = tail->prev;
			delete tail;
			tail = temp;
		}
	}
	void add_node(const T & item)
	{
		Unit<T> * obj;
		if (!head)
		{
			obj = new Unit<T>(item);
			head = obj;
			tail = obj;
			return;
		}
		
	}
	void print() const
	{
		Unit<T> * p = tail;
		while (p)
		{
			cout << tail->data << ' ';
			p = tail->prev;
		}
	}
private:
	Unit<T> *head{};
	Unit<T> *tail{};
};

#endif
