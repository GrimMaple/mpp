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
#include <cstring>

namespace mpp
{

class omemstream
{
public:
	omemstream(uint8_t* data, size_t sz)
		: size(sz),
		data(data),
		pos(0)
	{

	}

	template<typename T>
	omemstream &operator>> (T& val)
	{
		val = *((T*)(data + pos));
		pos += sizeof(T);

		return *this;
	}

	template<typename T>
	omemstream operator>> (T* val)
	{
		std::memcpy(val, data + pos, sizeof(T));
		pos += sizeof(T);

		return *this;
	}

private:
	size_t size;
	size_t pos;
	uint8_t* data;
};

}
