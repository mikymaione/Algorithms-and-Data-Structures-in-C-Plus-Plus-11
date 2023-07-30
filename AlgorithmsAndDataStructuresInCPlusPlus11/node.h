/*
MIT License

Copyright (c) 2023 Michele Maione

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef NODE_H
#define NODE_H

#include <functional>
#include <memory>

template <typename T>
class node : public std::enable_shared_from_this<node<T>>
{
private:
	T v;
	std::shared_ptr<node<T>> l {nullptr};
	std::shared_ptr<node<T>> r {nullptr};

public:
	// costructor
	node(const T z);

	// editing
	void insert(T z);

	// searching
	std::shared_ptr<node<T>> search(T z);

	// printing
	void pre_order(std::function<void(T)> printFn);

	void in_order(std::function<void(T)> printFn);

	void post_order(std::function<void(T)> printFn);
};

#include "node.hpp"

#endif