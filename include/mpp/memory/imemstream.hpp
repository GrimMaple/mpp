/* - memory/imemstream.hpp ------------------------------------------------------------------------
* Input Memory Stream
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_MEMORY_IMEMSTREAM_
#define _MPP_MEMORY_IMEMSTREAM_

#include <vector>

namespace mpp
{

class imemstream
{
public:
	imemstream() : bytes()
	{

	}

	template<typename T>
	imemstream &operator<<(T val)
	{
		for (int i = 0; i < sizeof(T); i++)
			bytes.push_back(((char*)(&val))[i]);

		return *this;
	}

	template<typename T>
	imemstream &operator<<(T* val)
	{
		char* data = static_cast<char*>(val);
		for (int i = 0; i < sizeof(T); i++)
			bytes.push_back(data[i]);

		return *this;
	}

	template<typename T>
	imemstream &operator<<(std::vector<T> val)
	{
		for(auto i : val)
			*this << i;
	       return *this;	
	}

	std::vector<char> get()
	{
		return bytes;
	}

private:
	std::vector<char> bytes;
};

}

#endif
