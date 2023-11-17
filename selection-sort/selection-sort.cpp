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
struct SelectionSort {
  static constexpr auto sort(ArrayType auto const &list) {
    auto copy = list;
    sort_helper(copy);
    return copy;
  }

  template <size_t i>
  static constexpr void find_min_and_swap(ArrayType auto &&list) {
    int min = i;
    LoopBasedFor<i + 1, n, 1>::compute([&] (int j) {
      if (list[j] < list[min])
        min = j;
    });
    std::swap(list[i], list[min]);
  }

  template <size_t index = 0>
  static constexpr void sort_helper(ArrayType auto &&list) {
    if constexpr (index < n - 1) {
      find_min_and_swap<index>(std::forward<decltype(list)>(list));
      sort_helper<index + 1>(std::forward<decltype(list)>(list));
    }
  }
};

const int N = 128;

constexpr std::array<int, N> generate_data() {
  std::array<int, N> v;
  for (int i = 0; i < N; ++i)
    v[i] = N - i;
  return v;
}

void normal_selection_sort(ArrayType auto &list) {
  for (int i = 0; i < N - 1; ++i) {
    int min = i;
    for (int j = i + 1; j < N; ++j)
      if (list[j] < list[min])
        min = j;
    std::swap(list[i], list[min]);
  }
}

int main() {
  constexpr auto data = generate_data();
  
  for (int i: data)
    std::cout << i << ' ';
  std::cout << '\n';
  
  constexpr auto result = SelectionSort<N>::sort(data);
  constexpr auto expected = [] () {
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
