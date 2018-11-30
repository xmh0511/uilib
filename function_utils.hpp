#pragma once
#include <tuple>
#include "xjson.hpp"
template<typename T>
struct function_type
{

};
template<typename Ret,typename...Args>
struct function_type<Ret(Args...)>
{
	using ret = Ret;
	using params_tuple = std::tuple<Args...>;
	constexpr static const std::size_t params_size = sizeof...(Args);
	using method_type = Ret(Args...);
	//constexpr static const tuple_index_seque = std::make_index_sequence<params_size>{};
};
template<typename Ret,typename ClassName,typename...Args>
struct function_type<Ret(ClassName::*)(Args...) const>
{
	using ret = Ret;
	using params_tuple = std::tuple<Args...>;
	constexpr static const std::size_t params_size = sizeof...(Args);
	using method_type = Ret(Args...);
	//constexpr static const tuple_index_seque = std::make_index_sequence<params_size>{};
};

template<typename T,typename U = void>
struct function_traits
{

};

template<typename Ret,typename...Args>
struct function_traits<Ret(*)(Args...)>:public function_type<Ret(Args...)>
{

};

template<typename Ret,typename ClassName,typename...Args>
struct function_traits<Ret(ClassName::*)(Args...)>:public function_type<Ret(Args...)>
{

};

template<typename F>
struct function_traits<F, std::void_t<decltype(&F::operator())>>:public function_type<decltype(&F::operator())>
{

};

template<std::size_t N,std::size_t Max,typename Params_Tuple>
struct get_params_from_json
{
	template<typename Tuple>
	static auto work(const xmh::json& params_json, Tuple&& tuple) noexcept
	{
		//std::cout << typeid(std::remove_reference_t<std::tuple_element_t<N, Params_Tuple>>).name() << std::endl;
		//auto item = params_json[0];
		auto arg = params_json[N].get<std::remove_reference_t<std::tuple_element_t<N, Params_Tuple>>>();
		auto params = std::tuple_cat(tuple, std::make_tuple(arg));
		return get_params_from_json<N + 1, Max, Params_Tuple>::template work(params_json, params);
	}
};

template<std::size_t N,typename Params_Tuple>
struct get_params_from_json<N, N, Params_Tuple>
{
	template<typename Tuple>
	static auto work(const xmh::json& params_json, Tuple&& tuple) noexcept
	{
		return tuple;
	}
};
