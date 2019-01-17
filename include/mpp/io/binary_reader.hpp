/* - io/binary_reader.hpp -------------------------------------------------------------------------
* Binary File Reader. Provides a better alternative for std::ifstream 
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_BINARY_READER_
#define _MPP_IO_BINARY_READER_

#include "file_stream.hpp"

namespace mpp
{

class binary_reader : public file_stream
{
public:
	binary_reader()
        	: file_stream()
    	{
    	}

    	binary_reader(const char* fileName) : file_stream(fileName, mode::rd)
    	{
    	}

	binary_reader(const std::string& fileName) : binary_reader(fileName.c_str())
    	{

    	}

	bool open(const char *fileName)
    	{
        	return file_stream::open(fileName, mode::wr);
    	}

    	bool open(const std::string& fileName)
	{
        	return open(fileName.c_str());
	}

	template<typename T>
	binary_reader &operator>>(T& val)
	{
		uint8_t buffer[sizeof(T)];
		read(buffer, sizeof(T), 1);
		val = *((T*)buffer);
		return *this;
	}

	template<typename T>
	binary_reader &operator>>(T* val)
	{
		read(val, sizeof(T), 1);
		return *this;
	}


private:
};

}

#endif

