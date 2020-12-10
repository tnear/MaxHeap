// MaxHeap.h

#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>

// templated max-heap data structure implemented as an array representing visualized as a complete binary tree
// A heap works by maintaining a heap invariant:
//  - each parent is less than or equal to its both its children
//  - because the tree is complete, children can be calculated using idx*2 and idx*2 + 1
//  - similarly, parents are calculated using idx/2
template <typename T>
class MaxHeap
{
public:
	MaxHeap(const std::vector<T> &list)
        : m_vec(list), m_size(m_vec.size())
	{
        heapSort();
	}

    const std::vector<T>& getVec() const
    {
        // return sorted elements
        assert(std::is_sorted(m_vec.cbegin(), m_vec.cend()));
        return m_vec;
    }

    void heapSort()
    {
        // data can be sorted by building a heap, then "popping" one element one at a time
        // by swapping to end then "heapifying" back to a proper heap
        buildMaxHeap();

        for (int x = 0; x < static_cast<int>(m_vec.size()) - 1; ++x)
        {
            std::swap(m_vec.front(), m_vec[m_size - 1]);
            --m_size;
            maxHeapify(0);
        }
    }

private:

    std::vector<T> m_vec;
    size_t m_size = 0;

    void buildMaxHeap()
    {
        const int mid = m_vec.size() / 2;
        for (int i = mid - 1; i >= 0; --i)
        {
            maxHeapify(i);
        }
    }

	void maxHeapify(const int elementIdx)
	{
        // this maintains heap invariant by continuously swapping elements
        // until either: (1) reaching leaf, or (2) finding correct location within tree
		const size_t leftChild = getLeftChild(elementIdx);
		if (!isIndex(leftChild))
		{
			// no children
			return;
		}

        const std::size_t rightChild = getRightChild(elementIdx);

        const int maxIndex = getLargerChild(leftChild, rightChild);

        if (m_vec[elementIdx] < m_vec[maxIndex])
		{
			// swap with largest child
            std::swap(m_vec[elementIdx], m_vec[maxIndex]);

			// max_heapify on new element
            maxHeapify(maxIndex);
		}
	}

	bool isIndex(const size_t index) const
	{
		if (index > m_size - 1)
		{
			return false;
		}

		return true;
	}

    int getLargerChild(const int left, const int right) const
    {
        if (isIndex(right))
        {
            return (m_vec[left] >= m_vec[right]) ? left : right;
        }
        
        // only one child, return left
        return left;
    }
	
    // children and parent can be computed using powers of 2
    int getLeftChild(const int element) const
	{
		return (element * 2) + 1;
	}

    int getRightChild(const int element) const
	{
		return (element * 2) + 2;
	}

    int getParent(const int element) const
    {
        return (element / 2) - 1;
    }
};

void testHeap()
{
    { // empty
        std::vector<double> list = { };
        MaxHeap<double> heap{ list };
        assert(heap.getVec().empty());
    }

    { // basic integer
        std::vector<int> list = { 2, 4, 1, 3 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = { 1, 2, 3, 4 };
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 4, 14, 7, 2, 8, 1 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = { 1, 2, 4, 7, 8, 14 };
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 1 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = list;
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 1, 1 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = { 1, 1 };
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 2, 1 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = { 1, 2 };
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 1, 2, 3, 4, 5, 6 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = list;
        assert(heap.getVec() == exp);
    }

    {
        std::vector<int> list = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        MaxHeap<int> heap{ list };
        std::vector<int> exp = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        assert(heap.getVec() == exp);
    }

    { // string
        std::vector<std::string> list = { "a", "d", "c", "f", "b", "e" };
        MaxHeap<std::string> heap{ list };
        std::vector<std::string> exp = { "a", "b", "c", "d", "e", "f" };
        assert(heap.getVec() == exp);
    }
}

void TimeIt()
{
    // Timing information by sorting vectors of random data of varying sizes
    /*
    std::vector<T> list = Random::Vector(size, 1, 1000);

    Size = 100'000
    Elapsed time : 0.01 seconds.

    Size = 1'000'000
    Elapsed time : 0.146 seconds.

    Size = 10'000'000
    Elapsed time : 3.676 seconds.

    Size = 30'000'000
    Elapsed time : 11.711 seconds.
    */

    /*
    const int size = 30'000'000;
    std::vector<int> list = Random::Vector(size, 1, 1000);

    {
        Time time;
        Heap<int> h{ list };
    }
    */
}
