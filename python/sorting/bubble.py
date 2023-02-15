def bubbleSort(unsorted):
    swaped = True
    while swaped:
        swaped = False
        for n in range(len(unsorted)-1):
            if unsorted[n] > unsorted[n+1]:
                swaped = True
                unsorted[n], unsorted[n+1] = unsorted[n+1], unsorted[n]
                
