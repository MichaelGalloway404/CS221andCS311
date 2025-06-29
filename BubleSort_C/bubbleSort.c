/*
  A helper function to swap variables used in bubbleSort()
*/
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
/*
  A simple buble sort that uses a swap function
  accepts an array to be sorted, arrays length, and an A or D 
  for ascending or descending order
*/
void bubbleSort(int arr[], int n, char order)
{
  // itter through array
  for (int i = 0; i < n - 1; i++)
  {
    // Skip what we know is in correct spot
    for (int j = 0; j < n - i - 1; j++)
    {
      if(order == 'A')
      {
        // ascending order
        if (arr[j] > arr[j + 1])
        {
          swap(&arr[j], &arr[j + 1]);
        }
      }
      if(order == 'D')
      {
        // descending order
        if (arr[j] < arr[j + 1])
        {
          swap(&arr[j], &arr[j + 1]);
        }
      }
    }
  }
}