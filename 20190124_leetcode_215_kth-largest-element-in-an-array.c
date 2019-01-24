/*
 * 有两种做法，依具体方式而定，我们这边采用的是 quick select
 * 实现的时候， for 不应该设置  i < j 具体见下面注释
 */
#define CUTOFF (3)

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int median3(int *arr, int left, int right) {
  int mid = left + (right - left) / 2;
  if (arr[left] > arr[mid])
    swap(&arr[left], &arr[mid]);
  if (arr[mid] > arr[right])
    swap(&arr[mid], &arr[right]);
  if (arr[left] > arr[mid])
    swap(&arr[left], &arr[mid]);
  swap(&arr[mid], &arr[right - 1]);
  return arr[right - 1];
}

void insertion_sort(int *arr, int n) {
  int inserted, j;
  for (int i = 1; i < n; i++) {
    inserted = arr[i];
    for (j = i; j > 0 && arr[j - 1] > inserted; j--)
      arr[j] = arr[j - 1];
    arr[j]= inserted;
  }
}

void quick_select(int *arr, int left, int right, int k) {
  if (right - left + 1 <= CUTOFF) {
    insertion_sort(arr + left, right - left + 1);
    return;
  }

  int pivot = median3(arr, left, right);
  int i,j;
  // for (i = left + 1, j = right - 2; i < j; i++, j--) {
  // 上面是错的，因为初始状态 i >= j 但是并不满足 arr[i] 一定 > pivot 而 arr[j] < pivot，这样后面讲 pivot 跟 i 交换后， arr[i + 1] 可能还是小于  pivot
  // 这时逻辑就 break 了，考虑     findKthLargest(&(int[]){3, 1, 2, 4}, 4, 2);
  // 经过 median3 后 为 {1, 2, 3, 4}，此时 i = left + 1 为 1，而 j 为 right - 2 为 1，则 arr[i] == arr[j] == 2，此时满足  i >= j，这时交换 arr[i] 和 arr[right - 1]
  // 后变为 {1, 3, 2, 4} 破坏了原有的逻辑
  for (i = left + 1, j = right - 2;; i++, j--) {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;
    if (i >= j)
      break;
    swap(&arr[i], &arr[j]);
  }
  swap(&arr[i], &arr[right - 1]);
  if (k - 1 < i)
    quick_select(arr, left, i - 1, k);
  else if (k - 1 > i)
    quick_select(arr, i + 1, right, k);
}

bool g_invalid = false;

int findKthLargest(int* arr, int n, int k) {
  if (!arr || n < 1 || k > n || k < 1) {
    g_invalid = true;
    return 0;
  }

  quick_select(arr, 0, n - 1, n - k + 1);
  return arr[n - k];
}

