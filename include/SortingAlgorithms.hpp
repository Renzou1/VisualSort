#include "VisualArray.hpp"
#include "Globals.hpp"
#include "Main_f.hpp"

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void selectionSort(int array[], Configuration config)
{
    int pointersNumber = 3;
    VisualArray visualArray = makeVisualArray(array, pointersNumber, &config);
    bool upward = true;

    int min = 0;
    visualArray.addPointer(!upward, 0, config.font_ptr, "min");
    visualArray.addPointer(upward, 0, config.font_ptr, "i");
    visualArray.addPointer(upward, 0, config.font_ptr, "j");
    visualArray.renderArray();
    for(int i = 0; i < SIZE; i++)
    {
        SDL_Delay(100);
        while(SDL_PollEvent(config.event_ptr))
        {
            if (config.event_ptr->type == SDL_QUIT)
            {  destroyVisualSort(config.window_ptr, config.font_ptr, config.visualArray_ptr);  }
        }
        visualArray.slidePointer("j", "i", config);
        for(int j = i; j < SIZE; j++)
        {
            if(array[j] < array[min])
            {
                visualArray.slidePointer("min", "j", config);
                min = j;
            }
        }
        visualArray.swapElementsPointedBy("i", "j", config);
        swap(&array[i], &array[min]);
    }

}