#include <iostream>
#include <concepts>
#include <type_traits>

template<bool Condition, typename Then, typename Else>
struct If;

template<typename Then, typename Else>
struct If<true, Then, Else> {
  using type = Then;
};

template<typename Then, typename Else>
struct If<false, Then, Else> {
  using type = Else;
};

template<bool Condition, typename Then, typename Else>
using If_t = typename If<Condition, Then, Else>::type;

template<typename T>
concept ForBody = std::is_invocable_v<T, int>;

template<int i, int j, int jump>
struct ForwardFor;

template<int i, int j, int jump>
struct BackwardFor;

struct EmptyFor {
  template<ForBody F>
  static constexpr void compute(F &&) {
    return;
  }
};

template<int i, int j, int jump>
struct ForwardForHelper:
  If_t<
    i >= j,
    EmptyFor,
    ForwardFor<i, j, jump>
  >
{ };

template<int i, int j, int jump>
struct BackwardForHelper:
  If_t<
    i <= j,
    EmptyFor,
    BackwardFor<i, j, jump>
  >
{ };

template<int i, int j, int jump>
struct ForwardFor {
  using ForwardForNext = ForwardForHelper<i + jump, j, jump>;
  
  template<ForBody F>
  static constexpr void compute(F &&f) {
    f(i);
    ForwardForNext::compute(std::forward<F>(f));
  }
};

template<int i, int j, int jump>
struct BackwardFor {
  using BackwardForNext = BackwardForHelper<i + jump, j, jump>;
  
  template<ForBody F>
  static constexpr void compute(F &&f) {
    f(i);
    BackwardForNext::compute(std::forward<F>(f));
  }
};

template<int i, int j, int jump>
struct For:
  If_t<
    jump < 0,
    BackwardForHelper<i, j, jump>,
    ForwardForHelper<i, j, jump>
  >
{ static_assert(jump != 0); };

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

int main() {
  For<0, 10, 1>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<0, 10, 2>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<0, 10, 3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<12, 10, 3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<9, -1, -1>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<8, -1, -2>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<9, -1, -3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  For<9, 12, -3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  
  LoopBasedFor<0, 10, 1>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<0, 10, 2>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<0, 10, 3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<12, 10, 3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<9, -1, -1>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<8, -1, -2>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<9, -1, -3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  LoopBasedFor<9, 12, -3>::compute([] (int i) { std::cout << i << ' '; });
  std::cout << '\n';
  
  return 0;
}

