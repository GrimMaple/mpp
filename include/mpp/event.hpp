/* - event.hpp ------------------------------------------------------------------------------------
* Provides basic eventing mechanism on a subscription basis
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_EVENT_
#define _MPP_EVENT_

#include <unordered_map>
#include <functional>

#include "no_copy.hpp"

namespace mpp
{

template<typename ... Args>
class event : public no_copy
{
public:
	event() = default;

	class token
	{
	public:
		token() : ref(nullptr) {}

		token(event <Args ...> *base)
			: ref(base) {}

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
		event<Args...> *ref;
		friend class event<Args ... >;
	};
	void operator()(Args... args)
	{
		for (auto& i : callbacks)
			i.second(args...);
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
	void unsubscribe(const token& tok)
	{
		callbacks.erase(tok.i);
	}

	int id = 0;
	std::unordered_map<int, std::function<void(Args... args)>> callbacks;
};

}

#endif
