# Solutions to *Algorithms*

C++ solutions to some exercises, and implementation of algorithms listed in the
book *Algorithms*, 4th Edition, in C++. Implementation of algorithms are put in
[include](include/), and solutions are put in folders for each
chapters like [Chapter1](Chapter1/), [Chapter6](Chapter6/).

## Notes

Yes, the book is written for **Java**, and this repository is written in
**C++** (or, more precisely, C++11, with full respect for C++14 or C++17
regarding deprecated stuffs).

Also, the utility library (utils/io.hpp, utils/random.hpp, etc.) is
subtly different from those provided by the book. Check the book author's
packages here: https://github.com/kevin-wayne/algs4.

## Todos

- Implement half of all algorithms and data structures
  - RedBlack BST
  - KD tree
  - quick-select
- Implement some of the most interesting algorithms from the exercise.

## Implemented Algorithms and Data Structures

### [Fundamentals](include/fundamentals/)

1. Linked List ([list.hpp](include/fundamentals/list.hpp))
    - with linked-list mergesort
0. Bag (with linked-list) ([bag.hpp](include/fundamentals/bag.hpp))
0. Stack (with linked-list) ([stack.hpp](include/fundamentals/stack.hpp))

### [Sorting](include/sorting/)

1. Selection sort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Insertion sort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Shellsort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Mergesort (top-down and bottom-up) ([mergesort.hpp](include/sorting/mergesort.hpp))
0. Heapsort (and Priority Queue) ([heapsort.hpp](include/sorting/heapsort.hpp))
0. Radix sort ([linear.hpp](include/sorting/linear_sort.hpp))

### [Symbol Tables](include/symbol_tables/)

1. Binary search (Symbol Table) ([binary.hpp](include/symbol_tables/binary.hpp))
0. Binary Search Tree ([binary_tree.hpp](include/symbol_tables/binary_tree.hpp))
0. Red-black Binary Search Tree ([rb_tree.hpp](include/symbol_tables/rb_tree.hpp))

### Graphs

1. Graph ([graph.hpp](include/graphs/graph.hpp))
0. Digraph ([digraph.hpp](include/graphs/digraph.hpp))
0. Edge-weighted Graph ([weighted_graph.hpp](include/graphs/weighted_graph.hpp))
0. Depth- and Breadth-first search ([graph_search.hpp](include/graphs/graph_search.hpp))
0. Topological sort ([dag.hpp](include/graphs/dag.hpp))
0. Prim's MST algorithm (lazy ver.) ([mst.hpp](include/graphs/mst.hpp))

### Strings

1. Least-significant-digit-first string sort ([string_sort.hpp](include/strings/string_sort.hpp))
0.


<!-- Algorithms and Data Structures : Complete List

-- Chapter 1, basics --
1. Stack (with resizing array)  (todo)
2. Stack (with linked-list)
3. FIFO queue                   (todo)
4. Bag

-- Chapter 2, sort  --
1. Selection sort
2. Insertion sort
3. Shellsort
4. Top-down mergesort
5. Bottom-up mergesort
6. Quicksort                         (todo)
7. Quicksort with 3-way partitioning (todo)
8. Priority Queue
9. Heapsort

-- Chapter 3, search--
1. Sequential Search Symbol Table (todo)
2. Binary Search Symbol Table
3. Binary Search Tree Symbol Table class
4. Red-black Binary Search Tree Symbol Table class     (todo)
    @NOTE: complete the implementation 
5. Separate Chaining Hash Symbol Table (todo)
6. Linear Probing Hash Symbol Table (todo)

-- Chapter 4, graph --
1. Adjacency-list Graph class
2. Depth-first search for paths
3. Breadth-first search for paths
4. Depth-first search for connected components    (todo)
5. Adjacency-list Directed Digraph class          (todo)
6. Reachability / Directed Depth-first search     (todo)
    - Depth-first directed paths                  (todo)
    - Breadth-first directed paths                (todo)
7. Directed cycle       (todo)
8. Depth-first Order    
9. Topological sort     
10. Kosaraju strong connected components   (todo)
-- weighted graph --
11. Edge Weighted Graph class
    - Edge class                 
12. Lazy version of Prim's MST
13. Eager version of Prim's MST   (todo)
  - needs IndexPQ (no implemented)
-- weighted directed graph --
14. Edge-weighted Directed Graph class  (todo)
    - Directed Weighted Edge class      (todo)
15. Dijkstra's shortest-path            (todo)
16. Shortest-path in edge-weighted DAG  (todo)
17. Bellman-ford shortest-path          (todo)

-- Chapter 5, strings --
1. Least-significant-digit-first string sort
2. Most-significant-digit-first string sort (todo)
3. Three-way string quicksort              (todo)
-- trie --
4. Trie Symbol Table class          (todo)
5. Ternary Search Trie Symbol Table (todo)
-- substring search --
6. Knuth-Morris-Pratt substring search (todo)
7. Boyer-Moore substring search        (todo)
8. Rabin-Karp fingerprint search       (todo)
9. Regular expression pattern matching (todo)
-- data compression --
10. Huffman compression           (todo)
11. LZW compression and expansion (todo)

## Addition Algorithms List

1. Quick-select (todo; page 346) (todo)
0. A* algorithm (page 358)
  - embed in Graph module? (todo)
0. AVL tree (page 452) (todo)
0. kd-tree (http://algs4.cs.princeton.edu/92search/ and http://algs4.cs.princeton.edu/lectures/99GeometricSearch-2x2.pdf) (todo)
0. B-tree (page 872) (todo)
0. B*-tree (page 924) (todo)

end of the list -->
