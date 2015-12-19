var defaultCompare, merge;

defaultCompare = function(a, b) {
    return a - b;
};

merge = function(arr, p, q, r, compare) {
    var left = [], right = [], i, j, k, n1, n2;

    for (i = 0, len = (q - p + 1); i < len; ++i) {
        left.push(arr[p + i]);
    }

    for (i = 0, len = (r - q); i < len; ++i) {
        right.push(arr[q + i + 1]);
    }

    for (k = p, i = 0, j = 0; k <= r; ++k) {
        if (j >= (r - q) || (i < (q - p + 1) && compare(left[i], right[j]) < 0)) {
            arr[k] = left[i];
            ++i;
        } else {
            arr[k] = right[j];
            ++j;
        }
    }

    return arr;
};

module.exports = function mergeSort(arr, compare, start, end) {
    if (typeof(compare) !== 'function') {
        compare = defaultCompare;
    }

    if (start === undefined || end === undefined) {
        start = 0;
        end = arr.length - 1;
    }
    if (end - start <= 0) {
        return arr;
    }

    var middle = Math.floor((start + end) / 2);
    arr = mergeSort(arr, compare, start, middle);
    arr = mergeSort(arr, compare, middle + 1, end);
    return merge(arr, start, middle, end, compare);
};
