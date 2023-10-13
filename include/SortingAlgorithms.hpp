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
    int pointersNumber = 3;
    VisualArray visualArray = makeVisualArray(array, pointersNumber, config_ptr);
    bool upward = true;

    int min = 0;
    visualArray.addPointer(!upward, 0, config_ptr->font_ptr, "min");
    visualArray.addPointer(upward, 0, config_ptr->font_ptr, "i");
    visualArray.addPointer(upward, 0, config_ptr->font_ptr, "j");
    SDL_RenderClear(config_ptr->renderer_ptr);
    visualArray.renderArray();
    for(int i = 0; i < SIZE; i++)
    {
        waitForInput(config_ptr);
        visualArray.slidePointer("j", "i", config_ptr);
        for(int j = i; j < SIZE; j++)
        {
            if(array[j] < array[min])
            {
                visualArray.slidePointer("min", "j", config_ptr);
                min = j;
            }
        }
        visualArray.swapElementsPointedBy("i", "j", config_ptr);
        swap(&array[i], &array[min]);
    }

}