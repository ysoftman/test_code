# ysoftman
# python versioni 3.x


def binarysearch(array, target):
    while True:
        length = len(array)
        print("array:", array)
        pivot = int(length / 2)
        if array[pivot] == target:
            return array[pivot]
        elif array[pivot] > target:
            array = array[:pivot]
        elif array[pivot] < target:
            array = array[pivot:]
        if length == 1:
            return -1


array = [d for d in range(1, 21)]
print(array)
print(binarysearch(array, 7))
print(binarysearch(array, 12))
