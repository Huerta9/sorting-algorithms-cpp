# sorting-algorithms-cpp

Three sorting algorithms and two search algorithms in C++, each instrumented to count comparisons so their growth can be measured directly. Written for a Data Structures course at Tecnológico de Monterrey.

| Algorithm | Growth |
|---|---|
| Exchange sort | O(n²) |
| Bubble sort (stops early if no swaps) | O(n²) |
| Merge sort | O(n log n) |
| Sequential search (unsorted input) | O(n) |
| Binary search (on the merge-sorted array) | O(log n) |

## Build

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sorting
```

## Input and output

Input (stdin): `n`, then `n` integers, then `b`, then `b` values to search.

Output: first line is the comparison count of exchange, bubble and merge sort. Then one line per search: `posSequential compsSequential posBinary compsBinary` (`-1` when not found).

```
$ printf "8\n5 2 9 1 7 3 8 4\n3\n7 10 1\n" | ./sorting
28 25 24
4 5 5 2
-1 8 -1 4
3 4 0 3
```

## Result: 10,000 random integers

| Exchange | Bubble | Merge |
|---|---|---|
| 49,995,000 | 49,993,170 | 133,616 |

To reproduce (Python 3, seed 1):

```bash
python3 -c "
import random
random.seed(1)
a=[random.randint(0,10**6) for _ in range(10000)]
print(10000); print(*a); print(1); print(a[5])" | ./sorting
```

Note: the counter in merge sort also counts the leftover elements copied after one half runs out, so it measures total merge steps rather than only element-to-element comparisons.
