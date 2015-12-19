var defaultCompare = function(a, b) { 
    return a - b;
};

module.exports = function(arr, compare) {
    var i, len, j, minIdx;

    if (typeof compare !== 'function') {
        compare = defaultCompare;
    }

    for (i = 0, len = arr.length; i < len - 1; ++i) {
        minIdx = i;
        for (j = i + 1; j < len; ++j) {
            if (compare(arr[minIdx], arr[j]) > 0) {
                minIdx = j;
            }
        }
        if (i !== minIdx) {
            arr[i] = [arr[minIdx], arr[minIdx] = arr[i]][0];
        }
    }

    return arr;
};
