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