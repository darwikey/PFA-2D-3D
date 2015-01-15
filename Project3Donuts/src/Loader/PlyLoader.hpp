#ifndef PLYLOADER_HPP
#define PLYLOADER_HPP

#include "global.hpp"


class Object;

//! \class PlyLoader
//! \brief Load .ply files and convert them to Model
class PlyLoader {
public:
	PlyLoader(std::string fPath);
	~PlyLoader();

	//! \brief parse the file and build the Model
	bool load(Object* fModel);


private:
	enum class VerticesProperties{
		X, Y, Z, NX, NY, NZ, RED, GREEN, BLUE	
	};

	enum class PlyFormat{
		ASCII, BINARY_LITTLE_ENDIAN, BINARY_BIG_ENDIAN
	};

	void parseHeader();
	void parseVertex(Object* fModel);
	void parseFace(Object* fModel);

	std::ifstream mFile;
	PlyFormat mFormat = PlyFormat::ASCII;
	size_t mVerticesNumber = 0;
	size_t mFacesNumber = 0;
	std::function<void(std::istream&, Object*)> mVerticesFunction;
};

#endif
