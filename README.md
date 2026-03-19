# CP Practicals SS26 — Practical 1: Analysis Report

## Problem 1 — Dynamic Array Basics

### Problem Summary
Read N integers into a dynamic container and compute the maximum element, minimum element, and sum of all elements.

### Algorithm Explanation
Populate a `vector<int>` of size N. Use STL helpers `max_element` and `min_element` for max/min (linear scan internally), and a range-based for loop to accumulate the sum.

### Time Complexity
| Operation | Complexity |
|---|---|
| Reading input | O(N) |
| Finding max/min | O(N) each |
| Computing sum | O(N) |
| **Overall** | **O(N)** |

### Space Complexity
**O(N)** — for storing N elements in the vector.

### Reflection
This problem is a warm-up to get comfortable with `vector`, the fundamental dynamic array in C++. The key takeaway is that STL provides ready-made functions like `max_element` and `min_element` that save time during contests. I also used `long long` for the sum to avoid integer overflow when N is large.

---

## Problem 2 — Reverse the Array

### Problem Summary
Given N integers stored in a vector, print all elements in reverse order (last element first, first element last).

### Algorithm Explanation
Read N integers into a `vector<int>`, then traverse from index `n-1` down to `0`, printing each element. No second array is needed — a single reverse loop is sufficient.

### Time Complexity
| Operation | Complexity |
|---|---|
| Reading input | O(N) |
| Reverse print | O(N) |
| **Overall** | **O(N)** |

### Space Complexity
**O(N)** — for storing N elements in the vector.

### Reflection
This problem reinforces index-based traversal of vectors. The important insight is that printing in reverse does NOT require creating a second array — a simple loop from `n-1` to `0` is sufficient. This teaches the habit of avoiding unnecessary memory allocation, which matters at scale in competitive programming.

---

## Problem 3 — Remove Duplicates

### Problem Summary
Given N integers (possibly with duplicates), output only the unique values in sorted order. For example, `1 2 2 3 4 4 5` → `1 2 3 4 5`.

### Algorithm Explanation
Use the classic **sort → unique → erase** idiom:
1. Sort the vector — brings all duplicates adjacent.
2. Apply `std::unique` — collapses consecutive duplicates, returns iterator to new logical end.
3. Erase leftover elements after the iterator.

### Time Complexity
| Operation | Complexity |
|---|---|
| Sorting | O(N log N) |
| unique + erase | O(N) |
| **Overall** | **O(N log N)** |

### Space Complexity
**O(N)** — in-place modification, no extra array needed.

### Reflection
This problem taught me the classic `sort → unique → erase` idiom in C++ STL. A beginner might use a nested loop O(N²) to manually remove duplicates, but this clean three-step approach is both elegant and efficient. An alternative is using `std::set<int>` which auto-deduplicates on insertion — also O(N log N) but uses extra space.

---

## Problem 4 — Sliding Window Maximum

### Problem Summary
Given an array of size N and a window of size K, slide the window from left to right and print the maximum element in each window position. E.g., `[1,3,-1,-3,5,3,6,7]` with K=3 → `3 3 5 5 6 7`.

### Algorithm Explanation
Use a **monotonic deque** storing array indices (not values). The deque maintains decreasing order of values front to back:
- **Expire**: Pop from front if index is outside the current window.
- **Maintain order**: Pop from back while `arr[dq.back()] <= arr[i]` — smaller/older elements are useless.
- Push current index to back. Once `i >= k-1`, `arr[dq.front()]` = window maximum.

### Time Complexity
| Operation | Complexity |
|---|---|
| Each element pushed once | O(N) |
| Each element popped at most once | O(N) |
| **Overall** | **O(N)** |

> Brute force (check every window) = O(N×K). The deque approach is a major improvement.

### Space Complexity
**O(K)** — the deque holds at most K indices at any time.

### Reflection
This is a classic and important problem. My initial instinct was brute force O(N×K), but the deque insight is elegant: we never need to reconsider elements that are both older AND smaller than the current element. This monotonic deque pattern repeats across many competitive programming problems (largest rectangle in histogram, minimum in sliding window). Understanding why we store indices and not values was the key aha-moment.

---

## Problem 5 — Balanced Line Problem

### Problem Summary
Simulate a double-ended queue (line of people) supporting `push_front`, `push_back`, `pop_front`, and `pop_back`. After each operation, print the current contents of the line.

### Algorithm Explanation
Use C++ `std::deque<int>` which natively supports O(1) insertions and deletions at both ends. Read each operation string, execute the corresponding deque method, and print the full deque contents after each operation. Guard against popping from an empty deque.

### Time Complexity
| Operation | Complexity |
|---|---|
| push/pop at ends | O(1) per operation |
| Printing deque | O(M) where M = current size |
| **Overall (Q ops)** | **O(Q × M)** worst case |

### Space Complexity
**O(M)** — where M is the maximum number of elements in the deque at any time.

### Reflection
This problem is a direct application of `std::deque` and demonstrates why a deque is more powerful than a regular queue or stack — it supports both-end access in O(1). A common mistake is forgetting to check for an empty deque before popping. This type of simulation problem is very common in contests (e.g., Codeforces Div. 2 A/B level).

---

## Problem 6 — K Largest Elements

### Problem Summary
Given N numbers, find and print the K largest numbers in descending order. E.g., from `[7, 10, 4, 3, 20, 15]` with K=3 → `20 15 10`.

### Algorithm Explanation
Use a **max-heap** (`priority_queue<int>` — max-heap by default in C++):
1. Push all N elements into the max-heap.
2. Call `.top()` and `.pop()` exactly K times — each extraction yields the next largest element.

### Time Complexity
| Operation | Complexity |
|---|---|
| Building heap | O(N log N) |
| K extractions | O(K log N) |
| **Overall** | **O(N log N)** |

### Space Complexity
**O(N)** — all elements stored in the heap.

### Reflection
Priority queues are one of the most powerful tools in competitive programming. This problem showed me the two strategies: max-heap for simplicity, or min-heap-of-size-K (O(N log K)) for memory efficiency when K is small. I also noted that `priority_queue<int, vector<int>, greater<int>>` creates a **min-heap** in C++, which is useful for Dijkstra's algorithm.

---

## Problem 7 — Running Median

### Problem Summary
Given a stream of N integers arriving one by one, after each insertion print the median of all integers seen so far. (HackerRank: Find the Running Median)

### Algorithm Explanation
Maintain **two heaps** partitioning all elements:
- **`lower` (max-heap)**: stores the smaller half. Top = largest of smaller half.
- **`upper` (min-heap)**: stores the larger half. Top = smallest of larger half.

**Invariant:** `lower.size() == upper.size()` OR `lower.size() == upper.size() + 1`

For each new element: insert into the correct heap, rebalance if the size invariant breaks, then read the median from the top(s).

| Condition | Median |
|---|---|
| Sizes equal (even total) | `(lower.top() + upper.top()) / 2.0` |
| Lower has one extra (odd total) | `lower.top()` |

### Time Complexity
| Operation | Complexity |
|---|---|
| Heap push/pop per element | O(log N) |
| **Overall for N elements** | **O(N log N)** |

> Brute force (sort after every insertion) = O(N² log N).

### Space Complexity
**O(N)** — all N elements stored across both heaps.

### Reflection
This is a classic hard problem. The key insight — splitting the dataset into two halves maintained by opposing heaps — was not intuitive at first. Once understood, it is elegant: the median always sits at the boundary between the two heaps. The tricky parts were the rebalancing step and correctly handling even vs odd total counts.

---

## Problem 8 — Subset Generation

### Problem Summary
Given a set of N numbers, enumerate and print all 2^N possible subsets including the empty set. For `{1, 2, 3}` there are 8 subsets from `{}` to `{1, 2, 3}`.

### Algorithm Explanation
Use the **bitmask technique**: iterate `mask` from `0` to `2^N - 1`. For each mask, the i-th bit being set (`mask & (1 << i) != 0`) means `arr[i]` is included in the subset.

```
mask = 0 (000) → {}
mask = 1 (001) → {1}
mask = 3 (011) → {1, 2}
mask = 7 (111) → {1, 2, 3}
```

### Time Complexity
| Operation | Complexity |
|---|---|
| Iterating all masks | O(2^N) |
| Checking N bits per mask | O(N) |
| **Overall** | **O(N × 2^N)** |

### Space Complexity
**O(N)** — only the input array. No extra storage for subsets.

### Reflection
Bitmask enumeration is one of the most elegant tricks in competitive programming. The key insight is that binary representation naturally encodes "include or exclude" for each element. This is applicable for N ≤ 20 typically (2^20 ≈ 1 million is manageable). This technique forms the foundation of bitmask DP, used in TSP and scheduling problems.

---

## Problem 9 — Count Subsets with Even Sum

### Problem Summary
Given N numbers, count how many of the 2^N subsets have an even sum (including the empty subset, sum = 0). For `{1, 2, 3}` the answer is 4.

### Algorithm Explanation
Build directly on Problem 8's bitmask enumeration: for each mask, compute the sum of included elements, and increment a counter if `sum % 2 == 0`.

**Verified subsets for `{1, 2, 3}` with even sum:**
- `{}` → 0 ✓ | `{2}` → 2 ✓ | `{1,3}` → 4 ✓ | `{1,2,3}` → 6 ✓ → **Total = 4**

> **Mathematical shortcut:** The answer is always `2^(N-1)` for N ≥ 1 when the set contains at least one odd number — exactly half of all subsets have even sum.

### Time Complexity
| Operation | Complexity |
|---|---|
| Iterating all masks | O(2^N) |
| Computing sum per mask | O(N) |
| **Overall** | **O(N × 2^N)** |

### Space Complexity
**O(N)** — only input array and loop variables.

### Reflection
This problem is a direct extension of Problem 8, showing how bitmask enumeration can be augmented with a condition check. I also discovered the mathematical shortcut (answer = 2^(N-1)) which is a great competitive programming trick to verify brute-force answers quickly during a contest.

---

## Summary Table

| # | Problem | Data Structure | Time Complexity | Space Complexity |
|---|---|---|---|---|
| 1 | Dynamic Array Basics | Vector | O(N) | O(N) |
| 2 | Reverse the Array | Vector | O(N) | O(N) |
| 3 | Remove Duplicates | Vector | O(N log N) | O(N) |
| 4 | Sliding Window Maximum | Deque | O(N) | O(K) |
| 5 | Balanced Line | Deque | O(Q × M) | O(M) |
| 6 | K Largest Elements | Priority Queue (Max-Heap) | O(N log N) | O(N) |
| 7 | Running Median | Priority Queue (Two Heaps) | O(N log N) | O(N) |
| 8 | Subset Generation | Bitmask | O(N × 2^N) | O(N) |
| 9 | Count Subsets Even Sum | Bitmask | O(N × 2^N) | O(N) |