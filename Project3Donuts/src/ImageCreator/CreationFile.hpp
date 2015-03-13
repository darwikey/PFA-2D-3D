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

	~CreationFile();

	//! \brief add an image
	void pushImage(std::unique_ptr<QImage> fImage);

	//! \brief save the content of the class into a file
	//! \param the path of the file
	void save(const QString& fFileName);

	//! \brief return the first image add 
	const QImage* getFirstImage() const;


private:
	//! \brief Copy constructor
	CreationFile(const CreationFile& fInstance);


	std::vector<QImage*> mImages;

	Type mType;

};

#endif