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
	auto fmap(Fn &&fn) const;		\
}						\

template <typename Fn, typename T>
static inline decltype(auto) fmap(Fn &&fn, T &&v)
{
	return v.fmap(std::forward<Fn>(fn));
}

}