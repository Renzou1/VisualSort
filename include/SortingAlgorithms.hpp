#include <stdbool.h>
#include "VisualArray.hpp"
#include "Globals.hpp"

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int array[], Configuration* config_ptr)
{
    bool upPointer = true;
    VisualArray visualArray = makeVisualArray(array, 3, config_ptr);
    int i = 0;
    visualArray.addPointer(upPointer, i, config_ptr->font_ptr, "i");
    int j = 1;
    visualArray.addPointer(upPointer, j, config_ptr->font_ptr, "j");
    int min = 0;
    visualArray.addPointer(!upPointer, min, config_ptr->font_ptr, "min");

    while(i < config_ptr->size - 1)
    {
        j = i + 1;
        visualArray.slidePointer("j", i + 1, config_ptr);
        if (j < config_ptr->size)
        {
            while(j < config_ptr->size)
            {
                waitForInput(config_ptr, 0);
                visualArray.setComparing(j, min, true);
                waitForInput(config_ptr, DEFAULT_DELAY / 2);
                if(array[j] < array[min])
                {
                    visualArray.setComparing(j, min, false);

                    min = j;
                    visualArray.slidePointer("min", "j", config_ptr);
                    waitForInput(config_ptr, DEFAULT_DELAY);
                }
                visualArray.setComparing(j, min, false);
                j++;
                visualArray.incrementPointer("j", config_ptr);
            }
            waitForInput(config_ptr, 0);            
        }

        
        if (visualArray.getPointer("i")->getIndex() != visualArray.getPointer("min")->getIndex()){
            swap(&array[i], &array[min]);
            visualArray.swapElementsPointedBy("i", "min", config_ptr);
            waitForInput(config_ptr, DEFAULT_DELAY);
        }
        
        i++;
        visualArray.incrementPointer("i", config_ptr);
        waitForInput(config_ptr, 0);

        if (min != i){
            min = i;
            visualArray.slidePointer("min", "i", config_ptr);
            waitForInput(config_ptr, 0);            
        }
    }

    waitToQuit(config_ptr);
}

/* selection sort base:
void selectionSort(int arr[], int size)
{
    int i = 0;
    int j = 1;    
    int min = 0;

    // One by one move boundary of unsorted subarray
    for (int i = 0; i < size - 1; i++)
    {
        // Find the minimum element in unsorted array
        min = i;
        for (int j = i + 1; j < size; j++)
        {
          if (arr[j] < arr[min])
            min = j;
        }

        // Swap the found minimum element with the first element
           if(min != i)
            swap(&arr[min], &arr[i]);
    }
}
*/

void insertionSort(int array[], Configuration* config_ptr)
{
    bool upPointer = true;
    VisualArray VisualArray = makeVisualArray(array, 2, config_ptr);
    VisualArray.addVariable("teste", 0);
    waitForInput(config_ptr, 0);
}

/*  insertion sort base:
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

           Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
*/