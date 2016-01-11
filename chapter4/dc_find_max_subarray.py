#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

M_INF = -float('inf')

def find_max_subarray(arr, low, high):
    if low == high:
        return (low, high, arr[low])

    mid = (low + high) >> 1

    (l_low, l_high, l_sum) = find_max_subarray(arr, low, mid)
    (r_low, r_high, r_sum) = find_max_subarray(arr, mid + 1, high)
    (c_low, c_high, c_sum) = find_cross_subarray(arr, low, mid, high)

    if l_sum >= r_sum and l_sum >= c_sum:
        return (l_low, l_high, l_sum)

    if r_sum >= l_sum and r_sum >= c_sum:
        return (r_low, r_high, r_sum)

    return (c_low, c_high, c_sum)

def find_cross_subarray(arr, low, mid, high):
    tmp = 0
    left_sum = M_INF
    s_low = mid
    for i in range(mid, low - 1, -1):
        tmp = tmp + arr[i]
        if tmp > left_sum:
            left_sum = tmp
            s_low = i

    tmp = 0
    right_sum = M_INF
    s_high = mid + 1
    for j in range(mid + 1, high + 1):
        tmp = tmp + arr[j]
        if tmp > right_sum:
            right_sum = tmp
            s_high = j

    return (s_low, s_high, left_sum + right_sum)

def rude_find_max_subarray(arr):
    n = len(arr)
    max_sum = M_INF
    low, high = 0, 0

    for i in range(n):
        c_sum = 0
        for j in range(i, n):
            c_sum = c_sum + arr[j]
            if max_sum < c_sum:
                max_sum = c_sum
                low, high = i, j

    return (low, high, max_sum)

def linear_find_max_subarray(arr):
    n = len(arr)
    max_sum = M_INF
    c_sum, min_sum = 0, 0
    low, high = 0, 0
    min_pos = -1

    for j in range(n):
        c_sum = c_sum + arr[j] # A[1, j + 1] = A[1, j] + A[j + 1]
        """
        we have to find max subarray in A[1, j + 1]
        it could be subarray in A[1, j] or subarray A[i, j + 1], i in [0, j + 1]

        how to find i ? we just find min subarray in A[0, j - 1]

        """
        r_sum = c_sum - min_sum

        if r_sum > max_sum:
            max_sum = r_sum
            low, high = min_pos + 1, j

        if c_sum < min_sum:
            min_sum = c_sum
            min_pos = j

    return (low, high, max_sum)

class Test(unittest.TestCase):

    def test_empty_arrs(self):
        provider = [
            {
                'arr': [
                    13, -3, -25, 20, -3, -16, -23, 18, 20,
                    -7, 12, -5, -22, 15, -4, 7
                ],
                'expected': (7, 10, 43)
            },
            { 'arr': [1, -4, 3, -4], 'expected': (2, 2, 3) },
            { 'arr': [i for i in range(1, 11)], 'expected': (0, 9, 55) },
            { 'arr': [-1, -2, -3, -4], 'expected': (0, 0, -1) },
            { 'arr': [-2, -3, -1, -4], 'expected': (2, 2, -1) }
        ]

        for test in provider:
            arr = test['arr']

            self.assertEqual(
                test['expected'], find_max_subarray(arr, 0, len(arr) - 1)
            )

            self.assertEqual(test['expected'], rude_find_max_subarray(arr))

            self.assertEqual(test['expected'], linear_find_max_subarray(arr))

if __name__ == "__main__":
    unittest.main()
