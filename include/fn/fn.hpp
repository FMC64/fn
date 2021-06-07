#pragma once

#include <type_traits>
#include <tuple>
#include <boost/preprocessor/variadic.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

namespace fn {

namespace cog {

/* CREDIT START */
/* snippet from @ecatmur (https://stackoverflow.com/a/12283159/11921314) */
template<typename T>
struct remove_class
{
};

template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...)>
{
	static inline constexpr size_t count = sizeof...(A);
};
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const>
{
	static inline constexpr size_t count = sizeof...(A);
};
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) volatile>
{
	static inline constexpr size_t count = sizeof...(A);
};
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const volatile>
{
	static inline constexpr size_t count = sizeof...(A);
};

template <typename T>
struct is_callable
{
	template <typename U, typename V = decltype(&U::operator())>
	static inline constexpr bool test(void)
	{
		return true;
	}

	template <typename U, typename ...Args>
	static inline constexpr bool test(Args &&...)
	{
		return false;
	}

	static inline constexpr bool value = test<T>();
};

template <typename T>
struct fun_arg
{
	static inline constexpr size_t get_count(void)
	{
		if constexpr (is_callable<T>::value || true)
			return remove_class<decltype(&std::remove_reference<T>::type::operator())>::count;
		else
			return 0;
	}

	static inline constexpr size_t count = get_count();
};
template <typename R, typename... A>
struct fun_arg<R(A...)>
{
	static inline constexpr size_t count = sizeof...(A);
};
template <typename R, typename... A>
struct fun_arg<R(&)(A...)>
{
	static inline constexpr size_t count = sizeof...(A);
};
template<typename R, typename... A>
struct fun_arg<R(*)(A...)>
{
	static inline constexpr size_t count = sizeof...(A);
};

/* CREDIT END @ecatmur */

template <size_t Count, typename ...Acc, typename Fn>
decltype(auto) decompose_impl(std::tuple<Acc...> &&acc, Fn &&fn)
{
	return [acc, fn]<typename First>(First &&first) -> decltype(auto) {
		if constexpr (Count == 1) {
			return std::apply(fn, std::tuple_cat(acc, std::forward_as_tuple(first)));
		} else {
			return decompose_impl<Count - 1>(std::tuple_cat(acc, std::forward_as_tuple(first)), fn);
		}
	};
}

template <size_t Count, typename Fn>
decltype(auto) decompose(Fn &&fn)
{
	if constexpr (Count == 0) {
		return fn();
	} else {
		return decompose_impl<Count>(std::tuple<>(), std::forward<Fn>(fn));
	}
}

}

}

#define fn_lambda_probe_result(a) { return a; } )
#define fn_lambda_prepend_auto_each(r, data, elem) , data elem
#define fn_lambda_eat_first_impl(ignore, ...) __VA_ARGS__
#define fn_lambda_eat_first(...) fn_lambda_eat_first_impl(__VA_ARGS__)
#define fn_lambda_prepend_auto(...) BOOST_PP_SEQ_FOR_EACH(fn_lambda_prepend_auto_each, auto, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define lc_(cap, ...) fn::cog::decompose<BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)>(cap(__VA_OPT__(fn_lambda_eat_first(fn_lambda_prepend_auto(__VA_ARGS__)))) -> decltype(auto) fn_lambda_probe_result
#define l_(...) lc_([], __VA_ARGS__)
#define ls_(...) l_(x)(x __VA_ARGS__)
#define lcs_(cap, ...) lc_(cap, x)(x __VA_ARGS__)
#define lps_(...) l_(x, y)(x __VA_ARGS__ y)
#define lpcs_(cap, ...) lc_(cap, x, y)(x __VA_ARGS__ y)