#include "CreationFile.hpp"
#include "GifWriter.hpp"


CreationFile::CreationFile(Type fType, float fDelayBetweenFrame) : mType(fType), mDelayBetweenFrame(fDelayBetweenFrame){

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

  QString _fileName = fFileName + ".gif";
  
  switch (mType){
  case Type::IMAGE:
    {
      if (!mImages.empty()){
        mImages.front()->save(_fileName);
      }
    }
    break;

  case Type::ANIMATED_GIF:
    {
      if (!mImages.empty()){
        GifWriter _gif;
        _gif.GifBegin(_fileName.toStdString().c_str(), mImages.front()->width(), mImages.front()->height(), (int)mDelayBetweenFrame);

        for (auto _im = mImages.begin(); _im != mImages.end(); ++_im){
          _gif.GifWriteFrame(*_im);
        }

        _gif.GifEnd();
      }
    }
    break;

  case Type::SEPARATED_IMAGE:
    {
      std::string _filename = _fileName.toStdString();

      auto _dot = _filename.find_last_of('.');
      if (_dot != std::string::npos){
        _filename = _filename.substr(0, _dot);
      }

      if (!mImages.empty()){
        int _i = 1;
        for (auto _im = mImages.begin(); _im != mImages.end(); ++_im){
          (*_im)->save(QString::fromStdString(_filename + std::to_string(_i) + ".png"));
          _i++;
        }
      }
    }

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
