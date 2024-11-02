#include "gtest/gtest.h"
#include "CircularBuffer.hpp"

TEST(constructorsTests, defaultConstructor){
    CircularBuffer cb;
    EXPECT_TRUE(cb.empty());
    EXPECT_EQ(cb.getCapacity(), 1);
}

TEST(constructorsTests, constructorCap){
    EXPECT_NO_THROW(CircularBuffer cb(4));
    EXPECT_THROW(CircularBuffer cb(0), std::invalid_argument);
}

TEST(constructorsTests, copyConstructor){
    CircularBuffer cb;
    CircularBuffer cb1(cb);
    EXPECT_TRUE(cb1.empty());
    EXPECT_EQ(cb1.getCapacity(), 1);

    cb.clear();
    CircularBuffer cb2(cb);
    EXPECT_ANY_THROW(cb2.set_capacity(2));

    CircularBuffer cb3(5, 3);
    CircularBuffer cb4(cb3);
    for(int i = 0; i < cb4.getCapacity(); i++){
        EXPECT_TRUE(cb4[i] == cb3[i]);
    }

    CircularBuffer cb5(7);
    cb5.push_back(1);
    cb5.push_front(2);
    cb5.push_front(3);
    cb5.push_back(4);
    CircularBuffer cb6(cb5);
    for(int i = 0; i < cb6.getCapacity(); i++){
        EXPECT_TRUE(cb6[i] == cb5[i]);
    }
}

TEST(constructorsTests, constructorFillCap){
    CircularBuffer cb(5, 1);
    for(int i = 0; i < cb.getCapacity(); i++){
        EXPECT_EQ(cb[i], 1);
    }
    EXPECT_TRUE(cb.full());
    EXPECT_TRUE(cb.is_linearized());
    EXPECT_THROW(CircularBuffer cb1(-1, 5), std::invalid_argument);
}

TEST(funcTests, linearize){
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

TEST(funcTests, rotate){
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

TEST(funcTests, set_capacity){
    CircularBuffer cb(7);
    cb.push_back(1);
    cb.push_front(2);
    cb.push_front(3);
    cb.push_back(4);
    cb.set_capacity(10);
    EXPECT_THROW(cb.set_capacity(0), std::invalid_argument);
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

TEST(funcTests, resize){
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

TEST(funcTests, swap){
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

TEST(removingTests, pop){
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
    EXPECT_EQ(cb.front(), 2);
}

TEST(removingTests, erase){
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

TEST(indexingTests, usual){
    CircularBuffer cb(6, 2);
    EXPECT_NO_THROW(cb[8]);
    cb.insert(4, 7);
    EXPECT_EQ(cb[4], 7);
    CircularBuffer cb2(3);
    cb2.push_back(1);
    cb2.push_front(2);
    cb2.push_back(3);
    EXPECT_EQ(cb2[1], 1);
}

TEST(indexingTests, at){
    CircularBuffer cb(6, 2);
    EXPECT_THROW(cb.at(8), std::out_of_range);
    CircularBuffer cb1(3);
    cb1.push_back(1);
    cb1.push_front(2);
    cb1.push_back(3);
    EXPECT_EQ(cb1.at(2), 3);
    cb1.clear();
    EXPECT_THROW(cb1.at(0), std::runtime_error);
}