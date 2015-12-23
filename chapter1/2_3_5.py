#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

def binary_search_rec(arr, v, start, end):
    if start > end:
        return None

    mid = start + ((end - start) >> 1)

    if arr[mid] == v:
        return v

    if arr[mid] > v:
        end = mid - 1
    else:
        start = mid + 1

    return binary_search_rec(arr, v, start, end)

def binary_search(arr, v):
    start = 0
    end = len(arr) - 1

    if end < 0:
        return None

    while end - start >= 0:
        mid = start + ((end - start) >> 1)
        if arr[mid] == v:
            return v
        if arr[mid] > v:
            end = mid - 1
        else:
            start = mid + 1

    return None

class Test(unittest.TestCase):

    def test_empty_arrs(self):
        provider = [
            { 'arr': [0, 1, 2, 5, 7, 10], 'v': 5, 'expected': 5 },
            { 'arr': [0, 1, 2, 5, 7, 10], 'v': 1, 'expected': 1 },
            { 'arr': [], 'v': 3, 'expected': None },
            { 'arr': [10], 'v': 10, 'expected': 10 },
            { 'arr': [-2, -1, 0, 1, 2, 5, 7, 10], 'v': -1, 'expected': -1 },
            { 'arr': [0, 1, 2, 5, 7, 10], 'v': 6, 'expected': None },
            { 'arr': [i for i in range(1, 100)], 'v': 1, 'expected': 1 },
            { 'arr': [i for i in range(1, 1000)], 'v': 761, 'expected': 761 }
        ]

        for test in provider:
            self.assertEqual(
                test['expected'],
                binary_search_rec(test['arr'], test['v'], 0, len(test['arr']) - 1)
            )

            self.assertEqual(
                test['expected'],
                binary_search(test['arr'], test['v'])
            )

if __name__ == "__main__":
    unittest.main()
