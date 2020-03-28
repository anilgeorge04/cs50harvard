// Merge Sort Algorithm
// Prompts the user to enter the count and value of numbers to sort
// Performs Merge Sort with a recursive function and presents a new sorted array

#include <stdio.h>
#include <cs50.h>

void mergesort(int arr[], int low, int high);
void merge(int low, int mid, int high, int arr[]);

int main(void)
{
    int num = get_int("How many numbers would you like to sort? ");
    int a[num];
    int i;
    printf("Enter the array of numbers below (in any order).\n");
    for (i = 0; i < num; i++)
        a[i] = get_int("Num %i: ", i + 1);

    mergesort(a, 0, num-1);

    printf("Sorted array of numbers below.\n");
    for (i = 0; i < num; i++)
        printf("Num %i: %i\n", i + 1, a[i]);
}

// Recursive sort by dividing array into Left & Right sublists, sorting them and then merging them
void mergesort(int a[], int low, int high)
{
    // Base Condition to exit when only 1 element in sublist
    if (low >= high)
        return;

    int mid = (low + (high-1)) / 2;

    mergesort(a, low, mid);
    mergesort(a, mid+1, high);
    merge(low, mid, high, a);
}

void merge(int low, int mid, int high, int a[])
{
    int i, j;
    // Create Left and Right Sublists
    int l_len = mid - low + 1, r_len = high - mid;
    int left[l_len], right[r_len];

    // Copy data to temp Left & Right Sublists
    for (i = 0; i < l_len ; i++)
        left[i] = a[low + i];
    for (j = 0; j < r_len; j++)
        right[j] = a[mid + 1 + j];

    // Initialize index for each array
    i = 0; // Left subarray
    j = 0; // Right subarray
    int k = low; // Main array

    while (i < l_len && j < r_len)
    {
        // Copy the smallest value to main array and move through subarray
        if (left[i] <= right [j])
        {
            a[k] = left[i];
            i++;
        }
        else
        {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    // Copy any remaining elements of Left subarray
    while (i < l_len)
    {
        a[k] = left[i];
        i++;
        k++;
    }
    // Copy any remaining elements of Right subarray
    while (j < r_len)
    {
        a[k] = right[j];
        j++;
        k++;
    }
}