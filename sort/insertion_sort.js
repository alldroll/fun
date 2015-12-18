var defaultCompare = function(a, b) { 
    return a - b;
};

module.exports = function(arr, compare) {
    var i, len, j, key;

    if (typeof compare !== 'function') {
        compare = defaultCompare;
    }

    for (i = 1, len = arr.length; i < len; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && compare(key, arr[j]) < 0) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }

    return arr;
};
