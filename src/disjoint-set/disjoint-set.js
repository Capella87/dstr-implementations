function union_set(arr, a, b) {
    if (a >= arr.length || b >= arr.length) return;
    let a_root = find_set(arr, a);
    let b_root = find_set(arr, b);

    if (a_root == b_root) return;

    if (arr[b_root] < arr[a_root]) {
        arr[a_root] = b_root;
    }
    else {
        if (arr[a_root] == arr[b_root])
            arr[a_root]--;
        arr[b_root] = a_root;
    }
}

function find_set(arr, target) {
    if (target >= arr.length) return -1;
    if (arr[target] < 0) return target;
    else return arr[target] = find_set(arr, arr[target]);
}

function get_root(arr, target) {
    let rt = find_set(arr, target);
    if (rt == -1) return;

    console.log(`Set ${target}'s root is ${rt}.`);
}

const arr = [];
for (let i = 0; i < 100; i++) {
    arr.push(-1);
}

get_root(arr, 1);
union_set(arr, 1, 2);
union_set(arr, 1, 3);
union_set(arr, 1, 4);
get_root(arr, 2);
get_root(arr, 4);
union_set(arr, 5, 6);
get_root(arr, 6);
union_set(arr, 1, 5);
get_root(arr, 1);
get_root(arr, 5);

/*
Output:
Set 1's root is 1.
Set 2's root is 1.
Set 4's root is 1.
Set 6's root is 5.
Set 1's root is 1.
Set 5's root is 1.
*/