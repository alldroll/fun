var defaultCompare, sort;

defaultCompare = function(a, b) { 
    return a - b;
};

sort = function recSort(arr, compare, i) {
    var j, key;

    if (i < 0) {
        return arr;
    }

    recSort(arr, compare, i - 1);

    key = arr[i];
    j = i - 1;
    while (j >= 0 && compare(key, arr[j]) < 0) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = key;

    return arr;
};

module.exports = function(arr, compare) {
    if (typeof compare !== 'function') {
        compare = defaultCompare;
    }
    return sort(arr, compare, arr.length - 1);
};
