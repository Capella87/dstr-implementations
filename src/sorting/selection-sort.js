function selectionSort(arr) {
    let size = arr.length;
    for (let i = 0; i < size - 1; i++) {
        let minIdx = i;
        for (let j = i + 1; j < size; j++) {
            if (arr[minIdx] > arr[j])
                minIdx = j;
        }
        if (minIdx != i) [arr[minIdx], arr[i]] = [arr[i], arr[minIdx]];
    }

    return arr;
}

const arr = [ 10, 642, 779, 1, 674, 925, 153, 743, 264, 380, 512, 23 ];
let output = "Before: ";
for (let i in arr) {
    output = output.concat(`${arr[i]} `);
}
output = output.concat("\nAfter: ");
const result = selectionSort(arr);
for (let i in result) {
    output = output.concat(`${result[i]} `);
}

console.log(output);

/*
Output:
Before: 10 642 779 1 674 925 153 743 264 380 512 23 
After: 1 10 23 153 264 380 512 642 674 743 779 925
*/