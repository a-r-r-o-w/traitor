#include <cstddef>
#include <cstdint>
#include <iostream>

template<size_t n>
struct factorial {
  static constexpr uint64_t value = n * factorial<n - 1>::value;
};

template<>
struct factorial<0> {
  static constexpr uint64_t value = 1;
};

int main() {
  static_assert(factorial<0>::value == 1);
  static_assert(factorial<1>::value == 1);
  static_assert(factorial<3>::value == 6);
  static_assert(factorial<10>::value == 3628800);
  static_assert(factorial<18>::value == uint64_t(6402373705728000));

  std::cout << "factorial<0>::value = " << factorial<0>::value << '\n';
  std::cout << "factorial<1>::value = " << factorial<1>::value << '\n';
  std::cout << "factorial<3>::value = " << factorial<3>::value << '\n';
  std::cout << "factorial<10>::value = " << factorial<10>::value << '\n';
  std::cout << "factorial<18>::value = " << factorial<18>::value << '\n';

  return 0;
}
