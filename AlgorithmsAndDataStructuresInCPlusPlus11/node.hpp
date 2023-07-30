/*
MIT License

Copyright (c) 2023 Michele Maione

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef NODE_HPP
#define NODE_HPP

#include <functional>
#include <memory>
#include "node.h"


// costructor
template<typename T>
node<T>::node(const T z) :v(z) {}


// editing
template<typename T>
inline void node<T>::insert(T z)
{
	if (z < v)
	{
		if (l)
			l->insert(z);
		else
			l = std::make_shared<node>(z);
	}
	else
	{
		if (r)
			r->insert(z);
		else
			r = std::make_shared<node>(z);
	}
}


// searching
template<typename T>
std::shared_ptr<node<T>> node<T>::search(T z)
{
	if (v == z)
		return this->shared_from_this();
	else if (l && z < v)
		return l->search(z);
	else if (r && z >= v)
		return r->search(z);
	else
		return nullptr;
}


// printing
template<typename T>
void node<T>::pre_order(std::function<void(T)> printFn)
{
	printFn(v);

	if (l)
		l->in_order(printFn);

	if (r)
		r->in_order(printFn);
}

template<typename T>
void node<T>::in_order(std::function<void(T)> printFn)
{
	if (l)
		l->in_order(printFn);

	printFn(v);

	if (r)
		r->in_order(printFn);
}

template<typename T>
inline void node<T>::post_order(std::function<void(T)> printFn)
{
	if (l)
		l->in_order(printFn);

	if (r)
		r->in_order(printFn);

	printFn(v);
}

#endif