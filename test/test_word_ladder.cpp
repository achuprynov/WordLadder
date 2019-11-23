/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#define BOOST_TEST_MODULE WordLadderTestModule
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <list>
#include <stack>

#include "word_ladder.h"

std::pair<std::string, std::string> get_begin_end_words()
{
    return std::make_pair("hit", "cog");
}

std::list<std::string> get_dictionary()
{
    return std::list<std::string>{"hit", "hot", "dot", "dog", "lot", "log", "cog"};
}

std::stack<std::string> get_result()
{
    return std::stack<std::string>({"cog", "dog", "dot", "hot", "hit"});
}

std::stack<std::string> get_result_reverted()
{
    std::stack<std::string> result;
    auto path = get_result();

    while (!path.empty())
    {
        result.push(path.top());
        path.pop();
    }

    return result;
}

BOOST_AUTO_TEST_SUITE(WordLadderTest)

BOOST_AUTO_TEST_CASE(FindPathTest)
{
    auto words = get_begin_end_words();
    auto dictionary = get_dictionary();
    auto path1 = get_result();

    auto path2 = word_ladder::find_path(words.first, words.second, dictionary);

    BOOST_TEST(path1.size() == path2.size());
    BOOST_TEST((path1 == path2));
}

BOOST_AUTO_TEST_CASE(FindPathRevertedTest)
{
    auto words = get_begin_end_words();
    auto dictionary = get_dictionary();
    auto path1 = get_result_reverted();

    auto path2 = word_ladder::find_path(words.second, words.first, dictionary);

    BOOST_TEST(path1.size() == path2.size());
    BOOST_TEST((path1 == path2));
}

BOOST_AUTO_TEST_CASE(FindPathFailedTest)
{
    auto words = get_begin_end_words();
    auto dictionary = get_dictionary();
    auto path1 = get_result();

    auto path2 = word_ladder::find_path(words.first, words.second, dictionary);
    path2.pop();

    BOOST_TEST(path1.size() != path2.size());
    BOOST_TEST((path1 != path2));
}

BOOST_AUTO_TEST_SUITE_END()
