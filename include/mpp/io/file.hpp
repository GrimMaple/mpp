/* - io/binary_writer.hpp -------------------------------------------------------------------------
* Binary File Writer. Provides a better alternative for std::ofstream 
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_FILE_
#define _MPP_IO_FILE_

#include <vector>
#include <cstdio>

namespace mpp
{

class file
{
public:

	static std::vector<uint8_t> read_fully(const std::string& path)
	{
		return read_fully(path.c_str());
	}

	static std::vector<uint8_t> read_fully(const char* path)
	{
		FILE *f = fopen(path, "rb");
		if (!f)
			throw 1;
		fseek(f, 0, SEEK_END);
		long sz = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		uint8_t *data = new uint8_t[sz];
		fread(data, 1, sz, f);

		std::vector<uint8_t> ret(data, data+sz);
		return ret;
	}

	static std::vector<std::string> read_all_lines(const std::string& path)
	{
		return read_all_lines(path.c_str());
	}

	static std::vector<std::string> read_all_lines(const char* path)
	{
		FILE *f = fopen(path, "rt");
		if (!f)
			throw 1;
		std::vector<std::string> ret;
		char buff[1024*4];
		while (fgets(buff, 1024 * 4, f) != NULL)
			ret.push_back(std::string(buff));

		fclose(f);

		return ret;
	}

	static void write_all_lines(const std::vector<std::string>& strings, const char* path)
	{
		FILE *f = fopen(path, "wt");
		if (!f)
			throw 1;
		for (auto i : strings)
		{
			fputs(i.c_str(), f);
		}
		fclose(f);
	}
};

}

#endif