def delayedReplacementSort(unsorted):
    for i in range(len(unsorted)-1):
        lowest = i
        for n in range(i+1, len(unsorted)):
            if unsorted[lowest] > unsorted[n]:
                lowest = n
        if lowest != i:
            unsorted[i], unsorted[lowest] = unsorted[lowest], unsorted[i]
