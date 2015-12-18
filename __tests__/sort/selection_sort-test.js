jest.dontMock('../../sort/selection_sort');
var selectionSort = require('../../sort/selection_sort');

Array.prototype.selectionSort = function(compare) {
    return selectionSort(this, compare);
};

describe('selection sort test', function() {
    it('test suite', function() {
        var provider = [
            { arr: [], expected: [] },
            { arr: [1], expected: [1] },
            { arr: [2, 1], expected: [1, 2] },
            { arr: [3, 5, 1, 4, 0], expected: [0, 1, 3, 4, 5] },
            { arr: [], expected: [] }
        ], i, len, test, actual;

        for (i = 0, len = provider.length; i < len; ++i) {
            test = provider[i];
            actual = test.arr.selectionSort();
            expect(actual).toEqual(test.expected);
        }
    });

    it('comparator test suite', function() {
        var provider = [
            { arr: [2, 1], expected: [1, 2], comparator: null },
            {
                arr: [3, 5, 1, 4, 0],
                expected: [5, 4, 3, 1, 0],
                comparator: function(a, b) { return b - a; } 
            },
            {
                arr: ['test', 't', 'longlong', 'pa'],
                expected: ['t', 'pa', 'test', 'longlong'],
                comparator: function(a, b) { return a.length - b.length; }
            },
        ], i, len, test, actual;

        for (i = 0, len = provider.length; i < len; ++i) {
            test = provider[i];
            actual = test.arr.selectionSort(test.comparator);
            expect(actual).toEqual(test.expected);
        }
    });
});
