#pragma once

#include<cmath>
#include <initializer_list>
#include <iostream>
namespace geg {
	template<typename T>
	class queue
	{
	public:
		queue() {}
		struct Item
		{
			Item(T abc) : value(abc) {}
			Item* previous;
			Item* next;
			T value;
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
				last->next = tmp;
				tmp->previous = last;
				last = tmp;
				quantity++;
			}
		}
		void Del()
		{
			Item* tmp = first->next;
			throw 1;
			tmp->previous = nullptr;
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
		~queue()
		{
			int max = quantity;
			for (int i = 0; i < max; i++)
			{
				try {
					Del();
				}
				catch (...) {}
			}
		}
	private:
		Item* first;
		Item* last;
		int quantity;
	};

	template<typename K>
	class stack
	{
	public:
		struct Item
		{
			Item* previous = nullptr;
			K value;
			Item(K val, Item* prev) : value(val), previous(prev) {}
		};

		void push(K value)
		{
			last = new Item(value, last);
			quantity++;
		}
		void pop() { Item* tmp = last->previous; delete last; last = tmp; quantity--; }
		K& top() { return last->value; }
		int size() { return quantity; }
		bool empty() { return quantity > 0 ? false : true; }
	private:
		Item* last = nullptr;
		int quantity = 0;
	};

	template<typename Y>
	class vector
	{
	public:
		vector() {}
		vector(std::initializer_list<Y> list)
		{
			int _size = list.size();
			quantity = _size;
			last_index = quantity - 1;
			_size = _size + _size / 2;
			vec_size = _size;
			Y* _list = new Y[_size];
			int k = 0;
			for (const Y* i = list.begin(); i <= list.end(); i++)
			{
				*(_list + k) = *i;
				k++;
			}
			copy = _list;
		}
		~vector() { delete[] _list; }
		vector(int lenght)
		{
			Y* _list = new Y[lenght];
		}
		void operator = (vector* right)
		{
			int l_size = sizeof(right->_list);
			this->_list = new Y[l_size] = right->_list;
		}
		Y& operator [] (int i)
		{
			i;
			return (*(copy + i));
		}

		void push_back(Y value)
		{

			quantity++;
			if (quantity > vec_size)
			{
				_list = new Y[(vec_size + 1 + (vec_size + 1) / 2)];
				for (int i = 0;i < sizeof(copy);i++)
				{
					*(_list + i) = *(copy + i);
				}
				for (int i = sizeof(copy);i < sizeof(_list);i++)
				{
					*(_list + i) = NULL;
				}
				delete[] copy;
				copy = _list;
				vec_size = sizeof(copy);
			}
			else
			{
				*(copy + last_index + 1) = value;
			}
			last_index++;
		}

		Y& front()
		{
			return *copy;
		}
		Y& back() { return *(copy + last_index); }

		int capacity() { return vec_size; }
		int size() { return quantity; }
	private:
		Y* _list;
		Y* copy;
		int quantity = 0;
		int vec_size = 0;
		int last_index = 0;
	};

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

		struct Bucket
		{
			int item_quantity = 0;
			Item* first_item;
		};

		void insert(U pre_hash, O value)
		{
			int hash_tmp = hashfunc(pre_hash);
			int tmp = abs(hash_tmp % n);
			std::cout << tmp << "\n";
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
			std::cout << tmp << "\n";
			while (until)
			{
				id_tmp = i_ptr->id;
				if (id_tmp == pre_hash)
					until = false;
				else
					i_ptr = i_ptr->next;
			}
			return i_ptr->value;
		}

		void Del(U pre_hash)
		{
			int hash_tmp = hashfunc(pre_hash);
			int tmp = abs(hash_tmp % n);
			Bucket* ptr_tmp = bucket_list + tmp;
			Item* i_ptr = (ptr_tmp->first_item);
			while (i_ptr->id != pre_hash) { i_ptr = i_ptr->next; }
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
			Bucket* tmp = bucket_list + number;
			return tmp->item_quantity;
		}

		int size() { return _size; }

		bool empty() { return _size > 0 ? false : true; }

		void rehash(int lenght)
		{
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

	private:
		int hashfunc(U id) { return std::hash<U>{}(id); }
		Bucket* bucket_list;
		int n = 16;
		int _size = 0;
	};
}
