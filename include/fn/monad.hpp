#pragma once

namespace fn {

template <template <typename> class Ctx, typename Arg>
class Monad
{
};

#define FN_MONAD_IMPL(name) 			\
template <typename T>				\
class Monad<name, T>				\
{						\
public:						\
	template <typename Fn>			\
	auto operator>>(Fn &&fn) const;	\
}						\

}