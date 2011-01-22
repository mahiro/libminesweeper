#ifndef _MINESWEEPER_SOLVER_COMBINATION_H_
#define _MINESWEEPER_SOLVER_COMBINATION_H_

#include "common.h"
#include <set>
#include <vector>

namespace minesweeper {
	namespace solver {
		template <typename T>
		class CombinationGenerator {
			private:
				std::vector<T> items;
				std::size_t numItems;
				std::size_t minK, maxK;
				
				size_t k;
				std::size_t * indices;
				
				std::set<T> result;
				
				void refreshIndices();
				bool advance(std::size_t i);
				
			public:
				explicit CombinationGenerator(const std::set<T> & input, std::size_t _minK, std::size_t _maxK);
				virtual ~CombinationGenerator();
				
				const std::set<T> & next();
				
				bool hasNext() const {
					return k <= maxK;
				}
		};
		
		template <typename T>
		CombinationGenerator<T>::CombinationGenerator(const std::set<T> & input, std::size_t _minK, std::size_t _maxK) :
					items(input.begin(), input.end()), minK(_minK), maxK(_maxK), k(_minK), result() {
			numItems = input.size();
			
			if (maxK > numItems) {
				maxK = numItems;
			}
			
			refreshIndices();
		}
		
		template <typename T>
		CombinationGenerator<T>::~CombinationGenerator() {
			delete indices;
		}
		
		template <typename T>
		void CombinationGenerator<T>::refreshIndices() {
			indices = new std::size_t[k];
			
			for (std::size_t i = 0; i < k; i++) {
				indices[i] = i;
			}
		}
		
		template <typename T>
		const std::set<T> & CombinationGenerator<T>::next() {
			result.clear();
			
			for (std::size_t i = 0; i < k; i++) {
				result.insert(items[indices[i]]);
			}
			
			if (k == 0 || !advance(0)) {
				k++;
				
				if (k <= maxK) {
					delete indices;
					refreshIndices();
				}
			}
			
			return result;
		}
		
		template <typename T>
		bool CombinationGenerator<T>::advance(size_t i) {
			if (indices[i] + (k - i) >= numItems) {
				return false;
			}
			
			if (i < k - 1 && advance(i + 1)) {
				return true;
			}
			
			indices[i]++;
			
			for (std::size_t j = i + 1; j < k; j++) {
				indices[j] = indices[j - 1] + 1;
			}
			
			return true;
		}
	}
}

#endif
