from bubble import bubbleSort
from delayed_replacement import delayedReplacementSort
from merge_sort_no_recursion import mergeSortNoRecursion
import random

def checkListSorted(arr):
    for i in range(1, len(arr)):
        if arr[i] < arr[i-1]:
            return False
    return True

def checkIfListsSame(arr1, arr2):
    print("lists are same" if (arr1 == arr2) else "lists are different")

def checkSortingAlgorithm(algorithm, list_to_sort):
    res = algorithm(list_to_sort)
    if res is not None:
        # update values of list_to_sort with returned data
        # just for checking types of sort function which return new lists
        list_to_sort[:] = res[:]

    is_sorted = checkListSorted(list_to_sort)
    print("{}: list is {}".format(algorithm.__name__, "sorted" if is_sorted else "not sorted"))

if __name__ == "__main__":
    N_ELEMENTS = 2000
    original_list = [random.randrange(1, N_ELEMENTS) for _ in range(N_ELEMENTS)]

    for_bubble_sort = original_list[:]
    for_repl_delayed_sort = original_list[:]
    for_merge_sort = original_list[:]

    checkSortingAlgorithm(bubbleSort, for_bubble_sort)
    checkSortingAlgorithm(delayedReplacementSort, for_repl_delayed_sort)
    checkSortingAlgorithm(mergeSortNoRecursion, for_merge_sort)

    checkIfListsSame(for_bubble_sort, for_repl_delayed_sort)
    checkIfListsSame(for_merge_sort, for_repl_delayed_sort)
