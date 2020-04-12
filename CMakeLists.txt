cmake_minimum_required(VERSION 3.13)
project(algorithms CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(
	algorithms
	src/stack/list_stack.h
	src/stack/smart_list_stack.h
	src/stack/array_stack.h
	src/stack/stackable.h
	src/util.h
	src/queue/list_queue.h
	src/queue/array_queue.h
	src/queue/list_queue.cpp
	src/queue/array_queue.cpp
	src/stack/two_stack_array.cpp
	src/stack/two_stack_array.h
	src/deque/array_deque.cpp
	src/deque/array_deque.h
	src/queue/two_stack_queue.cpp
	src/queue/two_stack_queue.h
	src/stack/two_queue_stack.cpp
	src/stack/two_queue_stack.h
	src/list/doubly_list.cpp
	src/list/doubly_list.h
	src/list/singly_list.cpp
	src/list/singly_list.h
	src/list/one_ptr_doubly_list.cpp
	src/list/one_ptr_doubly_list.h
	src/memory/multi_memory.cpp
	src/memory/multi_memory.h
	src/memory/single_memory.cpp
	src/memory/single_memory.h
	src/memory/stack_memory.cpp
	src/memory/stack_memory.h
	src/tree/binary_tree.cpp
	src/tree/binary_tree.h
	src/tree/sibling_tree.cpp
	src/tree/sibling_tree.h
	src/table/bit_vector.cpp
	src/table/bit_vector.h
	src/table/direct_list.cpp
	src/table/direct_list.h
	src/table/hash_table.cpp
	src/table/hash_table.h
	src/tree/rb_tree.cpp src/tree/rb_tree.h src/math/math.cpp src/math/math.h src/tree/b_tree.cpp src/tree/b_tree.h src/graph/adjacency_list.cpp src/graph/adjacency_list.h src/graph/adjacency_matrix.cpp src/graph/adjacency_matrix.h)
set_target_properties(algorithms PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
	algorithms

	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include/algorithms>

	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src/internal"
)


# gtest
#enable_testing()
find_package(GTest REQUIRED)
add_executable(
	algorithms_tests
	test/stack_tests.cpp
	test/queue_tests.cpp
	test/deque_tests.cpp
	test/list_tests.cpp
	test/memory_tests.cpp
	test/tree_tests.cpp
	test/table_tests.cpp
	test/math_tests.cpp test/graph_tests.cpp)
target_link_libraries(algorithms_tests GTest::GTest GTest::Main algorithms)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
add_executable(
	main
	main.cpp)
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
target_link_libraries(main algorithms Threads::Threads)

add_executable(
	hanoi
	src/hanoi/hanoi.h
	src/hanoi/hanoi.cpp
)