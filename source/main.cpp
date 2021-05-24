#include "Scene.h"



AutoDrone d(20, 30);
AutoDrone d2(-10, 15);
void fun()
{
    d.fly(10, 20);
}

void fun2()
{
    d2.fly(100, 30);
}

int main()
{
    Scene s;
    s.run();
    return 0;
}