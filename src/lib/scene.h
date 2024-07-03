#include <vector>
#include "element.h"

using std::vector;

class scene
{
private:
    vector<element> elements;

public:
    scene();

    void getElements();
    void addElement(element &element);
    bool findElement(element &element);
    void removeElement(element &element);

    void update(float dt);
    void draw();

    ~scene();
};
