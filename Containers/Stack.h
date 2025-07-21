#pragma once
template<typename K>
class stack
{
public:
	
	void push(K value)
	{
		last = new Item(value, last);
		quantity++;
	}
	void pop() 
	{ 
		Item* tmp = last->previous; 
		delete last;
		if(tmp != nullptr)
			last = tmp; 
		quantity--; }
	K& top() { return last->value; }
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