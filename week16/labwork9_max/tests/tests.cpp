#include <gtest/gtest.h>
#include <lib/myadapters.h>
#include <vector>
#include <map>

TEST(adapter, transform_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (int i: v | Transform([](int i){ return i*i; })){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 4, 9, 16, 25, 36};
    ASSERT_EQ(res,ans);
}

TEST(adapter, filter_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Filter([](int i){ return i%2; })){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 3, 5};
    ASSERT_EQ(res,ans);
}

TEST(adapter, take_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Take(3)){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 2, 3};
    ASSERT_EQ(res,ans);
}

TEST(adapter, drop_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Drop(3)){
        res.push_back(i);
    }
    std::vector<int> ans = {4, 5, 6};
    ASSERT_EQ(res,ans);
}

TEST(adapter, reverse_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Reverse()){
        res.push_back(i);
    }
    std::vector<int> ans = {6, 5, 4, 3, 2, 1};
    ASSERT_EQ(res,ans);
}

TEST(adapter, keys_test){
    std::map<int, int> m = {{1,2}, {2,3}, {3,4}};
    std::vector<int> res;
    for (auto i: m | Keys()){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 2, 3};
    ASSERT_EQ(res,ans);
}

TEST(adapter, values_test){
    std::map<int, int> m = {{1,2}, {2,3}, {3,4}};
    std::vector<int> res;
    for (auto i: m | Values()){
        res.push_back(i);
    }
    std::vector<int> ans = {2, 3, 4};
    ASSERT_EQ(res,ans);
}

TEST(adapter, transform_transform_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Transform([](int i){ return i*i; }) | Transform([](int i){ return i*2; })){
        res.push_back(i);
    }
    std::vector<int> ans = {2, 8, 18, 32, 50, 72};
    ASSERT_EQ(res,ans);
}

TEST(adapter, transform_filter_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Transform([](int i){ return i*i; }) | Filter([](int i){ return i%2; })){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 9, 25};
    ASSERT_EQ(res,ans);
}

TEST(adapter, filter_filter_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6 , 7 , 8 , 9 , 10 , 11 , 12};
    std::vector<int> res;
    for (auto i: v | Filter([](int i){ return i%2 == 0; }) | Filter([](int i){ return i%4 == 0; })){
        res.push_back(i);
    }
    std::vector<int> ans = {4, 8, 12};
    ASSERT_EQ(res,ans);
}


TEST(adapter, transform_reverse_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Transform([](int i){ return i*i; }) | Reverse()){
        res.push_back(i);
    }
    std::vector<int> ans = {36, 25, 16, 9, 4, 1};
    ASSERT_EQ(res,ans);
}

TEST(adapter, transform_drop_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Transform([](int i){ return i*i; }) | Drop(3)){
        res.push_back(i);
    }
    std::vector<int> ans = {16, 25, 36};
    ASSERT_EQ(res,ans);
}



TEST(adapter, transform_values_test){
    std::map<int, int> m = {{1,2}, {2,3}, {3,4}};
    std::vector<int> res;
    for (auto i: m | Values() | Transform([](int i){ return i*i; })){
        res.push_back(i);
    }
    std::vector<int> ans = {4, 9, 16};
    ASSERT_EQ(res,ans);
}

TEST(adapter, transform_keys_test){
    std::map<int, int> m = {{1,2}, {2,3}, {3,4}};
    std::vector<int> res;
    for (auto i: m | Keys() | Transform([](int i){ return i*i; })){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 4, 9};
    ASSERT_EQ(res,ans);
}

TEST(adapter, transform_take_test){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    for (auto i: v | Transform([](int i){ return i*i; }) | Take(3)){
        res.push_back(i);
    }
    std::vector<int> ans = {1, 4, 9};
    ASSERT_EQ(res,ans);
}
