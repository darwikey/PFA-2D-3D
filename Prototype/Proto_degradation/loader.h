#ifndef LOADER_H
#define LOADER_H

#include"mywindow.h"
#include"model.h"
#include "singleton.h"


class Loader : public Singleton<Loader>
{
public:
    Loader();
    Model* getModel(const std::string& fName);
    void show();

private:
    myWindow mWindow;

	map<std::string, Model*> mModels;

};

#endif // LOADER_H
