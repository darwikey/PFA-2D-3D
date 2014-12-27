#ifndef EXEMPLE_HPP
#define EXEMPLE_HPP

#include "global.hpp"


// ! \class Loader
// ! \brief The loader is in charge with parsing XML files for scene initialisation or parsing OBJ and PLY files for objects creation
class Loader{
public:
	// ! \brief There is only one default constructor for Loader which will initialize what we potentially need for using it
	Loader();

	//! \brief Loader can create a new scene from nothing
	void createScene();
	//! \brief It can also create a scene from an XML file that will be given by the user. It will parse it and create the associate objects and scene
	//! \param path to the XML file
	void createScene(char *fPath);

	//! \brief Loader has to create object from OBJ or PLY files. It will parse them and add them to the scene, then they will be placed by the user
	//! \param Path to an OBJ or PLY file
	void createObject(char *fPath);
	
private:
	//! \brief createObject method will recognise an OBJ or PLY file and will call the adequate method
	//! \param Path to the file
	void _parseOBJFile(char *fPath);
	void _parsePLYBinaryFile(char *fPath);
	void _parsePLYAsciiFile(char *fPath);
};


#endif
