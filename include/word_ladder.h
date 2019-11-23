/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#pragma once

#include <list>
#include <stack>
#include <string>

namespace word_ladder
{  
    std::stack<std::string> find_path(
        const std::string& begin_word, 
        const std::string& end_word, 
        std::list<std::string>& dictionary);
}
