import math

def mergeSortNoRecursion(arr):
    orig_id = id(arr)
    temp = [None] * len(arr)

    for block_length in [2**n for n in range(1, math.ceil(math.log2(len(arr)))+1)]:# 2,4,8,...
        for idx in range(0, len(arr), block_length):
            idx_l = idx
            idx_r = idx + (block_length//2)
            stop_l = idx_r
            stop_r = idx + block_length
            if stop_r > len(arr): stop_r = len(arr)

            temp_pos = idx
            while idx_l < stop_l and idx_r < stop_r:
                if arr[idx_l] > arr[idx_r]:
                    temp[temp_pos] = arr[idx_r]
                    idx_r += 1
                else:
                    temp[temp_pos] = arr[idx_l]
                    idx_l += 1
                temp_pos += 1
            # add remained
            if idx_l < stop_l:
                temp[temp_pos:temp_pos+stop_l-idx_l] = arr[idx_l:stop_l]
            if idx_r < stop_r:
                temp[temp_pos:temp_pos+stop_r-idx_r] = arr[idx_r:stop_r]

        temp,arr = arr,temp

    return arr
