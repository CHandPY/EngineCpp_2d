#pragma once

#include <iostream>
#include <vector>

namespace engine {
	namespace core {
		template<class K, class V> class HashMap {

		public:
			HashMap() { pairs = std::vector<Pair*>(); }
			~HashMap() {}

			bool put(K key, V* value) {
				Pair* pair = new Pair(key, value);

				if (searchAndReplace(pair)) return true;

				pairs.push_back(pair);

				return false;

			};

			V* get(K key) {
				return getPr(key);
			}

		protected:
			class Pair {

			public:
				Pair(K key, V* val) : key(key), val(val) {}
				bool is(Pair* p) { return p->key == this->key; }
				bool is(K key) { return key == this->key; }
				void set(V* val) { this->val = val; }
				V* getValue() { return val; }

			private:
				K key;
				V* val;

			};

		private:
			std::vector<Pair*> pairs;

			bool searchAndReplace(Pair* pair) {

				for (int i = 0; i < pairs.size(); i++) {
					if (pairs[i]->is(pair)) {
						pairs[i]->set(pair->getValue());
						return true;
					}
				}

				return false;
			}

			V* getPr(K key) {

				for (int i = 0; i < pairs.size(); i++) {
					if (pairs[i]->is(key)) {
						return pairs[i]->getValue();
					}
				}

				return NULL;

			}

		};
	}
}