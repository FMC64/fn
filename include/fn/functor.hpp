#pragma once

#include <utility>

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
	name<T> fmap(Fn &&fn) const;		\
}						\

template <typename T, typename Fn>
static inline decltype(auto) fmap(T &&v, Fn &&fn)
{
	return v.fmap(std::forward<Fn>(fn));
}

}