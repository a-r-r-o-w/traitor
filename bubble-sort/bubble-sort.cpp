#include <iostream>
#include <array>

template<typename T>
concept ForBody = std::is_invocable_v<T, int>;

template<typename T>
concept ArrayType = requires(T t) {
  t[0];
};

template<int i, int j, int jump>
struct LoopBasedFor {
  static_assert(jump != 0);
  
  template<ForBody F>
  static constexpr void compute(F &&f) {
    if constexpr (jump > 0)
      for (int x = i; x < j; x += jump)
        f(x);
    else
      for (int x = i; x > j; x += jump)
        f(x);
  }
};

template<size_t n>
struct BubbleSort {
  static constexpr auto sort(ArrayType auto const &list) {
    static_assert(std::is_constant_evaluated());
    auto copy = list;
    sort_helper(copy);
    return copy;
  }

  static constexpr void sort_helper(ArrayType auto &&list) {
    LoopBasedFor<0, n - 1, 1>::compute([&] (int i) {
      if (list[i] > list[i + 1])
        std::swap(list[i], list[i + 1]);
    });
    BubbleSort<n - 1>::sort_helper(std::forward<decltype(list)>(list));
  }
};

template<>
struct BubbleSort<0> {
  static constexpr auto sort(ArrayType auto &) {
    return;
  }
  
  static constexpr void sort_helper(ArrayType auto&&) {
    return;
  }
};

const int N = 128;

constexpr std::array<int, N> generate_data() {
  static_assert(std::is_constant_evaluated());
  std::array<int, N> v;
  for (int i = 0; i < N; ++i)
    v[i] = N - i;
  return v;
}

static constexpr auto data = generate_data();

int main() {
  for (int i: data)
    std::cout << i << ' ';
  std::cout << '\n';
  
  constexpr auto result = BubbleSort<N>::sort(data);
  constexpr auto expected = [] () {
    static_assert(std::is_constant_evaluated());
    std::array<int, N> v;
    for (int i = 0; i < N; ++i)
      v[i] = i + 1;
    return v;
  } ();
  static_assert(result == expected);
  
  for (int i: result)
    std::cout << i << ' ';
  
  return 0;
}
