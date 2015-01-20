#ifndef LOADER_HPP
#define LOADER_HPP

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
	void createScene(std::string fPath);

	//! \brief Loader has to create object from OBJ or PLY files. It will parse them and add them to the scene, then they will be placed by the user
	//! \param Path to an OBJ or PLY file
	//! \param name of the object in the scene
	void loadObject(const std::string& fPath, const std::string& fObjectName);

    //! \brief When asked by the user, the Loader has to save the scene
    //! \param The name of the file where the user wants to save his scene (xml file)
    void saveScene(const std::string& fPath);
	
private:

};


#endif
