jest.dontMock('../../sort/insertion_sort');
jest.dontMock('../../sort/merge_sort');
jest.dontMock('../../sort/selection_sort');

var sortAlgoSet, addAlgoToArrProt, sortHelper;

sortAlgoSet = {
    insertionSort: require('../../sort/insertion_sort'),
    selectionSort: require('../../sort/selection_sort'),
    mergeSort: require('../../sort/merge_sort')
};

addAlgoToArrProt = function(algo, impl) {
    Array.prototype[algo] = function(compare) {
        return impl(this, compare);
    };
};

(function() {
    for (var algo in sortAlgoSet) {
         addAlgoToArrProt(algo, sortAlgoSet[algo]);
    }
})();

describe('insertion sort test', function() {

    it('test suite', function() {
        var provider = [
            { arr: [], expected: [] },
            { arr: [1], expected: [1] },
            { arr: [2, 1], expected: [1, 2] },
            { arr: [3, 5, 1, 4, 0], expected: [0, 1, 3, 4, 5] },
        ], i, len, test, actual;

        for (i = 0, len = provider.length; i < len; ++i) {
            test = provider[i];
            for (var algo in sortAlgoSet) {
                actual = test.arr[algo]();
                expect(actual).toEqual(test.expected);
            }
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
            for (var algo in sortAlgoSet) {
                actual = test.arr[algo](test.comparator);
                expect(actual).toEqual(test.expected);
            }
        }
    });
});
