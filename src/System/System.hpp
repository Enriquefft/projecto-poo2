#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <memory>
#include <tuple>
#include <vector>

#include "../View/View.hpp"

template <bool singleView = true> class System {

public:
  System() = default;
  void run();

private:
  View m_vista;
};

// class specialization
template <> class System<false> {
public:
  System() = delete;
  void run();

private:
  std::vector<View> m_vista;
};

#endif // !SYSTEM_HPP
