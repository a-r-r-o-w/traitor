#include <iostream>

template<int64_t n, int64_t m>
struct gcd {
  static constexpr int64_t value = gcd<m, n % m>::value;
};

template<int64_t m>
struct gcd<m, 0> {
  static constexpr int64_t value = m;
};

int main() {
  static_assert(gcd<0, 0>::value == 0);
  static_assert(gcd<2, 3>::value == 1);
  static_assert(gcd<16, 65536>::value == 16);
  static_assert(gcd<192875932678235LL, 123456789173450LL>::value == 5);

  std::cout << "gcd<0, 0>::value = " << gcd<0, 0>::value << '\n';
  std::cout << "gcd<2, 3>::value = " << gcd<2, 3>::value << '\n';
  std::cout << "gcd<16, 65536>::value = " << gcd<16, 65536>::value << '\n';
  std::cout << "gcd<192875932678235LL, 123456789173450LL>::value = " << gcd<192875932678235LL, 123456789173450LL>::value << '\n';
  
  return 0;
}
