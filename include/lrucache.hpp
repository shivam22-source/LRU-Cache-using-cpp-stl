/* 
 * File:   lrucache.hpp
 * Author: Alexander Ponomarev
 *
 * Created on June 20, 2013, 5:09 PM
 */

#ifndef _LRUCACHE_HPP_INCLUDED_
#define	_LRUCACHE_HPP_INCLUDED_

#include <cstddef>
#include <list>
#include <stdexcept>
#include <unordered_map>

namespace cache {

template<typename key_t, typename value_t>
class lru_cache {
public:
	typedef typename std::pair<key_t, value_t> key_value_pair_t;
	typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

	explicit lru_cache(size_t max_size) :
		max_size_(max_size) {
	}
	
	void put(const key_t& key, const value_t& value) {
		if (max_size_ == 0) {
			return;
		}

		auto it = items_map_.find(key);
		if (it != items_map_.end()) {
			items_list_.splice(items_list_.begin(), items_list_, it->second);
			it->second->second = value;
			return;
		}

		items_list_.push_front(key_value_pair_t(key, value));
		items_map_[key] = items_list_.begin();
		
		if (items_map_.size() > max_size_) {
			auto last = --items_list_.end();
			items_map_.erase(last->first);
			items_list_.pop_back();
		}
	}
	
	const value_t& get(const key_t& key) {
		auto it = items_map_.find(key);
		if (it == items_map_.end()) {
			throw std::range_error("There is no such key in cache");
		} else {
			items_list_.splice(items_list_.begin(), items_list_, it->second);
			return it->second->second;
		}
	}
	
	bool exists(const key_t& key) const {
		return items_map_.find(key) != items_map_.end();
	}
	
	size_t size() const {
		return items_map_.size();
	}

	bool empty() const {
		return items_map_.empty();
	}

	size_t capacity() const {
		return max_size_;
	}
	
private:
	std::list<key_value_pair_t> items_list_;
	std::unordered_map<key_t, list_iterator_t> items_map_;
	size_t max_size_;
};

} // namespace cache

#endif	/* _LRUCACHE_HPP_INCLUDED_ */
