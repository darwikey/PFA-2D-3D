#ifndef LOADER_H
#define LOADER_H

#include"mywindow.h"
#include"model.h"
class Loader
{
public:
    Loader();
    static void setModel(string path);
    void show();
    static Model model;

private:
    myWindow window;

};

#endif // LOADER_H
