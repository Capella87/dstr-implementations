function bubbleSort(arr) {
    let size = arr.length;
    for (let i = 0; i < size - 1; i++) {
        for (let j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
            }
        }
    }

    return arr;
}

const arr = [955, 393, 719, 189, 682, 685, 825, 939, 778, 979, 10, 523];
let result = "Before: ";
for (let i in arr) {
    result = result.concat(`${arr[i]} `);
}
const rt = bubbleSort(arr);
result = result.concat('\nAfter: ');
for (let i in rt) {
    result = result.concat(`${rt[i]} `);
}
console.log(result);


/*
Output:
Before: 955 393 719 189 682 685 825 939 778 979 10 523 
After: 10 189 393 523 682 685 719 778 825 939 955 979
*/