#pragma once

#include <utility>
#include <type_traits>

namespace fn {

template <template <typename> class Ctx, typename Arg>
class Functor
{
};

#define FN_FUNCTOR_IMPL(name) 			\
template <typename T>				\
class Functor<name, T>				\
{						\
public:						\
	template <typename Fn>			\
	auto fmap(Fn &&fn) const;		\
}						\

template <typename Fn, typename T>
static inline decltype(auto) fmap(Fn &&fn, T &&v)
{
	return v.fmap(std::forward<Fn>(fn));
}

template <typename Fn, template <typename> class Ctx, typename Arg>
static inline decltype(auto) operator%(Fn &&fn, Functor<Ctx, Arg> &&v)
{
	return v.fmap(std::forward<Fn>(fn));
}

}