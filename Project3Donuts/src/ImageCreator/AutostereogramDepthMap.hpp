#ifndef AUTOSTEREOGRAMDEPTHMAP_HPP
#define AUTOSTEREOGRAMDEPTHMAP_HPP

#include "global.hpp"
#include "Autostereogram.hpp"

//! \class AutostereogramDepthMap
//! \brief class to return the depth map of the current view

class AutostereogramDepthMap : public Autostereogram {
  Q_OBJECT

protected :
  virtual void createWindow(bool fHasPreview = true) override;
  
  virtual std::unique_ptr<CreationFile> render() override;

} ;

#endif
