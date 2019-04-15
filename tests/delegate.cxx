#include <gtest/gtest.h>
#include <mpp/delegate.hpp>

bool entered = false;
bool entered_second = false;

void call(int a)
{
    entered = true;
}

void call_second(int a)
{
    entered_second = true;
}

TEST (delegate, callable)
{
    mpp::delegate<int> callable;
    callable.connect(call).discard();
    callable(100);
    ASSERT_EQ(true, entered);
    entered = false;
}

TEST (delegate, multiple)
{
    mpp::delegate<int> callable;
    callable.connect(call).discard();
    callable.connect(call_second).discard();
    callable(100);
    ASSERT_EQ(true, entered);
    ASSERT_EQ(true, entered_second);
    entered = entered_second = false;
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
