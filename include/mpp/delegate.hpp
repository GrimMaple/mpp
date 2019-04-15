/* - delegate.hpp ---------------------------------------------------------------------------------
* A wrap over for command line arguments parsing.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_ARGS_
#define _MPP_ARGS_

#include <unordered_map>
#include <functional>

namespace mpp
{

template<typename ... Args>
class delegate
{
public:
	delegate()
		: id(0)
	{

	}

	class token
	{
	public:
		token() : ref(nullptr) {}
		//template<typename ... Args>
		token(delegate <Args ...> *base)
			: ref(base)
		{

		}

		//template<typename ... Args>
		token(token& other)
			: i(other.i),
			ref(other.ref)
		{
			other.ref = nullptr;
		}

		bool operator==(const token& other)
		{
			return other.id == id;
		}

		//template<typename ... Args>
		void operator=(token& other)
		{
			i = other.i;
			ref = other.ref;
			other.ref = nullptr;
		}

		void discard()
		{
			ref = nullptr;
		}

		void disconnect()
		{
			if(ref)
				ref->unsubscribe(*this);
		}

		~token()
		{
			disconnect();
		}
	private:
		int i;
		delegate<Args...> *ref;
		friend class delegate<Args ... >;
	};
	void operator()(Args... args)
	{
		for (auto& i : callbacks)
			i.second(args...);
	}

	void unsubscribe(const token& tok)
	{
		callbacks.erase(tok.i);
	}

	token connect(const std::function<void(Args... args)>& func)
	{
		callbacks.insert({ id, func });
		token ret(this);
		ret.i = id;
		id++;
		return ret;
	}

private:
	int id;
	std::unordered_map<int, std::function<void(Args... args)>> callbacks;
};

}

#endif
