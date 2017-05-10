#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include <cstddef>
#include <functional> // for std::less
#include <ostream> // self printing

/*
 * binary_tree.hpp
 * Binary Search Tree (BST) Symbol Table Implementation.
 * Interface naming is mimicing std::map.
 *
 * TODO: implement basic interface
 * TODO: add iterators
 */

namespace algs {

template<
  class Key,
  class Value,
  class Compare = std::less<Key>
> class BST {

  using key_type = Key;
  using value_type = Value;
  using size_type = std::size_t;

  // a private two-children node
  struct Node {
    Key key;
    Value val;
    size_type count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Key&& k, Value&& v) : key(k), val(v), count(1) {};
  };

public:

  // Default constructor
  BST(Compare comp = Compare()) : root(nullptr), less(comp) {};

  // Copy controls
  ~BST() = default;

  // element access and modifiers
  void put(const Key& k, const Value& v) { // put a key-value pair
    put(Key(k), Value(v)); }
  void put(Key&& k, Value&& v) { // move a key-value pair
    put(root, std::move(k), std::move(v)); }
  void get(const Key& k) const { // get a value by key
    // TODO
    return ;
  }
  Value pop(const Key& k) { // erase a key-value pair
    // TODO
    return Value();
  }

  // capacity
  bool empty() const { return root == nullptr; }
  size_type size() const { // number of all kay-value pairs
    if (this->empty()) return 0;
    return root->count;
  }

  // lookup
  bool contains(const Key& k) const { // existency query
    // TODO
    return true;
  }
  const Key& min() const { // smallest key
    // TODO
    return Key();
  }
  const Key& max() const { // greatest key
    // TODO
    return Key();
  }
  const Key& floor(const Key& k) const { // largest key <= k
    // TODO
    return Key();
  }
  const Key& ceiling(const Key& k) const { // smallest key >= k
    // TODO
    return Key();
  }
  size_type rank(const Key& k) const { // number of keys < k
    // TODO
    return 0;
  }
  const Key& select(size_type r) const { // key of rank r
    // TODO
    return Key();
  }
  size_type size(const Key& lo, const Key& hi) const {
    // number of keys in [lo, hi]
    // TODO
    return 0;
  }

  // Printing
  friend std::ostream& operator<<(std::ostream& os, const BST& bst) {
    // TODO : use an iterator ?
    os << "{" << std::endl;
    os << bst.root;
    os << "}";
    return os;
  }


private:
  Node* root = nullptr;
  Compare less;

  // Implementation Helpers //

  // Put a pair into a (sub-)tree, return the new (subtree-)root
  void put(Node* &x, Key&& key, Value&& val) {
    // Make a new node if it's the first one
    if (x == nullptr) {
      x = new Node(std::move(key), std::move(val));
      return;
    }
    if (less(key, root->key)) put(x->left, std::move(key), std::move(val));
    else if (less(root->key, key)) put(x->right, std::move(key), std::move(val));
    else x->val = std::move(val);
  }

  // Get a value by key from a (sub-)tree
  Value& get(Node* x, const Key& key) {
    if (x == nullptr) return Value(); // undefine behaviour
    if (less(key, x->key)) return Value();
  }

  // recursive printing of nodes
  friend std::ostream& operator<<(std::ostream& os, Node* x) {
    if (x == nullptr) return os;
    os << x->left;
    os << "  " << x->key << " : " << x->val << "," << std::endl;
    os << x->right;
    return os;
  }

};

} // namespace algs

#endif
