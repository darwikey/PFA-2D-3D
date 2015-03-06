#ifndef CREATIONFILE_H
#define CREATIONFILE_H

#include "global.hpp"


class CreationFile{
public:
	enum class Type{
		IMAGE, ANIMATED_GIF
	};

	CreationFile(Type fType);


	void pushImage(std::shared_ptr<QImage> fImage);

	void save(const QString& fFileName);

	std::shared_ptr<QImage> getFirstImage();


private:
	std::vector<std::shared_ptr<QImage>> mImages;

	Type mType;

};

#endif