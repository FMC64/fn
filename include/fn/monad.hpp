#pragma once

namespace fn {

template <typename Ctx>
class monad : public Ctx
{
public:
	using type = Ctx;

	template <typename Fn>
	monad operator>>(Fn &&fn);
};

//template <template <typename...> typename Ctx, typename ...Args, typename Fn>
//Ctx<Args...> operator>>(Ctx<Args...> &&in, Fn &&fn);

}

#include <optional>

namespace fn {

/*template <typename T>
template <typename Fn>
monad<std::optional<T>> monad<std::optional<T>>::operator>>(Fn &&fn);*/

}