/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#include <iostream>
#include <string>

#include "word_ladder.h"

void print_path(std::stack<std::string> & path)
{
    while (!path.empty())
    {
        std::cout << path.top() << std::endl;
        path.pop();
    }
}

void print_usage(const char * appName)
{
    std::cout << "usage: " << appName << " <begin word> <end word> <dictionary words>" << std::endl;
}

int main(int argc, char** argv)
{
    try
    {
        if (argc < 3)
        {
            print_usage(argv[0]);
            return 1;
        }

        std::list<std::string> dictionary;

        auto begin_word = argv[1];
        auto   end_word = argv[2];
        
        // path betwen words may be empty, i.e. "dot" -> "dog"
        dictionary.push_back(begin_word);
        dictionary.push_back(  end_word);

        for (auto i = 3; i < argc; i++)
        {
            dictionary.push_back(argv[i]);
        }

        auto path = word_ladder::find_path(begin_word, end_word, dictionary);

        if (path.size() > 0)
        {
            print_path(path);
        }
        else
        {
            std::cout << "path not found" << std::endl;
        }
    }
    catch (std::exception & ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
