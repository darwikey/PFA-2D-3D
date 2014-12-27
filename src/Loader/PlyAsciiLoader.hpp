#ifndef PLYASCIILOADER_HPP
#define PLYASCIILOADER_HPP

#include "global.hpp"


class Object;

//! \class PlyLoader
//! \brief Load .ply files and convert them to Model
class PlyAsciiLoader {
public:
	PlyAsciiLoader(std::string fPath);
	~PlyAsciiLoader();

	//! \brief parse the file and build the Model
	bool load(Object* fModel);


private:
	enum class VerticesProperties{
		X, Y, Z, NX, NY, NZ, RED, GREEN, BLUE	
	};

	void parseHeader();
	void parseVertex(Object* fModel);
	void parseFace(Object* fModel);

	std::ifstream mFile;
	size_t mVerticesNumber = 0;
	size_t mFacesNumber = 0;
	std::function<void(std::istringstream&, Object*)> mVerticesFunction;
};

#endif PLYLOADER_HPP
