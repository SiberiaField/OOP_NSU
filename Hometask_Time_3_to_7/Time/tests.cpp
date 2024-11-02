#include "gtest/gtest.h"
#include "Time.hpp"
#include <iostream>

TEST(constructorTests, constructorExcept){
    EXPECT_THROW(Time t(-10, 22, 22), std::invalid_argument);
    EXPECT_NO_THROW(Time t1(12, 40, 0));
}

TEST(constructorTests, normalize){
    Time t(22, -10, -122);
    EXPECT_EQ(t.GetHours(), 21);
    EXPECT_EQ(t.GetMinutes(), 47);
    EXPECT_EQ(t.GetSeconds(), 58);
}

TEST(constructorTests, copyConstructor){
    Time t(21, 55, 40);
    Time t1(t);
    EXPECT_TRUE(t1 == t);
    Time t2(Time(11, 61, 22));
    Time t3(12, 1, 22);
    EXPECT_TRUE(t2 == t3);
}

TEST(funcTests, toSeconds){
    Time t(21, 47, 58);
    EXPECT_EQ(t.toSeconds(), 78478);
    Time t1(23, 59, 59);
    EXPECT_EQ(t1.toSeconds(), 86399);
    Time t2;
    EXPECT_EQ(t2.toSeconds(), 123);
}

TEST(operatorsTests, plusEq){
    Time t(21, 47, 58);
    t += 10;
    Time t2(21, 48, 8);
    EXPECT_TRUE(t == t2);
    t += -112;
    Time t3(21, 46, 16);
    EXPECT_TRUE(t == t3);
    t += 180;
    Time t4(21, 49, 16);
    EXPECT_FALSE(t == t4);
}

TEST(operatorsTests, minusEq){
    Time t(21, 48, 8);
    t -= 120;
    Time t1(21, 46, 8);
    EXPECT_TRUE(t == t1);
    t -= -67;
    Time t2(21, 47, 15);
    EXPECT_TRUE(t == t2);
}

TEST(operatorsTests, subtraction){
    Time t(21, 48, 8);
    EXPECT_EQ(t - 256, 78232);
    EXPECT_EQ(t - (-256), 78744);
    EXPECT_EQ(t - t.toSeconds(), 0);
}

TEST(operatorsTests, eq){
    Time t1;
    t1 = Time(21, 77, 8);
    EXPECT_TRUE(t1 == Time(22, 17, 8));
    t1 = Time();
    EXPECT_EQ(t1.toSeconds(), 0);
}
