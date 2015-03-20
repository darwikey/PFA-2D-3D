#include "AutostereogramDepthMap.hpp"

void AutostereogramDepthMap::createWindow(bool fHasPreview){
  Autostereogram::createWindow(fHasPreview);
}

std::unique_ptr<CreationFile> AutostereogramDepthMap::render(){
  std::unique_ptr<QImage> _depthmap = this->getDepthMap() ;
  _depthmap->invertPixels() ;

  std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_depthmap));
  return _file ;
}
