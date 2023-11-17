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
struct InsertionSort {
  static constexpr auto sort(ArrayType auto const &list) {
    auto copy = list;
    sort_helper(copy);
    return copy;
  }

  template<size_t index = 1>
  static constexpr void sort_helper(ArrayType auto &&list) {
    if constexpr (index < n) {
      int key = list[index];
      int j = index - 1;
      LoopBasedFor<index - 1, -1, -1>::compute([&](int) {
        if (j >= 0 && list[j] > key) {
          list[j + 1] = list[j];
          --j;
        }
      });
      list[j + 1] = key;
      sort_helper<index + 1>(std::forward<decltype(list)>(list));
    }
  }
};

constexpr int N = 128;

constexpr std::array<int, N> generate_data() {
  std::array<int, N> v;
  for (int i = 0; i < N; ++i)
    v[i] = N - i;
  return v;
}

int main() {
  constexpr auto data = generate_data();

  for (int i : data)
    std::cout << i << ' ';
  std::cout << '\n';

  constexpr auto result = InsertionSort<N>::sort(data);
  constexpr auto expected = []() {
    std::array<int, N> v;
    for (int i = 0; i < N; ++i)
      v[i] = i + 1;
    return v;
  }();
  static_assert(result == expected);

  for (int i : result)
    std::cout << i << ' ';

  return 0;
}
