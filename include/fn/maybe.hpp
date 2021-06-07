#pragma once

#include "functor.hpp"
#include "monad.hpp"
#include "applicative.hpp"

#include <optional>
#include <utility>
#include <stdexcept>
#include <type_traits>

namespace fn {

struct Nothing_t;

template <typename T>
class Maybe;

FN_FUNCTOR_IMPL(Maybe);
FN_APPLICATIVE_IMPL(Maybe);
FN_MONAD_IMPL(Maybe);

template <typename T>
class Maybe : public Functor<Maybe, T>, public Applicative<Maybe, T>, public Monad<Maybe, T>
{
	std::optional<T> m_v;

public:
	static inline constexpr bool is_maybe_v = true;

	Maybe(const Nothing_t&)
	{
	}
	template <typename ...Args>
	Maybe(Args &&...args) :
		m_v(std::forward<Args>(args)...)
	{
	}
	template <typename U>
	Maybe(Pure<U> &&v) :
		m_v(v.get())
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

private:
	void assert_nempty(void) const
	{
		if (isNothing())
			throw std::runtime_error("Maybe: fromJust but value is Nothing");
	}

public:
	const T& fromJust(void) const
	{
		assert_nempty();
		return *m_v;
	}

	T& fromJust(void)
	{
		assert_nempty();
		return *m_v;
	}
};

#define FN_FWD_MAYBE(name) 			\
template <typename T>				\
static inline decltype(auto) name(T &&v)	\
{						\
	return v.name();			\
}						\

FN_FWD_MAYBE(isJust)
FN_FWD_MAYBE(isNothing)
FN_FWD_MAYBE(fromJust)
#undef FN_FWD_MAYBE

#define FN_FWD_MAYBE(name) auto name(void) const { return Maybe<int>().name(); }
struct Nothing_t
{
	FN_FWD_MAYBE(isJust);
	FN_FWD_MAYBE(isNothing);
	FN_FWD_MAYBE(fromJust);

	template <typename Fn>
	auto fmap(Fn&&) const
	{
		return Nothing_t{};
	}

	template <typename Fn>
	auto appl(Fn&&) const
	{
		return Nothing_t{};
	}

	template <typename Fn>
	auto operator>>(Fn&&) const
	{
		return Nothing_t{};
	}
};
#undef FN_FWD_MAYBE
static inline constexpr Nothing_t Nothing{};

template <typename T>
static inline Maybe<T> Just(T &&v)
{
	return Maybe<T>(std::forward<T>(v));
}

template <typename T>
template <typename Fn>
inline auto Functor<Maybe, T>::fmap(Fn &&fn) const
{
	auto &u = static_cast<const Maybe<T>&>(*this);
	using Tr = decltype(fn(u.fromJust()));
	if (u.isJust())
		return Maybe<Tr>(fn(u.fromJust()));
	else
		return Maybe<Tr>();
}

template <typename T>
template <typename Arg>
inline auto Applicative<Maybe, T>::operator*(Arg &&arg) const
{
	auto &u = static_cast<const Maybe<T>&>(*this);
	using Tr = decltype(u.fromJust()(arg.fromJust()));
	if (u.isJust() && arg.isJust())
		return Maybe<Tr>(u.fromJust()(arg.fromJust()));
	else
		return Maybe<Tr>();
}

template <typename T>
template <typename Fn>
inline auto Monad<Maybe, T>::operator>>(Fn &&fn) const
{
	auto &u = static_cast<const Maybe<T>&>(*this);
	using Tr = decltype(fn(u.fromJust()));
	static_assert(Tr::is_maybe_v, ">> result must be Maybe<T>");
	if (u.isJust())
		return fn(u.fromJust());
	else
		return Tr();
}

}