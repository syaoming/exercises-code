#ifndef ALGS_FUNDAMENTALS_STACK_HPP
#define ALGS_FUNDAMENTALS_STACK_HPP

#include "list.hpp"

/*
 * stack.hpp
 * LIFO Stack implemented with linked list. This class use the same interface
 * as std::stack, except that it doesn't support customized container (it is
 * not a container adapter)
 *
 * TODO : implement full construtors
 * TODO : implement non-member stuffs
 */

namespace algs {

template<class Item>
class Stack {
public:

  // Member types
  using container_type  = List<Item>;
  using value_type      = typename container_type::value_type;
  using size_type       = typename container_type::size_type;
  using reference	      = typename container_type::reference;
  using const_reference	= typename container_type::const_reference;
  using iterator        = typename container_type::iterator;
  using const_iterator  = typename container_type::const_iterator;

  // Default constructor
  // TODO: support complete construtor family
  Stack() {};

  // Copy Constrol : basically controlled by List<Item>
  ~Stack() = default;

  // Element access
  reference top() { return data.pop_front(); }
  const_reference top() const { return top(); }

  // Capacity
  bool empty() const { return data.empty(); }
  size_type size() const { return N; }

  // Modifiers //

  void push(const Item& item) { data.push_front(item); ++N; }
  void push(Item&& item) { data.push_front(std::move(item)); ++N; }

  // NOTE: using c++ 17 version
  template<class... Args> reference emplace( Args&&... args ) {
    ++N; return data.emplace_front(std::forward<Args>(args)...); }

  // NOTE: std::stack version return void
  Item pop() { --N; return data.pop_front(); }

  void swap(Stack& other) noexcept {
    using std::swap;
    swap(data, other.data);
  }

  // Non-standard functions //

  // Iterators. This is required in the ALGS book
  iterator begin() noexcept { return data.begin(); }
  const_iterator begin() const noexcept { return data.begin(); }
  const_iterator cbegin() const noexcept { return data.cbegin(); }
  iterator end() noexcept { return data.end(); }
  const_iterator end() const noexcept { return data.end(); }
  const_iterator cend() const noexcept { return data.cend(); }

  // TODO: self-printing
  friend std::ostream& operator<<(std::ostream& os, const Stack& stack) {
    os << "Stack(" << stack.N << "){";
    if (stack.empty()) return os << "}";
    os << stack.data.front();
    for (auto i = ++(stack.begin()); i != stack.end(); ++i)
      os << ", " << *i;
    return os << "}";
  }

private:

  List<Item> data;
  size_type N = 0;

};


// Non-member functions //
// TODO

// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// std::swap(algs::Stack) (specification in std namespace)


// Helper class //
// TODO

// std::uses_allocator<std::stack>


} // namespace algs

#endif
