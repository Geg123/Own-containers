#pragma once
template<typename T>
class queue
{
public:
	queue() {}
	struct Item
	{
		Item(T abc) : value(abc) {}
		Item* previous = nullptr;
		T value = NULL;
	};

	void Add(T var)
	{
		if (first == nullptr)
		{
			first = new Item{ var };
			last = first;
			quantity++;
		}
		else
		{
			Item* tmp = new Item{ var };
			last->previous = tmp;
			last = tmp;
			quantity++;
		}
	}
	void Del()
	{
		Item* tmp = first->previous;
		delete first;
		first = tmp;
		quantity--;
	}
	void Swap(queue con)
	{
		Item* tmp_f = first;
		Item* tmp_l = last;
		first = con.first;
		last = con.last;
		con.first = tmp_f;
		con.last = tmp_l;
	}
	int Size() { return quantity; }

	T First() { return first->value; }
	T Last() { return last->value; }
	bool empty() { return quantity > 0 ? false : true; }

	~queue()
	{
		int max = quantity;
		for (int i = 0; i < max; i++)
		{
			Del();
		}
	}
private:
	Item* first = nullptr;
	Item* last = nullptr;
	int quantity = 0;
};