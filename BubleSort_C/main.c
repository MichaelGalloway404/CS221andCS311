#include <stdio.h>

// Function to print "usage message"
void usageMessage(){
  printf("Incorrect usage\n");
  printf("Sort given data in ascending or descending order. First argument must be A or D to indicate\n");
  printf("ascending or descending sort order, followed by up to 32 integers separated by spaces\n");
  printf("Usage: ./main [A|D] n1 n2 ... n31 n32\n");
}

/*
  Michael Galloway
  CS 221 Winter 2023
  An implement a bubble sort algorithm on an array of integers.
  Uses command-line parameters to populate an array with data.
  Prints a "usage message" when no arguments are given.
  Program will accept an A or D as the second command line argument for sortting in ascending or  
  descending, prints a "usage message" if secound arg is not A or D.
  Program accepts upto 32 integers for array.

  Example input:
  ./main A 1 3 2 4 6 5
  ./main A 1 7 9 4 5 6 2 8 3 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
  ./main A 1 7 9 4 5 6 2 8 3 10 11 12 13 14 15 16 17 18 -9 20 21 22 23 24 25 26 27 28 29 30 31 32
*/
int main(int argc,char* argv[])
{
  int count = 0;
  
  if(argc>=2 && argc <= 34)
  {
    if(*argv[1] == 'A' || *argv[1] == 'D')
    {
      count = (argc-2);
      int array[count];
      for(int i = 0; i < count;i++)
      {
        array[i] = atoi(argv[i+2]);
      }
  
      bubbleSort(array, count,'A');
      
      // Print the array
      for (int i = 0; i < count; i++)
          printf("%d\n", array[i]);
    }
    else
    usageMessage();
  }
  else
    usageMessage();
  return 0;
}
