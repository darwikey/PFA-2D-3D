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

	//! \param fData, in the tuple : indice, texture coordinate, normal
	void injectDataInModel(Object* fObject, std::tuple<uint, uint, uint> fData);

	float getFloat(const std::string&);

	std::ifstream mFile;

};

#endif
