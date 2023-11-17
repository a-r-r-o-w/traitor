#include <ios>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
struct has_odd_template_params: std::false_type
{ };

template<template<typename...> typename T, typename... U> requires (sizeof...(U) % 2 == 1)
struct has_odd_template_params<T<U...>>: std::true_type
{ };

template<typename T>
static constexpr bool has_odd_template_params_v = has_odd_template_params<T>::value;

template<typename... T>
struct example
{ };

int main() {
  static_assert(!has_odd_template_params_v<std::vector<int>>); // vector has 2 template parameters
  static_assert(has_odd_template_params_v<example<int>>);
  static_assert(!has_odd_template_params_v<example<int, int>>);
  static_assert(has_odd_template_params_v<example<int, float, bool, std::vector<int>, int>>);
  
  std::cout << std::boolalpha;
  std::cout << "!has_odd_template_params_v<std::vector<int>> = " << !has_odd_template_params_v<std::vector<int>> << '\n';
  std::cout << "has_odd_template_params_v<example<int>> = " << has_odd_template_params_v<example<int>> << '\n';
  std::cout << "!has_odd_template_params_v<example<int, int>> = " << !has_odd_template_params_v<example<int, int>> << '\n';
  std::cout << "has_odd_template_params_v<example<int, float, bool, std::vector<int>, int>> = " << has_odd_template_params_v<example<int, float, bool, std::vector<int>, int>> << '\n';

  return 0;
}
