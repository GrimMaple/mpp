/* - io/file_stream.hpp ---------------------------------------------------------------------------
* File Stream abstraction for binary_* classes.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_FILE_STREAM_
#define _MPP_IO_FILE_STREAM_

#include <string>
#include <cstdio>

namespace mpp
{

class file_stream
{
public:
	enum mode : uint32_t
	{
		rd = 0,
		wr,
		app
	};

	enum origin : uint32_t
	{
		begin = SEEK_SET,
		end = SEEK_END,
		set = SEEK_CUR
	};

	file_stream()
		: f(nullptr),
		  isOpen(false)
	{

	}

	file_stream(const char* fileName, mode mod)
		: file_stream()
	{
		open(fileName, mod);
	}

	file_stream(const std::string& fileName, mode mod)
		: file_stream(fileName.c_str(), mod)
	{

	}

	bool open(const char* fileName, mode mod)
	{
		if(isOpen)
			return false;
		switch(mod)
		{
		case mode::rd:
			f = fopen(fileName, "rb");
			break;
		case mode::wr:
			f = fopen(fileName, "wb");
			break;
		case mode::app:
			f = fopen(fileName, "ab");
			break;
		} 
		isOpen = (f != nullptr);
		return isOpen;
	}

	void seek(size_t length, origin orig)
	{
		fseek(f, length, orig);
	}

	bool eof()
	{
		return feof(f);
	}

	void close()
	{
		if(isOpen)
		{
			fclose(f);
			//f = nullptr;
		}
	}

	size_t where() const
	{
		return ftell(f);
	}

	bool is_open() const
	{
		return isOpen;
	}

	virtual ~file_stream()
	{
		close();
	}

	void write(const void* data, size_t size, size_t count)
	{
		fwrite(data, size, count, f);
	}

	void read(void* data, size_t size, size_t count)
	{
		fread(data, size, count, f);
	}
protected:

	FILE *f;
	bool isOpen;
};

}

#endif //  _MPP_IO_FILE_STREAM_

