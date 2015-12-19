#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

def add_binary_nor(a, b):
    length = len(a)
    if not length or length != len(b):
        return False

    c = [0] * (length + 1)
    carry = 0
    for i in range(length - 1, -1, -1):
        c[i + 1] = (a[i] + b[i] + carry) % 2
        carry = (a[i] + b[i] + carry) / 2
    c[0] = carry

    return c

class Test(unittest.TestCase):

    def test_empty_arrs(self):
        provider = [
            { 'a': [], 'b': [], 'expected': False },
            { 'a': [1], 'b': [0], 'expected': [0, 1] },
            { 'a': [1, 1], 'b': [0, 0], 'expected': [0, 1, 1] },
            { 'a': [1, 1], 'b': [1, 1], 'expected': [1, 1, 0] },
            { 'a': [1, 0], 'b': [1, 0], 'expected': [1, 0, 0] }
        ]
        for test in provider:
            self.assertEqual(
                test['expected'], add_binary_nor(test['a'], test['b'])
            )

if __name__ == "__main__":
    unittest.main()
