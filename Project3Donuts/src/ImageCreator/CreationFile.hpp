#ifndef CREATIONFILE_H
#define CREATIONFILE_H

#include "global.hpp"

//! \class Creation file
//! \brief can contain an image or an animated image
class CreationFile{
public:
	enum class Type{
		IMAGE, ANIMATED_GIF
	};

	//! \brief Constructor
	//! \param the type of image that the class will contain
	CreationFile(Type fType);

	//! \brief add an image
	void pushImage(std::shared_ptr<QImage> fImage);

	//! \brief save the content of the class into a file
	//! \param the path of the file
	void save(const QString& fFileName);

	//! \brief return the first image add 
	std::shared_ptr<QImage> getFirstImage();


private:
	std::vector<std::shared_ptr<QImage>> mImages;

	Type mType;

};

#endif