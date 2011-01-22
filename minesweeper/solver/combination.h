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
				int numItems;
				int minK, maxK;
				
				int k;
				int * indices;
				
				std::set<T> result;
				
				void refreshIndices();
				bool advance(int i);
				
			public:
				explicit CombinationGenerator(const std::set<T> & input, int _minK, int _maxK);
				virtual ~CombinationGenerator();
				
				const std::set<T> & next();
				
				bool hasNext() const {
					return k <= maxK;
				}
				
		};
		
		template <typename T>
		CombinationGenerator<T>::CombinationGenerator(const std::set<T> & input, int _minK, int _maxK) :
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
			indices = new int[k];
			
			for (int i = 0; i < k; i++) {
				indices[i] = i;
			}
		}
		
		template <typename T>
		const std::set<T> & CombinationGenerator<T>::next() {
			result.clear();
			
			for (int i = 0; i < k; i++) {
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
		bool CombinationGenerator<T>::advance(int i) {
			if (indices[i] + (k - i) >= numItems) {
				return false;
			}
			
			if (i < k - 1 && advance(i + 1)) {
				return true;
			}
			
			indices[i]++;
			
			for (int j = i + 1; j < k; j++) {
				indices[j] = indices[j - 1] + 1;
			}
			
			return true;
		}
	}
}

#endif
