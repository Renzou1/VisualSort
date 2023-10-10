#include <VisualArray.hpp>

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
/*void selectionSort(int array[], int size, VisualArray visualArray)
{
    int smallest = 0;
    for(int i = 0; i < size; i++)
    {
        for(int j = i; j < size; j++)
        {
            if(array[j] < array[smallest])
            {
                smallest = j;
            }
        }
        swap(&array[i], &array[smallest]);
    }
}*/