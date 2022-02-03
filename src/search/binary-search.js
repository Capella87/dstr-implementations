function binarySearch(arr, left, right, target) {
    if (left > right) return -1;
    
    let mid = Math.floor((left + right) / 2);
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target)
        return binarySearch(arr, mid + 1, right, target);
    else return binarySearch(arr, left, mid - 1, target);
}

const arr = [218, 177, 381, 340, 678, 8, 277, 865, 112, 655, 1];
var result = "";

arr.sort((a, b) => a - b);
for (var i in arr)
    result = result.concat(String(arr[i]) + ' ');
console.log(binarySearch(arr, 0, arr.length - 1, 218));