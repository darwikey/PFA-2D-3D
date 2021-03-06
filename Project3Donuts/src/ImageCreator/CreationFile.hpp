#ifndef CREATIONFILE_H
#define CREATIONFILE_H

#include "global.hpp"

//! \class CreationFile
//! \brief can contain an image or an animated image
class CreationFile{
public:
  enum class Type{
    IMAGE, ANIMATED_GIF, SEPARATED_IMAGE
      };

  //! \brief Constructor
  //! \param the type of image that the class will contain
  //! \param fDelayBetwwenFrame the time between frames in hundredths of a second 
  CreationFile(Type fType, float fDelayBetweenFrame = 50.f);

  ~CreationFile();

  //! \brief add an image
  void pushImage(std::unique_ptr<QImage> fImage);

  //! \brief add the good extension to the file which will be saved
  //! \param the name of the file and the extension needed
  //! \return a QString with the good extension
  QString extension(QString fFileName, QString fExt);
  
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
  // in hundredths of a second 
  float mDelayBetweenFrame;

};

#endif
