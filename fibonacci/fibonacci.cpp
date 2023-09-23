#include <cstdint>
#include <iostream>

template<size_t n>
struct fibonacci {
  static constexpr uint64_t value = fibonacci<n - 1>::value + fibonacci<n - 2>::value;
};

template<>
struct fibonacci<0> {
  static constexpr uint64_t value = 0;
};

template<>
struct fibonacci<1> {
  static constexpr uint64_t value = 1;
};

int main() {
  static_assert(fibonacci<0>::value == 0);
  static_assert(fibonacci<1>::value == 1);
  static_assert(fibonacci<5>::value == 5);
  static_assert(fibonacci<21>::value == 10946);
  static_assert(fibonacci<79>::value == uint64_t(14472334024676221));

  std::cout << "fibonacci<0>::value = " << fibonacci<0>::value << '\n';
  std::cout << "fibonacci<1>::value = " << fibonacci<1>::value << '\n';
  std::cout << "fibonacci<5>::value = " << fibonacci<5>::value << '\n';
  std::cout << "fibonacci<21>::value = " << fibonacci<21>::value << '\n';
  std::cout << "fibonacci<79>::value = " << fibonacci<79>::value << '\n';
 
  return 0;
}
