#include <VisualIterator.hpp>

class VisualArray
{
public:
    VisualArray();
    void split();
    void swap();
private:
    int size;
    VisualIterator i;
    VisualIterator j;
};