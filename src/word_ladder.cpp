/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#include <queue>
#include <map>

#include "word_ladder.h"

namespace word_ladder
{
    std::map<std::string, std::string> build_graph(const std::string&, const std::string&, std::list<std::string>&);
    std::stack<std::string> build_path(const std::string&, const std::string&, std::map<std::string, std::string>&);
    bool is_edge(const std::string&, const std::string&);

    std::stack<std::string> find_path(
        const std::string& begin_word, 
        const std::string& end_word, 
        std::list<std::string>& dictionary)
    {
        auto graph = build_graph(begin_word, end_word, dictionary);

        auto path = build_path(begin_word, end_word, graph);

        return path;
    }

    std::map<std::string, std::string> build_graph(
        const std::string& begin_word, 
        const std::string& end_word, 
        std::list<std::string>& dictionary)
    {
        std::map<std::string, std::string> graph;
        std::queue<std::string> nodes;

        nodes.push(begin_word);
        dictionary.push_front(end_word);

        while (!nodes.empty())
        {
            auto node = nodes.front();
            nodes.pop();
            auto word = dictionary.begin();

            while (word != dictionary.end())
            {
                if (is_edge(*word, node))
                {
                    graph.insert(std::make_pair(*word, node));

                    if (*word == end_word)
                    {
                        return graph;
                    }

                    nodes.push(*word);

                    word = dictionary.erase(word);
                }
                else if (*word == node)
                {
                    // remove duplicates
                    word = dictionary.erase(word);
                }
                else
                {
                    word++;
                }
            }
        }

        graph.clear();
        return graph;
    }

    bool is_edge(const std::string& word1, const std::string& word2)
    {
        if (word1.size() != word2.size())
            return false;

        auto iter1 = word1.begin();
        auto iter2 = word2.begin();
        auto counter_diffrent_chars = 0;

        while (iter1 != word1.end() 
            && iter2 != word2.end() 
            && counter_diffrent_chars < 2)
        {
            if (*iter1++ != *iter2++)
            {
                counter_diffrent_chars++;
            }
        }

        return counter_diffrent_chars == 1;
    }

    std::stack<std::string> build_path(
        const std::string& begin_word, 
        const std::string& end_word, 
        std::map<std::string, std::string>& graph)
    {
        std::stack<std::string> path;

        if (!graph.empty())
        {
            auto word = end_word;
            while (true)
            {
                path.push(word);

                if (word == begin_word)
                    break;

                word = graph[word];
            }
        }

        return path;
    }
}
