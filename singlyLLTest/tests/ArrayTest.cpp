
#include <iostream>
#include <gtest/gtest.h>


extern "C"
{
	#include <singlyLinkedList.h>
}


using namespace std;


class singlyLinkedListArrEdgeTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
	
		singlyLinkedListArrEdgeTest() { s = newSinglyLinkedList(); }
		
		~singlyLinkedListArrEdgeTest() { freeSinglyLinkedList(&s); }

};

TEST_F(singlyLinkedListArrEdgeTest, addHeadWhenListEmpty)
{
	int val[] = {1,2,3};
	addHead(s, val);
	
	ASSERT_EQ(s->head, s->tail);//checking if the addess is same, for value,we have to derederence
	ASSERT_EQ(s->head->data, s->tail->data);//again checking for addresss match, not value
}

TEST_F(singlyLinkedListArrEdgeTest, addTailWhenListEmpty)
{
	int val[] = {1,2,3};
	addTail(s, val);
	
	ASSERT_EQ(s->head, s->tail);
	ASSERT_EQ(s->head->data, s->tail->data);
}



TEST_F(singlyLinkedListArrEdgeTest, removeHeadWhenListEmpty)
{
	ASSERT_EQ(-1, removeHead(s));
}

TEST_F(singlyLinkedListArrEdgeTest, removeTailWhenListEmpty)
{
	ASSERT_EQ(-1, removeTail(s));
}



TEST_F(singlyLinkedListArrEdgeTest, removeHeadWhenListHasOneEle)
{
	int val[] = {1,2,3};
	addHead(s, val);
	
	removeHead(s);
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListArrEdgeTest, removeTailWhenListHasOneEle)
{
	int val[] = {1,2,3};
	addTail(s, val);
	
	removeTail(s);
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}



int compareArray(const void *a, const void *b)
{
	int *c = (int*)a;
	int *d = (int*)b;
	for(int j = 0; j < 3; ++j)
		if(c[j] != d[j])
			return -1;
	return 0;
}

TEST_F(singlyLinkedListArrEdgeTest, removeDataWhenListEmpty)
{
	int val[] = {1,2,3};
	ASSERT_EQ(0, removeData(s, val, compareArray));
}


TEST_F(singlyLinkedListArrEdgeTest, removeDataWhenListHasOneMatchingEle)
{
	int val[] = {1,2,3};
	addTail(s, val);
	
	ASSERT_EQ(0, removeData(s, val, compareArray));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListArrEdgeTest, removeDataWhenListHasTwoMatchingEle)
{
	int val[][3] = { {1,2,3}, {1,2,3} };
	addTail(s, val[0]);
	addTail(s, val[1]);
	ASSERT_EQ(0, removeData(s, val[0], compareArray));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}

TEST_F(singlyLinkedListArrEdgeTest, removeDataWhenListHasAllMatchingEle)
{
	int val[][3] = {{1,2,3},{1,2,3},{1,2,3},{1,2,3},{1,2,3}};
	for(int j = 0; j < 5; ++j)
		addTail(s, val[j]);
	
	ASSERT_EQ(0, removeData(s, val[0], compareArray));
	ASSERT_EQ(NULL, s->head);
	ASSERT_EQ(NULL, s->tail);
}


class singlyLinkedListArrAddTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
		int **values;
		Iterator *i;
		
		singlyLinkedListArrAddTest()
		{
			s = newSinglyLinkedList(); 
			i = newIterator(&s);
			values = new int*[5];
			values[0] = new int[3]{1,2,3};
			values[1] = new int[3]{2,3,4};
			values[2] = new int[3]{1,2,3};
			values[3] = new int[3]{3,4,5};
			values[4] = new int[3]{1,2,3};
		}
		
		void SetUp() {}
		void TearDown() {}
		
		~singlyLinkedListArrAddTest()
		{
			freeIterator(&i);
			freeSinglyLinkedList(&s);
			for(int j = 0; j < 5; ++j)
				delete[] values[j];
			delete[] values;
		}

};

TEST_F(singlyLinkedListArrAddTest, addHeadTest)
{
	int j;
	for(j = 0; j < 5; ++j)
		addHead(s, values[j]);
	
	ASSERT_EQ(values[4], s->head->data);
	ASSERT_EQ(values[0], s->tail->data);

	for(start(i), j = 4; j >= 0; --j, next(i))
		ASSERT_EQ(values[j], data(i));
}

TEST_F(singlyLinkedListArrAddTest, addTailTest)
{
	int j;
	for(j = 0; j < 5; ++j)
		addTail(s, values[j]);
	
	ASSERT_EQ(values[0], s->head->data);
	ASSERT_EQ(values[4], s->tail->data);
	
	for(start(i), j = 0; j < 5; ++j, next(i))
		ASSERT_EQ(values[j], data(i));
}


class singlyLinkedListArrRemoveTest : public testing::Test
{	
	public:
		
		singlyLinkedList *s;
		Iterator *i;
		int **values;
		
		singlyLinkedListArrRemoveTest()
		{
			s = newSinglyLinkedList(); 
			i = newIterator(&s);
			values = new int*[5];
			values[0] = new int[3]{1,2,3};
			values[1] = new int[3]{2,3,4};
			values[2] = new int[3]{1,2,3};
			values[3] = new int[3]{3,4,5};
			values[4] = new int[3]{1,2,3};
		}
		
		void SetUp()
		{
			for(int j = 0; j < 5; ++j)
				addTail(s, values[j]);
		}
		void TearDown() {}
		
		~singlyLinkedListArrRemoveTest()
		{
			freeSinglyLinkedList(&s); 
			freeIterator(&i);
			for(int j = 0; j < 5; ++j)
				delete[] values[j];
			delete[] values;
		}

};


TEST_F(singlyLinkedListArrRemoveTest, removeHeadTest)
{
	for(int j = 0; j < 5; ++j)
	{
		ASSERT_EQ(values[j], s->head->data);
		removeHead(s);
	}
}


TEST_F(singlyLinkedListArrRemoveTest, removeTailTest)
{
	for(int j = 4; j >= 0; --j)
	{
		ASSERT_EQ(values[j], s->tail->data);
		removeTail(s);
	}
}


TEST_F(singlyLinkedListArrRemoveTest, removeDataTest)
{
	int val[] = {1,2,3};
	removeData(s, val, compareArray);
	
	start(i);//******************************very important, coz we are creating iterator first and then we are we are initializing values, so initially i->curr = NULL; so we have to use start function
	
	for(int j = 0; j < 5; ++j)
	{
		if(compareArray(values[j], val) == 0)
			continue;
		ASSERT_EQ(values[j], data(i));
		next(i);
	}
}
