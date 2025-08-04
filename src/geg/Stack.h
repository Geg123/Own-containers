#pragma once
template<typename K>
class stack
{
public:
	stack() {};
	void push(K value)
	{
		last = new Item(value, last);
		quantity++;
	}
	void pop() 
	{
		if (last != nullptr) {
			Item* tmp = last->previous;
			delete last;
			if (tmp != nullptr)
				last = tmp;
			quantity--;
		}
		else
			throw "Can't pop not existing item";
	}
	K& top() {
		if (last != nullptr) {
			return last->value;
		}
		else
			throw "Can't give out not exiting item";
	}
	int size() { return quantity; }
	bool empty() { return quantity > 0 ? false : true; }
	~stack()
	{
		Item* tmp;
		for (int i = 0;i < quantity; i++)
		{
			tmp = last->previous;
			delete last;
			last = tmp;
		}
	}
private:
	struct Item
	{
		Item* previous = nullptr;
		K value = NULL;
		Item(K val, Item* prev) : value(val), previous(prev) {}
	};

	Item* last = nullptr;
	int quantity = 0;
};