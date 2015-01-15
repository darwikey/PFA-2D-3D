#ifndef CREATION_HPP
#define CREATION_HPP

#include "global.hpp"
class Pixel;
class PixelTab;


  // ! \class Creation
  // ! \brief Creation is the basic virtual class for the creation of any other image. However, this basic virtual class also corresponds to basic Photography
class Creation{
public:
    //! \brief Creation can be initialize with a default size and content by calling the default constructor. Default size will be 100*100, so default attribute mPixelTable will contain 10 000 pixels colored in black (0,0,0)
    Creation();

    //! \brief Creation can also be initialize to a certain size, and attribute mPixelTable will be initialize to contain the corresponding number of Pixels colored in black
    //! \param fLength indicates how large is the image (in number of pixels) and fHeight indicates how high is the image (in number of pixels)
    Creation(int fLength, int fHeight);

    //! \brief To finish, Creation can be initialize with an already defined PixelTab given in arguments, and her length and height will also be given in arguments. First thing to do in that case is to check if the PixelTab contains as many pixels as it should
    //! \param fTable is the given PixelTab for the image, and fLength and fHeight corresponds as the same values as in the other constructor
    Creation(PixelTab fTable, int fLength, int fHeight);

    //! \brief Creation contains virtual methods that could be redefined in other classes that inherit from this class. Those methods will use a vector of PixelTab that the Creator will give them, and will turn back a vector of Images (even when there is only one image to return)
    //! \param fToUse is a PixelTab vector initialize by Creator and that contains what create method needs
    virtual <Image*> create(<PixelTab*> fToUse);

private:
    //! \brief Attributes for all types of creations
    <Pixel*> mPixelTable;
    //! \describe how large is the image to create in number of pixel
    int mLength; 
    //! \describe how high is the image to create in number of pixel
    int mHeight;
};

#endif
