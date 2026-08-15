# cpp-lru-cache

A small header-only LRU (Least Recently Used) cache written with only the C++ STL.

This project is intentionally simple: it uses a `std::list` to keep usage order and a
`std::unordered_map` to find list nodes in constant time. It is a good next step after
solving the common LRU Cache problem on LeetCode, because the same idea is packaged as a
reusable C++ class.

## Features

- Header-only implementation
- `put`, `get`, `exists`, `empty`, `size`, and `capacity` APIs
- O(1) average-time lookup, insert, update, and eviction
- Uses only standard C++ containers
- Includes a small assert-based test file

## How It Works

The most recently used item is kept at the front of the list. Whenever a key is read or
updated, its list node moves to the front. When the cache grows past its capacity, the
item at the back of the list is removed.

## Complexity

- `get`: O(1) average time
- `put`: O(1) average time
- Space: O(capacity)

## Example

```cpp
#include "lrucache.hpp"

#include <iostream>
#include <string>

int main() {
    cache::lru_cache<std::string, std::string> cache(3);

    cache.put("one", "first value");
    cache.put("two", "second value");

    std::cout << cache.get("two") << '\n';
}
```

## Run Tests

```sh
mkdir build
cd build
cmake ..
make check
```

You can also compile the test directly:

```sh
g++ -std=c++11 -I include src/test.cpp -o cpp-lru-cache-test
./cpp-lru-cache-test
```

## Notes

This is not meant to be a heavy production cache with expiry, persistence, or thread
safety. It is a clean STL implementation of the core LRU idea.
