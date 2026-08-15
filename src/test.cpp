#include "lrucache.hpp"

#include <cassert>
#include <stdexcept>

namespace {

void test_simple_put() {
    cache::lru_cache<int, int> cache_lru(1);
    assert(cache_lru.empty());

    cache_lru.put(7, 777);

    assert(!cache_lru.empty());
    assert(cache_lru.exists(7));
    assert(cache_lru.get(7) == 777);
    assert(cache_lru.size() == 1);
}

void test_missing_value() {
    cache::lru_cache<int, int> cache_lru(1);

    try {
        cache_lru.get(7);
        assert(false);
    } catch (const std::range_error&) {
        assert(true);
    }
}

void test_updates_existing_value_and_refreshes_recency() {
    cache::lru_cache<int, int> cache_lru(2);
    cache_lru.put(1, 100);
    cache_lru.put(2, 200);
    cache_lru.put(1, 111);
    cache_lru.put(3, 300);

    assert(cache_lru.exists(1));
    assert(!cache_lru.exists(2));
    assert(cache_lru.exists(3));
    assert(cache_lru.get(1) == 111);
    assert(cache_lru.size() == 2);
}

void test_zero_capacity_keeps_no_values() {
    cache::lru_cache<int, int> cache_lru(0);
    cache_lru.put(1, 100);

    assert(cache_lru.capacity() == 0);
    assert(cache_lru.size() == 0);
    assert(!cache_lru.exists(1));

    try {
        cache_lru.get(1);
        assert(false);
    } catch (const std::range_error&) {
        assert(true);
    }
}

void test_keeps_all_values_within_capacity() {
    const int num_records = 100;
    const int cache_capacity = 50;

    cache::lru_cache<int, int> cache_lru(cache_capacity);

    for (int i = 0; i < num_records; ++i) {
        cache_lru.put(i, i);
    }

    for (int i = 0; i < num_records - cache_capacity; ++i) {
        assert(!cache_lru.exists(i));
    }

    for (int i = num_records - cache_capacity; i < num_records; ++i) {
        assert(cache_lru.exists(i));
        assert(cache_lru.get(i) == i);
    }

    assert(cache_lru.size() == cache_capacity);
}

} // namespace

int main() {
    test_simple_put();
    test_missing_value();
    test_updates_existing_value_and_refreshes_recency();
    test_zero_capacity_keeps_no_values();
    test_keeps_all_values_within_capacity();
}
