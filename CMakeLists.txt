cmake_minimum_required(VERSION 3.13)
project(algorithms CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(
	algorithms
	src/stack/ListStack.hpp
	src/stack/SmartListStack.hpp
	src/stack/ArrayStack.hpp
	src/stack/Stackable.hpp
	src/Util.hpp
	src/queue/ListQueue.hpp
	src/queue/ArrayQueue.hpp
	src/queue/ListQueue.cpp
	src/queue/ArrayQueue.cpp
	src/stack/TwoStackArray.cpp
	src/stack/TwoStackArray.hpp
	src/deque/ArrayDeque.cpp
	src/deque/ArrayDeque.hpp
	src/queue/TwoStackQueue.cpp
	src/queue/TwoStackQueue.hpp
	src/stack/TwoQueueStack.cpp
	src/stack/TwoQueueStack.hpp
	src/list/DoublyList.cpp
	src/list/DoublyList.hpp
	src/list/SinglyList.cpp
	src/list/SinglyList.hpp
	src/list/OnePtrDoublyList.cpp
	src/list/OnePtrDoublyList.hpp
	src/memory/MultiMemory.cpp
	src/memory/MultiMemory.hpp
	src/memory/SingleMemory.cpp
	src/memory/SingleMemory.hpp
	src/memory/StackMemory.cpp
	src/memory/StackMemory.hpp
	src/tree/BinaryTree.cpp
	src/tree/BinaryTree.hpp
	src/tree/SiblingTree.cpp
	src/tree/SiblingTree.hpp
	src/table/BitVector.cpp
	src/table/BitVector.hpp
	src/table/DirectList.cpp
	src/table/DirectList.hpp
	src/table/HashTable.cpp
	src/table/HashTable.hpp
	src/tree/RBTree.cpp src/tree/RBTree.hpp src/math/Math.cpp src/math/Math.hpp src/tree/BTree.cpp src/tree/BTree.hpp src/graph/AdjacencyList.cpp src/graph/AdjacencyList.hpp src/graph/AdjacencyMatrix.cpp src/graph/AdjacencyMatrix.hpp src/graph/adjv.cpp src/graph/adjv.hpp)
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
	src/hanoi/Hanoi.hpp
	src/hanoi/Hanoi.cpp
)