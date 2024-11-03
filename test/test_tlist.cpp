#include "tlist.h"

#include <gtest.h>

TEST(TList, can_create_list)
{
  ASSERT_NO_THROW(TList<int> l);
}

TEST(TList, can_create_list_with_positive_length)
{
	ASSERT_NO_THROW(TList<int> l(3));
}

TEST(TList, cant_create_list_with_negative_length)
{
	ASSERT_ANY_THROW(TList<int> l(-1));
}

TEST(TList, can_create_copied_list)
{
	TList<int> l1(3);
	ASSERT_NO_THROW(TList<int> l(l1));
}

TEST(TList, can_get_size)
{
	TList<int> l1(3);
	EXPECT_EQ(3, l1.size());
}

TEST(TList, can_set_and_get_node)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	i = 0;
	for (TList<int>::iterator it1 = l1.begin(); it1 != l1.end(); ++it1) {
		EXPECT_EQ(l1.at(it1), i++);
	}
}

TEST(TList, copied_list_is_equal_to_source_one)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	TList<int> l2(l1);
	EXPECT_EQ(l1.size(), l2.size());
	for (TList<int>::iterator it1 = l1.begin(), it2 = l2.begin(); it1 != l1.end() && it2 != l2.end(); ++it1, ++it2) {
		EXPECT_EQ(l1.at(it1), l2.at(it2));
	}

}

TEST(TList, copied_list_has_its_own_memory)
{
	TList<int> l1(3);
	TList<int> l2(l1);
	EXPECT_NE(l1.begin(), l2.begin());
}

TEST(TList, can_assign_list_to_itself)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l1 = l1;
	EXPECT_EQ(l1.size(), 3);
	i = 0;
	for (TList<int>::iterator it1 = l1.begin(); it1 != l1.end(); ++it1) {
		EXPECT_EQ(l1.at(it1), i++);
	}
}

TEST(TList, can_assign_lists)
{
	TList<int> l1(3), l2(4);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = l1;
	EXPECT_EQ(l2.size(), 3);
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(l2.at(it2), i++);
	}
}

TEST(TList, can_create_list_using_move_semantic)
{
	TList<int> l1(3);
	ASSERT_NO_THROW(TList<int> l2(std::move(l1)));
}

TEST(TList, list_is_equal_to_copymoved_one)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	TList<int> l2(std::move(l1));
	EXPECT_EQ(3, l2.size());
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(i++, l2.at(it2));
	}

}

TEST(TList, copymoved_list_is_deleted)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	TList<int> l2(std::move(l1));
	EXPECT_EQ(0, l1.size());
	EXPECT_EQ(l1.begin(), l1.end());

}

TEST(TList, can_move_list)
{
	TList<int> l1(3), l2;
	ASSERT_NO_THROW(l2 = std::move(l1));
}

TEST(TList, list_is_equal_to_moved_one)
{
	TList<int> l1(3), l2;
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = std::move(l1);
	EXPECT_EQ(3, l2.size());
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(i++, l2.at(it2));
	}

}

TEST(TList, moved_list_is_deleted)
{
	TList<int> l1(3), l2;
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = std::move(l1);
	EXPECT_EQ(0, l1.size());
	EXPECT_EQ(l1.begin(), l1.end());

}

TEST(TList, can_insert_front_element)
{
	TList<int> l;
	l.insert_front(3);
	EXPECT_EQ(l.at(l.begin()), 3);
}

TEST(TList, can_insert_element)
{
	TList<int> l;
	l.insert_front(3);
	TList<int>::iterator it = l.begin();
	l.insert_after(2, it);
	EXPECT_EQ(l.at(++it), 2);
}

TEST(TList, can_erase_front_element)
{
	TList<int> l;
	l.insert_front(3);
	TList<int>::iterator it = l.begin();
	l.insert_after(2, it);
	l.erase_front();
	EXPECT_EQ(l.at(l.begin()), 2);
}

TEST(TList, can_erase_element)
{
	TList<int> l;
	l.insert_front(3);
	TList<int>::iterator it = l.begin();
	it = l.insert_after(2, it);
	l.insert_after(4, it);
	l.erase_after(l.begin());
	EXPECT_EQ(l.at(++l.begin()), 4);
}