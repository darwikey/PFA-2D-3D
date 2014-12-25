CXX=g++
CXXFLAGS=-Wall -g 

Loader: Loader.o Camera.o Scene.o Object.o BoundingBox.o
	$(CXX) $(CXXFLAGS) -c $^ -o $@

Loader.o : Loader.hpp Loader.cpp

Camera.o: Camera.hpp PixelTab.hpp Camera.cpp

Scene.o: Scene.hpp Object.hpp Scene.cpp

Object.o: Object.hpp Object.cpp

BoundingBox.o: BoundingBox.hpp BoundingBox.cpp

