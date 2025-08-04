#pragma once
template<typename T>
class queue
{
private:
	struct Item
	{
		Item(T abc) : value(abc) {}
		Item* previous = nullptr;
		T value = NULL;
	};
public:
	queue() {}

	void add(T var)
	{
		if (_first == nullptr)
		{
			_first = new Item{ var };
			_last = _first;
			quantity++;
		}
		else
		{
			Item* tmp = new Item{ var };
			_last->previous = tmp;
			_last = tmp;
			quantity++;
		}
	}

	void del()
	{
		Item* tmp = _first->previous;
		delete _first;
		_first = tmp;
		quantity--;
	}
	void swap(queue& con)
	{
		Item* tmp_f = _first;
		Item* tmp_l = _last;
		_first = con._first;
		_last = con._last;
		con._first = tmp_f;
		con._last = tmp_l;
	}
	int size() { return quantity; }

	T& first() { return _first->value; }
	T& last() { return _last->value; }
	bool empty() { return quantity > 0 ? false : true; }

	~queue()
	{
		int max = quantity;
		for (int i = 0; i < max; i++)
		{
			del();
		}
	}
private:
	Item* _first = nullptr;
	Item* _last = nullptr;
	int quantity = 0;
};