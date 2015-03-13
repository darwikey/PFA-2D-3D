#include "CreationFile.hpp"
#include "GifWriter.hpp"


CreationFile::CreationFile(Type fType) : mType(fType){

}


CreationFile::CreationFile(const CreationFile& fInstance) {
}


CreationFile::~CreationFile(){
	for (auto _im = mImages.begin(); _im != mImages.end(); ++_im){
		delete *_im;
	}
}


void CreationFile::pushImage(std::unique_ptr<QImage> fImage){
	mImages.push_back(fImage.release());
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

				for (auto _im = mImages.begin(); _im != mImages.end(); ++_im){
					_gif.GifWriteFrame(*_im);
				}

				_gif.GifEnd();
			}
		}
		break;

	default:
		break;
	}
}


const QImage* CreationFile::getFirstImage() const{
	if (mImages.empty()){
		return nullptr;
	}
	else{
		return mImages.front();
	}
}