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
    int j = 0;
    visualArray.addPointer(upPointer, 0, config_ptr->font_ptr, "i");
    int i = 0;
    visualArray.addPointer(upPointer, 0, config_ptr->font_ptr, "j");
    int min = 0;
    visualArray.addPointer(!upPointer, 0, config_ptr->font_ptr, "min");
    
    
    while(i < SIZE)
    {
        waitForInput(config_ptr);
        j = i;
        visualArray.slidePointer("j", "i", config_ptr);
        while(j < SIZE)
        {
            waitForInput(config_ptr);
            visualArray.setComparing(j, min, true);
            if(array[j] < array[min])
            {
                waitForInput(config_ptr);
                visualArray.setComparing(j, min, false);
                waitForInput(config_ptr);
                visualArray.slidePointer("min", "j", config_ptr);
                min = j;
            }
            waitForInput(config_ptr);
            visualArray.setComparing(j, min, false);
            waitForInput(config_ptr);
            j++;
            visualArray.incrementPointer("j", config_ptr);
            SDL_Delay(100 / SPEED);
        }
        waitForInput(config_ptr);
        visualArray.swapElementsPointedBy("i", "min", config_ptr);
        swap(&array[i], &array[min]);
        waitForInput(config_ptr);
        i++;
        visualArray.incrementPointer("i", config_ptr);
        waitForInput(config_ptr);
        min = i;
        visualArray.slidePointer("min", "i", config_ptr);
    }

    while(true)
    {
        waitForInput(config_ptr);
    }
}