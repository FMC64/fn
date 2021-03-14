#pragma once

#include "monad.hpp"

#include <optional>
#include <utility>

namespace fn {

struct Nothing_t {};
static inline constexpr Nothing_t Nothing_v{};

template <typename T>
class Maybe : public Monad<Maybe, T>
{
	std::optional<T> m_v;

public:
	Maybe(const Nothing_t&)
	{
	}
	template <typename ...Args>
	Maybe(Args &&...args) :
		m_v(std::forward<Args>(args)...)
	{
	}

	bool isJust(void) const
	{
		return m_v.has_value();
	}

	bool isNothing(void) const
	{
		return !m_v.has_value();
	}

	const T& fromJust(void) const
	{
		return *m_v;
	}

	T& fromJust(void)
	{
		return *m_v;
	}
};

template <typename T>
static inline Maybe<T> Just(T &&v)
{
	return Maybe<T>(std::forward<T>(v));
}

template <typename T>
static inline const Maybe<T> Nothing;

FN_MONAD_IMPL(Maybe);

template <typename T>
template <typename Fn>
Maybe<T> Monad<Maybe, T>::operator>>(Fn &&fn) const
{
	auto &u = static_cast<const Maybe<T>&>(*this);
	if (u.isJust())
		return fn(u.fromJust());
	else
		return Maybe<T>();
}

}