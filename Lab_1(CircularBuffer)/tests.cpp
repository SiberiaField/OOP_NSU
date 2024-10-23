#include "gtest/gtest.h"
#include "CircularBuffer.hpp"

TEST(CBTest, InitTests){
    CircularBuffer cb;
    EXPECT_TRUE(cb.empty());
    EXPECT_EQ(cb.getCapacity(), 1);
    CircularBuffer cb4(cb);
    EXPECT_TRUE(cb4.empty());
    CircularBuffer cb2(5, 1);
    EXPECT_TRUE(cb2.full());
    EXPECT_EQ(cb2.front(), 1);
    cb = cb2;
    EXPECT_EQ(cb.back(), cb.at(4));
    EXPECT_EQ(cb.getSize(), cb2.getSize());
    EXPECT_EQ(cb.back(), cb2.back());
    cb2.clear();
    EXPECT_TRUE(cb2.empty());
    EXPECT_THROW(CircularBuffer cb3(0), std::invalid_argument);
    cb.insert(4, 3);
    cb2 = cb;
    EXPECT_EQ(cb2.back(), cb.back());
}

TEST(CBTest, LinearizeTests){
    CircularBuffer cb(7);
    EXPECT_EQ(cb.getCapacity(), 7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);
    EXPECT_FALSE(cb.is_linearized());
    cb.linearize();
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_TRUE(cb.is_linearized());
}

TEST(CBTest, RotateTest){
    CircularBuffer cb(7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);
    EXPECT_EQ(cb.getSize(), 4);
    EXPECT_NO_THROW(cb.rotate(1));
    EXPECT_NO_THROW(cb.rotate(3));
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_FALSE(cb.is_linearized());
    EXPECT_THROW(cb.rotate(5), std::out_of_range);
}

TEST(CBTest, set_capacityTest){
    CircularBuffer cb(7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);
    cb.set_capacity(10);
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.at(1), 2);
    EXPECT_EQ(cb.back(), 4);
    cb.linearize();
    cb.set_capacity(3);
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.back(), 1);
    EXPECT_TRUE(cb.is_linearized());
    cb.clear();
    EXPECT_THROW(cb.set_capacity(1), std::runtime_error);
}

TEST(CBTest, resizeTest){
    CircularBuffer cb(7);
    cb.resize(4, 2);
    EXPECT_TRUE(cb.is_linearized());
    EXPECT_EQ(cb.front(), 2);
    EXPECT_EQ(cb.front(), cb.back());
    EXPECT_EQ(cb.getSize(), 4);
    cb.resize(6, 3);
    EXPECT_EQ(cb[4], 3);
    EXPECT_EQ(cb.back(), 3);
    cb.resize(2, 0);
    EXPECT_TRUE(cb.is_linearized());
    EXPECT_EQ(cb.front(), 2);
    EXPECT_EQ(cb.front(), cb.back());
    cb.clear();
    EXPECT_THROW(cb.resize(2, 0), std::runtime_error);
}

TEST(CBTest, swapTest){
    CircularBuffer cb(7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);
    CircularBuffer cb1(5, 4);
    cb.swap(cb1);
    EXPECT_EQ(cb.getCapacity(), 5);
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb.front(), 4);
    EXPECT_EQ(cb.front(), cb.back());
    EXPECT_TRUE(cb.is_linearized());
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.front(), 3);
    EXPECT_EQ(cb1.at(1), 2);
    EXPECT_EQ(cb1.back(), 4);
}

TEST(CBTest, removingTest){
    CircularBuffer cb(7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);

    cb.pop_back();
    cb.pop_back();
    EXPECT_EQ(cb.back(), 2);
    cb.pop_front();
    EXPECT_EQ(cb.front(), cb.back());

    CircularBuffer cb1(6, 2);
    cb1.insert(2, 4);
    cb1.erase(0, 2);
    EXPECT_EQ(cb1.front(), 4);
    EXPECT_EQ(cb1.getSize(), 4);
    cb1.insert(1, 5);
    cb1.erase(2, 4);
    EXPECT_EQ(cb1.back(), 5);
    cb1.push_back(6);
    cb1.push_back(7);
    cb1.erase(1, 3);
    EXPECT_EQ(cb1.front(), 4);
    EXPECT_EQ(cb1.back(), 7);

    cb1.push_front(3);
    EXPECT_EQ(cb1[0], 3);
    EXPECT_EQ(cb1[1], 4);
    EXPECT_EQ(cb1[2], 7);
    EXPECT_THROW(cb1.erase(0, 6), std::out_of_range);
}

TEST(CBTest, IndexTests){
    CircularBuffer cb(6, 2);
    EXPECT_NO_THROW(cb[8]);
    EXPECT_ANY_THROW(cb.at(8));
    cb.insert(4, 7);
    EXPECT_EQ(cb[4], cb.at(4));
    CircularBuffer cb2(3);
    cb2.push_back(1);
    cb2.push_front(2);
    cb2.push_back(3);
    EXPECT_EQ(cb2[1], 1);
    EXPECT_EQ(cb2.at(2), 3);
}