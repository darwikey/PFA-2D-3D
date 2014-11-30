#ifndef PLYLOADER_HPP
#define PLYLOADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

class Model;

//! \class PlyLoader
//! \brief Load .ply files and convert them to Model
class PlyLoader {
public:
	PlyLoader(std::string fPath);
	~PlyLoader();

	//! \brief parse the file and build the Model
	bool load(Model* fModel);


private:
	enum class VerticesProperties{
		X, Y, Z, NX, NY, NZ, RED, GREEN, BLUE	
	};

	void parseHeader();
	void parseVertex(Model* fModel);
	void parseFace(Model* fModel);

	std::ifstream mFile;
	size_t mVerticesNumber = 0;
	size_t mFacesNumber = 0;
	std::function<void(std::istringstream&, Model*)> mVerticesFunction;
};

#endif PLYLOADER_HPP
