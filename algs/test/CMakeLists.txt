# Test the libraries

# utils.h
set(utils_list "random" "io")
foreach(name ${utils_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# fundamentals.hpp
set(fundamentals_list "list" "stack" "bag" "queue")
foreach(name ${fundamentals_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# sorting.hpp
set(sort_list "simple_sort" "heapsort" "mergesort" "linear_sort")
foreach(name ${sort_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# symbol_tables.hpp
set(st_list "binary" "bst" "rb_tree")
foreach(name ${st_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# graphs.hpp
set(graph_list
  "graph" "graph_search" "digraph" "dag" "weighted_graph"
  "mst"
)
foreach(name ${graph_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# strings.hpp
set(strings_list
  "string_sort"
)
foreach(name ${strings_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)
