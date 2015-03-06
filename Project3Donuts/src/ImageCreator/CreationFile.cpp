#include "CreationFile.hpp"
#include "GifWriter.hpp"


CreationFile::CreationFile(Type fType) : mType(fType){

}


void CreationFile::pushImage(std::shared_ptr<QImage> fImage){
	mImages.push_back(fImage);
}


void CreationFile::save(const QString& fFileName){
	switch (mType){
	case Type::IMAGE:
		{
			if (!mImages.empty()){
				mImages.front()->save(fFileName);
			}
		}
		break;

	case Type::ANIMATED_GIF:
		{
			if (!mImages.empty()){
				GifWriter _gif;
				_gif.GifBegin(fFileName.toStdString().c_str(), mImages.front()->width(), mImages.front()->height(), 50);

				for (auto _im : mImages){
					_gif.GifWriteFrame(_im.get());
				}

				_gif.GifEnd();
			}
		}
		break;

	default:
		break;
	}
}


std::shared_ptr<QImage> CreationFile::getFirstImage(){
	if (mImages.empty()){
		return std::shared_ptr<QImage>();
	}
	else{
		return mImages.front();
	}
}