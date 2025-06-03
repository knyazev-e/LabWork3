#include <gtest/gtest.h>
#include "circular_list.h"
#include <vector>

TEST(CircularLinkedListTest, DefaultConstructor) {
    CircularLinkedList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CircularLinkedListTest, PushFront) {
    CircularLinkedList<int> list;
    list.push_front(3);
    EXPECT_EQ(list.front(), 3);
    list.push_front(2);
    EXPECT_EQ(list.front(), 2);
}

TEST(CircularLinkedListTest, PopFront) {
    CircularLinkedList<int> list;
    list.push_front(1);
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(CircularLinkedListTest, Iterator) {
    CircularLinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    std::vector<int> results;
    for (auto it = list.begin(); it != list.end(); ++it) {
        results.push_back(*it);
    }
    EXPECT_EQ(results, std::vector<int>({1, 2, 3}));
}

TEST(CircularLinkedListTest, ConstIterator) {
    CircularLinkedList<int> list;
    list.push_front(1);
    const auto& const_list = list;
    EXPECT_EQ(*const_list.begin(), 1);
}

TEST(CircularLinkedListTest, InsertAfter) {
    CircularLinkedList<int> list;
    list.push_front(1);
    auto it = list.insert_after(list.begin(), 2);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(list.size(), 2);
}

TEST(CircularLinkedListTest, EraseAfter) {
    CircularLinkedList<int> list;
    list.push_front(1);
    list.insert_after(list.begin(), 2);
    list.erase_after(list.begin());
    EXPECT_EQ(list.size(), 1);
}

TEST(CircularLinkedListTest, Clear) {
    CircularLinkedList<int> list;
    list.push_front(1);
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST(CircularLinkedListTest, CopyConstructor) {
    CircularLinkedList<int> list1;
    list1.push_front(1);
    CircularLinkedList<int> list2 = list1;
    EXPECT_EQ(list2.front(), 1);
}

TEST(CircularLinkedListTest, Equality) {
    CircularLinkedList<int> list1, list2;
    list1.push_front(1);
    list2.push_front(1);
    EXPECT_TRUE(list1 == list2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
