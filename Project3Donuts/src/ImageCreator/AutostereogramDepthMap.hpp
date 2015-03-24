#ifndef AUTOSTEREOGRAM_DEPTH_MAP_HPP
#define AUTOSTEREOGRAM_DEPTH_MAP_HPP

#include "global.hpp"
#include "Autostereogram.hpp"

// ! \class AutostereogramAlgorithm1
// ! \brief Dummy algorithm that merely returns the depth map
class AutostereogramDepthMap : public Autostereogram {
  Q_OBJECT
  
protected :
  virtual void createWindow(bool fHasPreview = true) override;
  
  virtual std::unique_ptr<CreationFile> render() override;

} ;

#endif
