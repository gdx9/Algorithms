from bubble import bubbleSort
from delayed_replacement import delayedReplacementSort
import random

def checkListSorted(arr):
    for i in range(1, len(arr)):
        if arr[i] < arr[i-1]:
            return False
    return True

def checkIfListsSame(arr1, arr2):
    for (el1, el2) in zip(arr1, arr2):
        if el1 != el2:
            return False
    return True

def checkSortingAlgorithm(algorithm, list_to_sort):
    algorithm(list_to_sort)
    is_sorted = checkListSorted(list_to_sort)
    print("{}: list is {}".format(algorithm.__name__, "sorted" if is_sorted else "not sorted"))

if __name__ == "__main__":
    N_ELEMENTS = 100
    original_list = [random.randrange(1, N_ELEMENTS) for _ in range(N_ELEMENTS)]


    for_bubble_sort = original_list[:]
    for_repl_delayed_sort = original_list[:]

    checkSortingAlgorithm(bubbleSort, for_bubble_sort)
    checkSortingAlgorithm(delayedReplacementSort, for_repl_delayed_sort)

    are_same = checkIfListsSame(for_bubble_sort, for_repl_delayed_sort)
    print("lists are same" if are_same else "lists are different")
