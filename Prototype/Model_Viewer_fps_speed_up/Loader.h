#ifndef LOADER_H
#define LOADER_H

#include "MyWindow.h"
#include "Model.h"
#include "Singleton.h"


class Loader : public Singleton<Loader> {
 public:
  Loader();
  Model* getModel(const std::string& fName);
  void show();

 private:
  MyWindow mWindow;

  map<std::string, Model*> mModels;

};

#endif // LOADER_H
