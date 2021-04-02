#include <iostream>
#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>

extern "C"
{
	#include <singlyLinkedList.h>
}


using namespace std;


class singlyLinkedListEdgeTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
	
		singlyLinkedListEdgeTest() { s = newSinglyLinkedList(); }
		
		~singlyLinkedListEdgeTest() { freeSinglyLinkedList(&s); }

};

TEST_F(singlyLinkedListEdgeTest, addHeadWhenListEmpty)
{
	int val = 5;
	addHead(s, &val);
	
	ASSERT_EQ(s->head, s->tail);//checking if the addess is same, for value,we have to derederence
	ASSERT_EQ(s->head->data, s->tail->data);//again checking for addresss match, not value
}

TEST_F(singlyLinkedListEdgeTest, addTailWhenListEmpty)
{
	int val = 5;
	addTail(s, &val);
	
	ASSERT_EQ(s->head, s->tail);
	ASSERT_EQ(s->head->data, s->tail->data);
}



TEST_F(singlyLinkedListEdgeTest, removeHeadWhenListEmpty)
{
	ASSERT_EQ(-1, removeHead(s));
}

TEST_F(singlyLinkedListEdgeTest, removeTailWhenListEmpty)
{
	ASSERT_EQ(-1, removeTail(s));
}



TEST_F(singlyLinkedListEdgeTest, removeHeadWhenListHasOneEle)
{
	int val = 5;
	addHead(s, &val);
	
	removeHead(s);
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListEdgeTest, removeTailWhenListHasOneEle)
{
	int val = 5;
	addTail(s, &val);
	
	removeTail(s);
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}



int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

TEST_F(singlyLinkedListEdgeTest, removeDataWhenListEmpty)
{
	int val = 5;
	ASSERT_EQ(0, removeData(s, &val, compare));
}


TEST_F(singlyLinkedListEdgeTest, removeDataWhenListHasOneMatchingEle)
{
	int val = 5;
	addTail(s, &val);
	
	ASSERT_EQ(0, removeData(s, &val, compare));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListEdgeTest, removeDataWhenListHasTwoMatchingEle)
{
	int val1 = 5, val2 = 5;
	addTail(s, &val1);
	addTail(s, &val2);
	ASSERT_EQ(0, removeData(s, &val1, compare));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListEdgeTest, removeDataWhenListHasAllMatchingEle)
{
	int val[5] = {5,5,5,5,5};
	for(int j = 0; j < 5; ++j)
		addTail(s, &val[j]);
	
	ASSERT_EQ(0, removeData(s, &val[0], compare));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

class singlyLinkedListAddTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
		int *values;
		int size;
		Iterator *i;
		
		singlyLinkedListAddTest()
		{
			s = newSinglyLinkedList(); 
			i = newIterator(&s);
			
			srand(time(0));
			size = rand() % 100 + 1;//+1 so that, size is never zero
			values = new int[size];
		}
		
		void SetUp() 
		{
			for(int j = 0; j < size; ++j)
				values[j] = rand();
		}
		void TearDown() {}
		
		~singlyLinkedListAddTest()
		{
			freeIterator(&i);
			freeSinglyLinkedList(&s); 
			delete[] values;
		}

};

TEST_F(singlyLinkedListAddTest, addHeadTest)
{
	int j;
	for(j = 0; j < size; ++j)
		addHead(s, &values[j]);
	
	ASSERT_EQ(&values[size-1], s->head->data);
	ASSERT_EQ(&values[0], s->tail->data);

	for(start(i), j = size-1; j >= 0; --j, next(i))
		ASSERT_EQ(&values[j], data(i));
}

TEST_F(singlyLinkedListAddTest, addTailTest)
{
	int j;
	for(j = 0; j < size; ++j)
		addTail(s, &values[j]);
	
	ASSERT_EQ(&values[0], s->head->data);
	ASSERT_EQ(&values[size-1], s->tail->data);
	
	for(start(i), j = 0; j < size; ++j, next(i))
		ASSERT_EQ(&values[j], data(i));
}


class singlyLinkedListRemoveTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
		Iterator *i;
		int *values;
		int size;
		
		singlyLinkedListRemoveTest()
		{
			s = newSinglyLinkedList(); 
			i = newIterator(&s);
			
			srand(time(0));
			size = rand() % 100 + 1;//+1 so that, size is never zero
			values = new int[size];
		}
		
		void SetUp()
		{
			for(int j = 0; j < size; ++j)
				values[j] = rand();
			
			for(int j = 0; j < size; ++j)
				addTail(s, &values[j]);
		}
		void TearDown() {}
		
		~singlyLinkedListRemoveTest()
		{
			freeSinglyLinkedList(&s); 
			freeIterator(&i);
			delete[] values;
		}

};


TEST_F(singlyLinkedListRemoveTest, removeHeadTest)
{
	for(int j = 0; j < size; ++j)
	{
		ASSERT_EQ(&values[j], s->head->data);
		removeHead(s);
	}
}


TEST_F(singlyLinkedListRemoveTest, removeTailTest)
{
	for(int j = size-1; j >= 0; --j)
	{
		ASSERT_EQ(&values[j], s->tail->data);
		removeTail(s);
	}
}


TEST_F(singlyLinkedListRemoveTest, removeDataTest)
{
	int val = rand();
	removeData(s, &val, compare);
	
	start(i);//******************************very important, coz we are creating iterator first and then we are we are initializing values, so initially i->curr = NULL; so we have to use start function
	
	for(int j = 0; j < size; ++j)
	{
		if(values[j] == val)
			continue;
		ASSERT_EQ(&values[j], data(i));
		next(i);
	}
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
