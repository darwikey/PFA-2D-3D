#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

class Model;

//! \class ObjLoader
//! \brief Load .obj files and convert them to Model
class ObjLoader {
public:
	ObjLoader(std::string fPath);
	~ObjLoader();

	//! \brief parse the file and build the Model
	bool load(Model* fModel);


private:
	
	void parseHeader();
	void parseVertex(Model* fModel);
	void parseFace(Model* fModel);

	std::ifstream mFile;

};

#endif
