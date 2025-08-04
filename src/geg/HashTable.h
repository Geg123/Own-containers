#pragma once
#include<cmath>

template<typename U, typename O>
class hash_table
{
public:
	~hash_table()
	{
		for (int i = 0;i < n;i++)
		{
			Bucket* tmp = bucket_list + i;
			if (tmp->first_item != null_first && tmp->first_item != null_item)
			{
				Item* i_tmp = tmp->first_item;
				Item* i_copy = i_tmp->next;
				while (i_tmp->next != null_item)
				{
					delete i_tmp;
					i_tmp = i_copy;
					i_copy = i_tmp->next;
				}
				delete i_tmp;
			}
		}
		delete[] bucket_list;
		delete null_first;
		delete null_item;
	}
	
	hash_table()
	{
		Bucket* tmp;
		bucket_list = new Bucket[n];
		for (int i = 0; i < n; i++)
		{
			tmp = bucket_list + i;
			tmp->first_item = null_first;
		}
	}
	hash_table(int lenght_bucket_list)
	{
		if (lenght_bucket_list > 0) {
			n = lenght_bucket_list;
			Bucket* tmp;
			bucket_list = new Bucket[n];
			for (int i = 0; i < n; i++)
			{
				tmp = bucket_list + i;
				tmp->first_item = null_first;
			}
		}
	}

	void insert(U pre_hash, O value)
	{
		int hash_tmp = hashfunc(pre_hash);
		int tmp = abs(hash_tmp % n);
		Bucket* ptr_tmp = bucket_list + tmp;
		if (ptr_tmp->first_item == null_first)
		{
			ptr_tmp->first_item = new Item(pre_hash, value, null_item);
		}
		else {
			Item* i_ptr = ptr_tmp->first_item;
			while (i_ptr->next != null_item)
			{
				i_ptr = i_ptr->next;
			}
			Item* last_i_ptr = new Item(pre_hash, value, null_item, i_ptr);
			i_ptr->next = last_i_ptr;
		}
		ptr_tmp->item_quantity++;
		_size++;
	}

	O& out(U pre_hash)
	{
		int hash_tmp = hashfunc(pre_hash);
		int tmp = abs(hash_tmp % n);
		Bucket* ptr_tmp = bucket_list + tmp;
		Item* i_ptr = ptr_tmp->first_item;
		U id_tmp;
		bool until = true;
		while (until)
		{
			id_tmp = i_ptr->id;
			if (id_tmp == pre_hash)
				return i_ptr->value;
			else
			{
				if (i_ptr->next == null_item)
				{
					throw "Item with same id doesn't exist";
				}
				else
					i_ptr = i_ptr->next;
			}
		}
	}

	void del(U pre_hash)
	{
		int hash_tmp = hashfunc(pre_hash);
		int tmp = abs(hash_tmp % n);
		Bucket* ptr_tmp = bucket_list + tmp;
		Item* i_ptr = (ptr_tmp->first_item);
		while (i_ptr->id != pre_hash) 
		{ i_ptr = i_ptr->next; 
		if (i_ptr == null_item)
			throw "Not item with same id";
		}
		if (i_ptr == (ptr_tmp->first_item))
		{
			delete i_ptr;
			ptr_tmp->first_item = null_first;
		}
		else
		{
			Item* pre_i_ptr = i_ptr->previous;
			Item* next_i_ptr = i_ptr->next;
			pre_i_ptr->next = next_i_ptr;
			next_i_ptr->previous = pre_i_ptr;
			delete i_ptr;
		}
		ptr_tmp->item_quantity--;
		_size--;
	}

	int bucket_size(int number)
	{
		if (number < n)
		{
			Bucket* tmp = bucket_list + number;
			return tmp->item_quantity;
		}
		else
		{ 
			throw "Out of bucket list range";
		}
	}

	int size() { return _size; }

	bool empty() { return _size > 0 ? false : true; }

	void rehash(int lenght)
	{
		if (lenght > 0) {
			Bucket* bucket_list_tmp = new Bucket[lenght];
			Bucket* tmp;
			for (int i = 0; i < lenght; i++)
			{
				tmp = bucket_list_tmp + i;
				tmp->first_item = null_first;
			}
			Bucket* bucket_tmp;
			Item* item_tmp;
			Bucket* new_bucket_tmp;
			for (int i = 0; i < n;i++)
			{
				bucket_tmp = bucket_list + i;
				if (bucket_tmp->item_quantity > 0)
				{
					item_tmp = bucket_tmp->first_item;

					int hash = hashfunc(item_tmp->id);
					int abs_hash = abs(hash % lenght);
					new_bucket_tmp = bucket_list_tmp + abs_hash;
					new_bucket_tmp->first_item = item_tmp;
				}
			}
			delete[] bucket_list;
			bucket_list = bucket_list_tmp;
			n = lenght;
		}
	}

	int bucket_count() { return n; }
private:
	struct Item
	{
		Item* next;
		Item* previous;
		O value;
		U id;
		Item() {}
		Item(U val_id, O val, Item* nl) : id(val_id), value(val), next(nl), previous(nl) {}
		Item(U val_id, O val, Item* nl, Item* prev) : id(val_id), value(val), next(nl), previous(prev) {}
		Item(Item* nm) : next(nm), previous(nm) {}
		Item(Item _next_prev, U _id) : next(_next_prev), previous(_next_prev), id(_id) {}

	};

	Item* null_item = new Item;
	Item* null_first = new Item(null_item);

	struct Bucket
	{
		int item_quantity = 0;
		Item* first_item;
	};

	int hashfunc(U id) { return std::hash<U>{}(id); }
	Bucket* bucket_list;
	int n = 16;
	int _size = 0;
};