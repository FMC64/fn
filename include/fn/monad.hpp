#pragma once

namespace fn {

template <template <typename> class Ctx, typename Arg>
class monad
{
public:
	template <typename Fn>
	Ctx<Arg> operator>>(Fn &&fn);
};

}

#include <optional>
#include <tuple>

namespace fn {

template <typename T>
class maybe : public monad<maybe, T>
{
	std::optional<T> m_v;

public:
	template <typename ...Args>
	maybe(Args &&...args) :
		m_v(std::forward<Args>(args)...)
	{
	}

	bool is_just(void)
	{
		return m_v.has_value();
	}

	T& from_just(void)
	{
		return *m_v;
	}
};

template <typename T>
class monad<maybe, T>
{
public:
	template <typename Fn>
	maybe<T> operator>>(Fn &&fn);
};

template <typename T>
template <typename Fn>
maybe<T> monad<maybe, T>::operator>>(Fn &&fn)
{
	auto &u = static_cast<maybe<T>&>(*this);
	if (u.is_just())
		return fn(u.from_just());
	else
		return maybe<T>();
}

}