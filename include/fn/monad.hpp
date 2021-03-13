#pragma once

namespace fn {

template <typename Up>
class monad
{
public:
	template <typename Fn>
	Up operator>>(Fn &&fn);
};

}

#include <optional>
#include <tuple>

namespace fn {

template <typename T>
class maybe : public monad<maybe<T>>
{
	std::optional<T> m_v;

public:
	template <typename ...Args>
	maybe(Args &&...args) :
		m_v(std::forward<Args>(args)...)
	{
	}

	bool isJust(void)
	{
		return m_v.has_value();
	}

	T& fromJust(void)
	{
		return *m_v;
	}
};

template <typename T>
template <typename Fn>
maybe<T> monad<maybe<T>>::operator>>(Fn &&fn)
{
	return maybe<T>();
}

}