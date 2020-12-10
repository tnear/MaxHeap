# MaxHeap

* templated max-heap data structure implemented as an array representing visualized as a complete binary tree
* A heap works by maintaining a heap invariant:
    * each parent is less than or equal to its both its children
    * because the tree is complete, children can be calculated using idx*2 and idx*2 + 1
    * similarly, parents are calculated using idx/2
