/*
MIT License

Copyright (c) 2023 Michele Maione

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <iostream>
#include <memory>
#include "data-structure/node.h"

int main() {
    // costructor
    const auto t = std::make_shared<node<int> >(50);

    // editing
    t->insert(10);
    t->insert(80);
    t->insert(90);
    t->insert(5);
    t->insert(75);
    t->insert(2);
    t->insert(11);

    // printing
    auto print = [](const int n) { std::cout << n << ' '; };

    std::cout << "Pre Order:" << std::endl;
    t->pre_order(print);
    std::cout << std::endl;

    std::cout << "In Order:" << std::endl;
    t->in_order(print);
    std::cout << std::endl;

    std::cout << "Post Order:" << std::endl;
    t->post_order(print);
    std::cout << std::endl;

    // searching
    const auto minimum = t->minimum();
    std::cout << "Mimum: " << minimum->value() << std::endl;

    const auto maximum = t->maximum();
    std::cout << "Maximum: " << maximum->value() << std::endl;

    std::cout << "Search for: 5 (that is present)" << std::endl;
    if (const auto n5 = t->search(5))
        std::cout << "Found!" << std::endl;
    else
        std::cout << "Not found!" << std::endl;

    std::cout << "Search for: 15 (that is not present)" << std::endl;
    if (const auto n15 = t->search(15))
        std::cout << "Found!" << std::endl;
    else
        std::cout << "Not found!" << std::endl;
}
