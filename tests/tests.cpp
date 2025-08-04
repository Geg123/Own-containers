#include <gtest/gtest.h>
#include "../src/geg/Containers.h"

geg::vector<int> _vector{ 1,2,9,5,94 };
geg::list<std::string> _list = {"123","dfk"};
geg::queue<char> _queue;
geg::queue<char> _queue2;
geg::hash_table<std::string,int> _htable;
geg::stack<int> _stack;
geg::stack<int> _stack2;

bool front_bool = false;
bool back_bool = false;
bool size_bool = false;
short res = 0;
bool push_back_bool = false;
bool push_front_bool = false;
bool queue_size = false;
bool queue_add = false;
bool queue_first = false;
bool queue_last = false;


TEST(Vector, back) {
	ASSERT_TRUE( _vector.back() == 94);
}

TEST(Vector, front) {
	ASSERT_TRUE(_vector.front() == 1);
}

TEST(Vector, index_operator) {
	ASSERT_TRUE(_vector[2] == 9);
}

TEST(Vector, push_back) {
	if (_vector[2] == 9)
	{
		_vector.push_back(312);
		ASSERT_TRUE(_vector[5] == 312);
	}
	else
		FAIL() << "Push_back hasn't tested, because operator[] doesn't working";
}

TEST(Vector, size) {
	ASSERT_TRUE(_vector.size() == 6);
}

TEST(Vector, empty) {
	ASSERT_FALSE(_vector.empty());
}



TEST(Queue, size) {
	ASSERT_TRUE(_queue.size() == 0);
	if (_queue.size() == 0)
		queue_size = true;
}

TEST(Queue, add) {
	if (queue_size) {
		_queue.add('r');
		_queue.add('u');
		ASSERT_TRUE(_queue.size() == 2);
	}
}

TEST(Queue, first) {
	if (queue_add) {
		ASSERT_TRUE(_queue.first() == 'r');
		if (_queue.first() == 'r') { queue_first = true; }
	}
}

TEST(Queue, last) {
	if (queue_add) {
		ASSERT_TRUE(_queue.last() == 'u');
		if (_queue.last() == 'u') { queue_last = true; }
	}
}

TEST(Queue, empty) {
	ASSERT_FALSE(_queue.empty());
}

TEST(Queue, swap) {
	if (queue_add && queue_first && queue_last)
	{
		_queue.swap(_queue2);
		if (_queue2.first() == 'r')
			++res;
		if (_queue2.last() == 'u')
			++res;
		if (_queue2.size() == 2)
			++res;
		if (_queue.size() == 0)
			++res;

		if (res == 4)
			SUCCEED();
		else
			FAIL();
		res = 0;
	}
}

TEST(Queue, del) {
	if (queue_add && queue_first && queue_size) {
		_queue2.del();

		if (_queue2.first() == 'u')
			++res;
		if (_queue2.size() == 1)
			++res;

		if (res == 2)
			SUCCEED();
		else
			FAIL();
		res = 0;
	}
}




TEST(hash_table, insert_and_out) {
	_htable.insert("wasd",123);
	_htable.insert("oval", 9083);
	ASSERT_TRUE(_htable.out("wasd") == 123);
	ASSERT_TRUE(_htable.out("oval") == 9083);
}

TEST(hash_table, size) {
	ASSERT_TRUE(_htable.size() == 2);
}

TEST(hash_table, del) {
	if (_htable.size() == 2) 
	{
		_htable.del("wasd");
		ASSERT_TRUE(_htable.size() == 1);
	}
}

TEST(hash_table, bucket_count) {
	ASSERT_TRUE(_htable.bucket_count() == 16);
}

TEST(hash_table, rehash) {
	if (_htable.bucket_count() == 16 && _htable.out("oval") == 9083)
	{
		_htable.rehash(10);
		ASSERT_TRUE(_htable.bucket_count() == 10 && _htable.out("oval") == 9083);
	}
}

TEST(hash_table, empty) {
	ASSERT_FALSE(_htable.empty());
}



TEST(List, size) {
	ASSERT_TRUE(_list.size() == 2);
	if (_list.size() == 2)
		size_bool = true;
}
TEST(List, back) {
	ASSERT_TRUE(_list.back() == "dfk");
	if (_list.back() == "dfk")
		back_bool = true;
}

TEST(List, front) {
	ASSERT_TRUE(_list.front() == "123");
	if (_list.front() == "123")
		front_bool = true;
}

TEST(List, push_back) {
	if (_list.back() == "dfk")
	{
		_list.push_back("hello world");
		ASSERT_TRUE(_list.back() == "hello world");
		if(_list.back() == "hello world")
			push_back_bool = true;
	}
	else
		FAIL() << "Push_back hasn't tested, because back() doesn't working";
}

TEST(List, push_front) {
	if (_list.front() == "123")
	{
		_list.push_front("night");
		ASSERT_TRUE(_list.front() == "night");
		if(_list.front() == "night")
			push_front_bool = true;
	}
	else
	{
		//std::cout << "Push_front hasn't tested,because front() doesn't working" << "\n";
		FAIL() << "Push_front hasn't tested, because front() doesn't working";
	}
}

TEST(List, assign1) {

	_list.assign(10, "2107");
	
	if (front_bool = true && _list.front() == "2107")
		res++;
	if (back_bool = true && _list.back() == "2107")
		res++;
	if (size_bool = true && _list.size() == 10)
		res++;

	if (res == 3)
		SUCCEED();
	else
		FAIL();
}

TEST(List, assign2) {
	res = 0;

	_list.assign({"1","2","3","4"});

	if (front_bool = true && _list.front() == "1")
		res++;
	if (back_bool = true && _list.back() == "4")
		res++;
	if (size_bool = true && _list.size() == 4)
		res++;
	if (res == 3)
		SUCCEED();
	else
		FAIL();
}

TEST(List, assign3) {
	res = 0;

	_list.assign(++_list.begin(),--(_list.end()));

	if (front_bool = true && _list.front() == "2")
		res++;
	if (back_bool = true && _list.back() == "3")
		res++;
	if (size_bool = true && _list.size() == 2)
		res++;

	if (res == 3)
		SUCCEED();
	else
		FAIL();
}
TEST(List, pop_back) {
	res = 0;

	_list.pop_back();

	if (back_bool == true &&_list.back() == "2")
		res++;
	if (size_bool == true && _list.size() == 1)
		res++;
	if (res == 2)
		SUCCEED();
	else
		FAIL();
}

TEST(List, pop_front) {
	res = 0;
	_list.pop_front();

	if (size_bool == true && _list.size() == 0)
		res++;
	if (res == 1)
		SUCCEED();
	else
		FAIL();
}

TEST(List, clear) {
	if (push_back_bool && size_bool)
	{
		_list.push_back("qwe");
		_list.push_back("9ef8ujd");
		_list.clear();
		ASSERT_TRUE(_list.size() == 0);
	}
}

TEST(Stack, size) {
	ASSERT_TRUE(_stack.size() == 0);
}

TEST(Stack, push_and_top) {
	_stack.push(456);
	ASSERT_TRUE(_stack.top() == 456 && _stack.size() == 1);
}

TEST(Stack, empty) {
	ASSERT_TRUE(_stack.empty());
}

TEST(Stack, pop) {
	if(_stack.size() == 1)
	{
		_stack.pop();
		ASSERT_TRUE(_stack.size() == 0);
	}
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}