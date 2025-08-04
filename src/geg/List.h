#pragma once

template<typename L>
class list
{
private:
	struct Node
	{
		L value = NULL;
		Node* prev = nullptr;
		Node* next = nullptr;
		Node() {}
		Node(L _value) : value(_value) {}
		Node(L _value, Node* _prev) : value(_value), prev(_prev) {}

	};

	struct iterator
	{
		list* parent = nullptr;
		Node* node = nullptr;
		iterator(list* _parent) : parent(_parent){}

		iterator& operator ++ ()
		{
			if (node->next != nullptr)
			{
				node = node->next;
				return *this;
			}
			else
				throw "node doesn't exist";
		}
		iterator& operator -- ()
		{
			if (node != nullptr) {
				if (node->prev != nullptr)
				{
					node = node->prev;
					return *this;
				}
				else
					throw "node doesn't exist";
			}
			else {
				if (parent->size() > 0)
				{
					node = parent->last;
					return *this;
				}
			}
		}
		bool operator == (iterator& right)
			if(right.node == this.node)
			{
				return true;
			}
			else
		};
public:
	list(int _size)
	{
		first = new Node;
		_size++;
		last = first;
		Node* tmp = first;
		for (int i = 0; i < _size - 1; i++)
		{
			last = new Node;
			tmp->next = last;
			last->prev = tmp;
			tmp = tmp->next;
			_size++;
		}
	}
	list(int _size, L val)
	{
		first = new Node(val);
		_size++;
		last = first;
		Node* tmp = first;
		for (int i = 0; i < _size - 1; i++)
		{
			last = new Node;
			tmp->next = last;
			last->prev = tmp;
			tmp = tmp->next;
			_size++;
		}
	}

	list(std::initializer_list<L> _list)
	{
		_size = _list.size();
		const L* a = _list.begin();
		first = new Node(*a);
		Node* tmp = first;
		Node* tmp2 = nullptr;
		for (int i = 1; i < _size; i++)
		{
			a = _list.begin() + i;
			tmp2 = new Node(*a, tmp);
			tmp->next = tmp2;
			tmp = tmp2;
		}
		last = tmp2;
	}

	list(list* right)
	{
		if (right->first != nullptr)
		{
			L val = right->first->value;
			Node* rtmp = right->first->next;
			Node* tmp = new Node(val);
			Node* tmp2 = tmp;
			_size++;
			first = tmp;
			while (rtmp != nullptr)
			{
				val = rtmp->value;
				tmp = new Node(val, tmp2);
				tmp2 = tmp;
				rtmp = rtmp->next;
				_size++;
			}
			last = tmp2;
		}
	}

	~list()
	{
		Node* tmp = first;
		Node* tmp2;
		while (tmp != nullptr)
		{
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
	}
	int size()
	{
		return _size;
	}

	L& front()
	{
		if (first != nullptr)
			return first->value;
		else
			throw "first node of list doesn't exist";
	}

	L& back()
	{
		if (last != nullptr)
			return last->value;
		else
			throw "last node of list doesn't exist";
	}

	void push_back(L value)
	{

		if (last == nullptr)
		{
			Node* tmp = new Node(value);
			last = tmp;
			first = tmp;
		}
		else
		{
			Node* tmp = new Node(value, last);
			last->next = tmp;
			last = tmp;
		}
		_size++;
	}

	void push_front(L value)
	{
		if (first == nullptr)
		{
			Node* tmp = new Node(value);
			first = tmp;
			last = tmp;
		}
		else
		{
			Node* tmp = new Node(value);
			tmp->next = first;
			first = tmp;
		}
		_size++;
	}

	void pop_back()
	{
		if (last != nullptr)
		{
			if (last->prev != nullptr)
			{
				Node* tmp = last->prev;
				delete last;
				last = tmp;
			}
			else
			{
				delete last;
				last = nullptr;
			}
			_size--;
		}
		else
			throw "last node doesn't exist";
	}

	void pop_front()
	{
		if (first != nullptr)
		{
			if (first->next != nullptr)
			{
				Node* tmp = first->next;
				delete first;
				first = tmp;
			}
			else
			{
				delete first;
				first = nullptr;
			}
			_size--;
		}
		else
			throw "first node doesn't exist";
	}

	void clear()
	{
		Node* tmp = first;
		Node* tmp2;
		while (tmp != nullptr)
		{
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		_size = 0;
		last = nullptr;
		first = nullptr;
	}

	void assign(std::initializer_list<L> _list)
	{
		this->clear();
		_size = _list.size();
		const L* a = _list.begin();
		first = new Node(*a);
		Node* tmp = first;
		Node* tmp2 = nullptr;
		for (int i = 1; i < _size; i++)
		{
			a = _list.begin() + i;
			tmp2 = new Node(*a, tmp);
			tmp->next = tmp2;
			tmp = tmp2;
		}
		last = tmp2;
	}

	void assign(int size, L val)
	{
		this->clear();
		if (size != 0) {
			first = new Node(val);
			_size++;
			last = first;
		}
		Node* tmp = first;
		for (int i = 0; i < size - 1; i++)
		{
			last = new Node(val);
			tmp->next = last;
			last->prev = tmp;
			tmp = tmp->next;
			_size++;
		}
	}

	void assign(iterator begin_, iterator end_)
	{
		Node* tmpb = begin_.node;
		tmpb = tmpb->prev;
		Node* tmp;
		while (tmpb != nullptr)
		{
			tmp = tmpb->prev;
			delete tmpb;
			tmpb = tmp;
			_size--;
		}
		tmpb = end_.node;
		last = tmpb->prev;
			while (tmpb != nullptr)
			{
				tmp = tmpb->next;
				delete tmpb;
				tmpb = tmp;
				_size--;
			}
		first = begin_.node;
	}

	void swap(list* right)
	{
		Node* tmp_first = right->first;
		Node* tmp_last = right->last;
		right->first = this->first;
		right->last = this->last;
		this->first = tmp_first;
		this->last = tmp_last;
	}

	iterator& begin()
	{
		_begin.node = first;
		return _begin;
	}

	iterator& end()
	{
		_end.node = nullptr;
		_end.node = last->next;
		return _end;
	}

private:

	Node* first = nullptr;
	Node* last = nullptr;
	int _size = 0;
	iterator _begin{this};
	iterator _end{this};
	iterator pos{this};
};
