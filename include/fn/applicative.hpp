#pragma once

#include <utility>

namespace fn {

template <template <typename> class Ctx, typename Arg>
class Applicative
{
};

#define FN_APPLICATIVE_IMPL(name) 		\
template <typename T>				\
class Applicative<name, T>			\
{						\
public:						\
	template <typename Fn>			\
	auto operator*(Fn &&fn) const;		\
}						\

}

#include "functor.hpp"
#include "monad.hpp"

namespace fn {

template <typename T>
class Pure;

FN_FUNCTOR_IMPL(Pure);
FN_APPLICATIVE_IMPL(Pure);
FN_MONAD_IMPL(Pure);

template <typename T>
class Pure : public Functor<Pure, T>, public Applicative<Pure, T>, public Monad<Pure, T>
{
	T m_v;

public:
	Pure(T &&v) :
		m_v(std::forward<T>(v))
	{
	}

	auto& get(void) const
	{
		return m_v;
	}
};

template <typename T>
auto pure(T &&v)
{
	return Pure<T>(std::forward<T>(v));
}

template <typename T>
template <typename Fn>
inline auto Functor<Pure, T>::fmap(Fn &&fn) const
{
	auto &u = static_cast<const Pure<T>&>(*this);
	return pure(fn(u.get()));
}

template <typename T>
template <typename Arg>
inline auto Applicative<Pure, T>::operator*(Arg &&arg) const
{
	auto &u = static_cast<const Pure<T>&>(*this);
	return fmap(u.get(), std::forward<Arg>(arg));
}

template <typename T>
template <typename Fn>
inline auto Monad<Pure, T>::operator>>(Fn &&fn) const
{
	auto &u = static_cast<const Pure<T>&>(*this);
	return fn(u.get());
}

}