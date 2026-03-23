## CP Practicals SS26—  Practical #1: Analysing Report 

## Problem 1 - Dynamic Arrays

### Problem Summary
Store N whole numbers into a dynamically growing array, or "container", and find its largest value and the smallest value as well as the total of all the values added together.

### Algorithm Description
Create a vector that holds N elements. Use the STL (Standard Template Library) helper methods named max_element and min_element to find the largest and smallest elements (both use O(N) Linear time for traversing through to find) and use a range-based for loop to total all elements.

### Performance Characteristics (Time Complexity)

| Operation | Time Complexity  |
| --------- | -----------------|
| Reading Input | O(N) |
| Finding max | O(N) |
| Finding min | O(N) |
| Totalling | O(N) |
| **Overall** | **O(N)** |

### Performance Characteristics (Space Complexity)
**O(N)** - for storing N values in the vector.

### Reflection
This question serves as a way of warming-up to show you how to use vectors, which are the most fundamental form of dynamic arrays in C++. In addition to this, the biggest thing I took away from working on this exercise was that the STL has built-in functions for finding your smallest/largest integers; meaning bright minds think alike therefore someone already solved that problem (i.e., using max_element/min_element saves you time during competition). I also used a long long for my summation variable in order to prevent an integer overflow from occurring in the event that N is really large.

---
## Problem 2 – Reverse the Array


### Summary of Problem
You need to reverse an array of integers stored in a vector, printing it in reverse order (starting with the last element of the array, then going down to the first).


### Explanation of Algorithm
Take an array of integers, store them in a `vector`, then traverse the vectors in reverse order from n - 1 to 0 to print each value without allocating additional space for another array.


### Time Complexity
| Operation | Complexity |
|---|---|
| Read inputs | O(n) |
| Print array backwards | O(n) |
| **Total** | **O(n)** |


### Space Complexity
**O(n)** — for storing n integers in the vector.


### Reflection on this Problem
This problem teaches about using indices to traverse vectors. You will learn that it is possible to print an entire array in reverse order without needing to allocate a new array; rather, you can just print each element using a for loop from n - 1 to 0. Avoiding unnecessary memory allocations becomes an important skill when competing at a large scale.


---

## Problem 3 — Eliminate Repeated Elements

### Description
You are given a list of N integer values, many of which may be the same (duplicates). Your goal is to output the list of unique values in numerical order. For example if the original list is `1 2 2 3 4 4 5`, your output must be `1 2 3 4 5`.

### How to Solve
Utilize the common approach of **sort → unique → erase** to achieve the desired result.
Sort the list (vector) - the sorting operation results in duplicates being placed next to one another.
Use the `std::unique` algorithm - `std::unique` collapses all consecutive duplicates in the vector and gives you an iterator to the new logical end of the vector.
Then erase from the end of the new logical end to the end of the original vector.

### Big O Analysis
| Operation | Time Complexity |
|-----------|-----------------|
| Sort      | O( N log N)     |
| unique + erase | O( N)      |
| **Total** | **O( N log N)**|

### Space Complexity
O(N) — The solution works by modifying the original vector directly and does not create an additional array or other storage mechanism.

### Reflection
This exercise has taught me the "sort → unique → erase" pattern in C++ STL. As a novice, I would have used an O(N²) nested loop to manually remove duplicates from a vector, but this three-step approach using STL is both elegant and efficient. Alternatively, you could use a `std::set` to auto-deduplicate when inserting values, which would also result in O(N log N) performance; however, this approach would consume more memory than the one provided here.

---

## Problem 4 — Sliding Window Maximum

### Problem Summary
Given an array of size N and a window of size K, slide the window from left to right and print the maximum element in each window position. E.g., `[1,3,-1,-3,5,3,6,7]` with K=3 → `3 3 5 5 6 7`.

#### Deque Algorithm Explanation
Utilize a **monotonically decreasing deque** containing indices of the values (not the values themselves). The front of the deque will always contain the maximum value for the window:
- **Expire**: Pop off the front of the deque if that index is out of the window.
- **Maintain Order**: Pop off the back of the deque until the back has a value greater than the new element.
- Add the new element at the back of the deque. Once `i >= (k - 1)`, the maximum value for the window is found at the front of the deque.


#### Time Complexity
| Operations | Time Complexity |
|---|---|
| Push to the back once for all N elements | O(N) |
| Pop from the back at most once for all N elements | O(N) |
| **Total** | **O(N)** |


> The bruteforce method requires O(N×K) checks for each sliding window.  Using a deque we significantly reduced this time complexity.


#### Space Complexity
O(K) — the deque will hold at most K indices at any time.


#### Insights
This is a well-known problem and an important problem to solve.  My initial inclination was to solve the problem using the brute force O(N×K) method.  The insight into using a monotonic queue to solve this problem allowed for a very elegant solution: we never have to reevaluate the older and smaller elements than the current element.  This method of using a monotonic deque appears again and again in many problems in competitive programming (largest rectangle in a histogram, minimum in a sliding window).  The key insight of storing indices instead of values was my "aha!" moment.

---

#### Problem 5 – Balanced Line

### Problem Summary
Implement a double-ended queue (line of people) that supports the `push_front`, `push_back`, `pop_front`, and `pop_back` operations and displays the contents of the line after each operation.

### Algorithm Explanation
We'll use C++'s `std::deque` to accomplish this as it is designed to allow O(1) insertion or removal from both ends. Each string of a requested operation will be read and used to call the corresponding function for the deque, followed by printing the contents of the deque. Popping from an empty deque will be avoided.

### Time Complexity
| Operation | Complexity |
|---|---|
| push/pop from ends | O(1) per |
| Printing deque | O(M) - (current size) |
| **Total (Q operations)** | **O(Q * M)** – (worst case) |

### Space Complexity
**O(M)** – Where M is the maximum number of elements in the deque at any point in time.

### Reflection
This is a direct application of `std::deque` and it shows how much more powerful a deque is than other collections (like regular queues and stacks), due to its O(1) access to both ends of the structure. One of the most common mistakes made by participants in these types of simulations is not checking the deque for empty before popping. This type of simulation problem occurs in virtually every programming contest (i.e., Codeforces Div. 2 A/B).

---

#### Problem 6 - K Largest Elements

## Summary of Problem
Given a collection of N numbers, find the K largest numbers and display them in descending order (ex. from [7,10,4,3,20,15] && K=3 ==> 20,15,10).

## Algorithm Explanation
Use a max-heap (priority_queue is a max-heap by default in C++):

1. Place all the N elements into the max-heap.
2. Perform exactly K times: Use the .top() to return next largest element; then use .pop() to remove that element from heap.

## Time Complexity

|Operation |   Complexity |
|-----------|-----|
|Heap Building | O(N log N) |
|K Extractions | O(K log N) |
|Overall | O(N log N) |

 ## Space Complexity

Overall space requirement is O(N) since each number in the input list will be stored in heap.

## Reflection
In competitive programming, a priority queue is one of the most powerful tools. In this particular problem, there were two potential approaches/tools available to us: max heap (simpler) versus min heap of size K (O(N log K)) which will require less memory if K is much less than N. Additionally, I noted that the syntax for creating a min heap in C++ is priority_queue, greater>() which can also be useful when using Dijkstra’s algorithm.

---

## Problem 7 — Running Median

### Problem Summary
Given a stream of N integers arriving one by one, after each insertion print the median of all integers seen so far. (HackerRank: Find the Running Median)
### Explanation of the Algorithm
There are **two heaps** that keep track of the data:
- **Lower (Max-Heap)** This contains the first half of the numbers that have been received. The maximum number in this heap (top) is the largest number in the first half of numbers.
- **Upper (Min-Heap)** This contains the second half of the numbers that have been received. The smallest number in this heap (top) is the smallest number in the second half of numbers.

The heap sizes must be equal or the lower heap must have 1 additional number compared to the upper heap.

On each insertion of a new number, insert it into the heap it belongs in, rebalance if necessary, then get the median from the tops of both heaps.

| Condition | Median Calculation |
|------|--------|
|Both heaps are equal & there is an even amount of total numbers|	(lowest of the max-heap) + (highest of min-heap) / 2 |
|Lower heap has 1 more than upper heap & there is an odd total amount of numbers|	Lowest of Max-Heap |

### Time Complexity
| Operation | Time Complexity |
|------------|-----------------|
| Pushing or popping from heap | O(log(N)) |
| **Time for N numbers** | O(N log(N)) |

> If you did brute force and sorted after each insertion, it would be O(N^2 log(N)) time.

### Space Complexity
**O(N)**. You must have all N numbers stored in the two heaps combined.

### Reflection
This problem has been one of the most difficult problems I have run into in my career. The key insight for me that I had an "aha" moment with, was splitting the data set and maintaining the split using opposing (lower being max-heap and upper being min-heap) heaps. Once I understood this was elegant and makes sense, my understanding of this method solidified. The harder pieces of this problem were rebalancing between the two heaps as well as addressing how to determine median with both an even total numbers or odd total numbers.

---

## Problem 8 — Subset Generation

### Problem Overview
Given N numbers, the goal is to list and print out every possible subset (2^N) for a given set of N items, which includes the empty set. For example: {1, 2, 3} has 8 possible subsets: { }, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, and {1,2,3}.


### Algorithm Description
We will use a technique called **bitmasking**. Starting at 0, we will go to 2^N -1 and for every number we will check the corresponding bits (0 or 1) to determine which of the original N items we can form a subset from.


```
mask = 0 (000) → {}
mask = 1 (001) → {1}
mask = 3 (011) → {1,2}
mask = 7 (111) → {1,2,3}
```


### Complexity
| Operation | Complexity |
|-----------|------------|
| Iterate through all masks | O(2^N) |
| Check for the N bits in each mask | O(N) |
| **Total** | **O(N * 2^N)** |


### Space Complexity
O(N) - We have only stored the numbers in the array, we have not created any new arrays to store subsets of numbers.


### Thoughts
The method of generating subsets using bitmasks is one of the beautiful tricks in competitive programming. The insight behind this is that the binary representation of a number naturally captures whether to include or not include all of the original N elements. This technique is generally valid only for a small number of N (e.g., N ≤ 20), since 2^20 (1 million) is typically manageable.  This technique is also a foundation for dynamic programming using bitmasks, as seen in the traveling salesman problem (TSP) and scheduling problems.

---

## Problem 9 — Count Subsets with Even Sum

#### Short Description of the Problem

You need to count how many sets of N integers contain elements that have a total of an even sum. Any time you have N (the number of integers) the total shall be 2^N (the total combinations) and those that have an even sum shall count for an even sum by having a total of 0 (your empty number). If you take the collection of integers you will need a way to represent all combinations of those integers using a mask. Thus for the set of integers {1, 2, 3} contains a total of 4 even sum categories

#### Explanation of the Algorithm

The simplest implementation of this algorithm relies heavily on the previous problem described in problem 8. Each mask defined above will include all the integers assigned to that particular mask. By having a running total when using the sum of all included integers to determine how many of the 2^N (N being the number of integers) masks created will produce an even total will help you arrive at the answer.

### Number of Subsets with an Even Sum for {1, 2, 3} = 4

- { } 0 | {2} 2 | {1, 3} 4 | {1, 2, 3} 6 | Total 4

> There is a mathematical proof to help you find the answer to the question; The answer for N >= 1 having at least one odd number in the integers provided: The answer is 2^(N-1) which means exactly half or 2^N of the total 2^N=total combinations of subsets.

### Algorithm Time Complexity

| Operation | Complexity |
|---|---|
| Iterating all Masks | O(2^N) |
| Sum for Each Mask | O(N) |
| **Total** | **O(N*2^N)** |

### Algorithm Space Complexity

**O(N)** - only the input and the loop variables will be stored in memory.

### Reflections About This Problem

This was a simple extension from the previous problem in the enumeration of bit masks, but to use the same enumeration idea to check all conditions was interesting to discover along with the mathematical proof to assist others in verifying a brute force solution much quicker while participating in a contest.

---
### Table of Summary

| num | Problem to solve | Data structure | Time complexity | Space complexity |
|-----|------------------|----------------|-----------------|------------------|
| 1 | Programming fun  | Vector         | O(n)            | O(n)             |
| 2 | Toggle back an Array | Vector     | O(n)            | O(n)             |
| 3 | Filter out duplicates from vector | Vector | O(n log n) | O(n) |
| 4 | Find max value in same size as Q (sliding window) | Deque      | O(n)            | O(K)             |
| 5 | Whether all line segments are balanced when drawn | Deque     | O(Q x M)        | O(M)             |
| 6 | Finding the k largest values | Priority Queue (Max-Heap)    | O(n log n)      | O(n)             |
| 7 | Find a running/moving median of many numbers | Priority Queue (2 Heaps) | O(n log n)      | O(n)             |
| 8 | Generating all possible subsets | Bitmask      | O(n x 2^n)     | O(n)             |
| 9 | Find count of subsets with an even total | Bitmask     | O(n x 2^n)     | O(n)             |