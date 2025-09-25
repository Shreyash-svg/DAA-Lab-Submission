#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxCrossingSum(int arr[], int l, int m, int h, int constraint, int *start, int *end) {
    int sum = 0, left_sum = INT_MIN, i;
    int temp_start = m;
    for (i = m; i >= l; i--) {
        sum += arr[i];
        if (sum <= constraint && sum > left_sum) {
            left_sum = sum;
            temp_start = i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN, temp_end = m + 1;
    for (i = m + 1; i <= h; i++) {
        sum += arr[i];
        if (left_sum != INT_MIN && left_sum + sum <= constraint && left_sum + sum > right_sum) {
            right_sum = left_sum + sum;
            temp_end = i;
        }
    }

    if (right_sum == INT_MIN && left_sum != INT_MIN) {
        *start = temp_start;
        *end = m;
        return left_sum;
    }

    if (right_sum != INT_MIN) {
        *start = temp_start;
        *end = temp_end;
        return right_sum;
    }

    return INT_MIN;
}

int maxSubArraySum(int arr[], int l, int h, int constraint, int *start, int *end) {
    if (l == h) {
        if (arr[l] <= constraint) {
            *start = *end = l;
            return arr[l];
        } else {
            return INT_MIN; // not feasible
        }
    }

    int m = (l + h) / 2;
    int s1, e1, s2, e2, s3, e3;

    int left_sum = maxSubArraySum(arr, l, m, constraint, &s1, &e1);
    int right_sum = maxSubArraySum(arr, m + 1, h, constraint, &s2, &e2);
    int cross_sum = maxCrossingSum(arr, l, m, h, constraint, &s3, &e3);

    int max_sum = left_sum;
    *start = s1; *end = e1;

    if (right_sum > max_sum) {
        max_sum = right_sum;
        *start = s2; *end = e2;
    }
    if (cross_sum > max_sum) {
        max_sum = cross_sum;
        *start = s3; *end = e3;
    }

    return max_sum;
}

int main() {
    int n, constraint;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter resource constraint: ");
    scanf("%d", &constraint);

    int start = -1, end = -1;
    int max_sum = maxSubArraySum(arr, 0, n - 1, constraint, &start, &end);

    if (max_sum == INT_MIN) {
        printf("No feasible subarray found.\n");
    } else {
        printf("Maximum subarray sum = %d\n", max_sum);
        printf("Subarray: [ ");
        for (int i = start; i <= end; i++) {
            printf("%d ", arr[i]);
        }
        printf("]\n");
    }

    return 0;
}

