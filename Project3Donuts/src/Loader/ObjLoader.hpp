#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include "global.hpp"

class Object;

//! \class ObjLoader
//! \brief Load .obj files and convert them to Object
class ObjLoader {
public:
	ObjLoader(std::string fPath);
	~ObjLoader();

	//! \brief parse the file and build the Object
	bool load(Object* fObject);


private:
	
	void parseHeader();
	void parseVertex(Object* fObject);
	void parseFace(Object* fObject);

	std::ifstream mFile;

};

#endif
