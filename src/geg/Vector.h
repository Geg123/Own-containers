#pragma once

template<typename Y>
class vector
{
private:
	struct iterator
	{
		Y* item = nullptr;
		iterator& operator ++ ()
		{
			if (list + vec_size - 1 >= (item + 1))
			{
				++item;
				return *this;
			}
			else
				return 0;
		}
		iterator& operator -- ()
		{
			if (list <= (item - 1))
			{
				--item;
				return *this;
			}
			else
				return 0;
		}
	};
public:
	vector(){}
	vector(std::initializer_list<Y> _list)
	{
		int _size = _list.size();
		quantity = _size;
		last_index = quantity - 1;
		_size = _size + _size / 2;
		vec_size = _size;
		list = new Y[_size];
		int k = 0;
		for (const Y* i = _list.begin(); i <= _list.end(); i++)
		{
			*(list + k) = *i;
			k++;
		}
		copy = list;
	}
	~vector() { delete[] list; }
	vector(int lenght)
	{
		Y* _list = new Y[lenght];
	}
	void operator = (vector* right)
	{
		int l_size = right->vec_size;
		this->list = new Y[l_size];
	}
	Y& operator [] (int i)
	{
		if (i <= last_index) 
		{
			return (*(copy + i));
		}
		else
		{
			return 0;
		}
	}

	void push_back(Y value)
	{
		quantity++;
		if (quantity > vec_size)
		{
			int new_size = vec_size + 1 + (vec_size + 1) / 2;
			copy = new Y[new_size];
			for (int i = 0;i < quantity;i++)
			{
				*(copy + i) = *(list + i);
			}
			delete[] list;
			list = copy;
			vec_size = new_size;
		}
		else
		{
			*(list + last_index + 1) = value;
		}
		last_index++;
	}

	Y& front()
	{
		if (list != nullptr)
			return *list;
		else
			return 0;
	}
	Y& back() 
	{
		if (list + last_index != nullptr)
			return *(list + last_index);
		else
			return 0;
	}

	int capacity() { return vec_size; }
	int size() { return quantity; }
	bool empty() { return quantity > 0 ? false : true; }

	iterator& begin()
	{
		_begin.item = list;
		return _begin;
	}
	
	iterator& end()
	{
		_end.item = list + last_index;
		return _end;
	}
private:
	Y* list = nullptr;
	Y* copy = nullptr;
	int quantity = 0;
	int vec_size = 0;
	int last_index = 0;
	iterator _begin;
	iterator _end;
};