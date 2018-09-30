/* - memory/omemstream.hpp ------------------------------------------------------------------------
* Output Memory Stream
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#include <memory>

namespace mpp
{

class omemstream
{
public:
	omemstream(char* data, size_t sz)
		: size(sz),
		data(data),
		pos(0)
	{

	}

	template<typename T>
	omemstream &operator>> (omemstream& stream, T& val)
	{
		val = reinterpret_cast<T>(data + pos);
		pos += sizeof(T);
	}

	template<typename T>
	omemstream operator>> (omemstream& stream, T* val)
	{
		std::memcpy(val, data + pos, sizeof(T));
		pos += sizeof(T);
	}

private:
	size_t size;
	size_t pos;
	char* data;
};

}