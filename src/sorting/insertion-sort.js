function insertionSort(arr) {
    let size = arr.length;

    for (let i = 1; i < size; i++) {
        let temp = arr[i];
        let j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }

    return arr;
}

const arr = [ 242, 889, 912, 916, 172, 785, 40, 431, 996, 721, 567, 731 ];
let output = "Before: ";

for (let i in arr) {
    output = output.concat(`${arr[i]} `);
}
output = output.concat("\nAfter: ");
const rt = insertionSort(arr);
for (let i in rt) {
    output = output.concat(`${rt[i]} `);
}
console.log(output);

/*
Output:
Before: 242 889 912 916 172 785 40 431 996 721 567 731 
After: 40 172 242 431 567 721 731 785 889 912 916 996
*/