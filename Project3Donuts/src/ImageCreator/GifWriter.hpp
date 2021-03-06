
#ifndef GIF_WRITER_H
#define GIF_WRITER_H

#include "global.hpp"
#include <stdint.h>


//! \class GifWriter
//! \brief use to create animated gif
//! \note coded by Charlie Tangora
//! \note Public domain.
//! \note Email me : ctangora -at- gmail -dot- com
class GifWriter {

public:
	//! \brief Constructor
	GifWriter() {};
	
	//! \brief Creates a gif file.
	//! \param filename name of the file, should end by .gif
	//! \param delay the time between frames in hundredths of a second - note that not all viewers pay much attention to this value.
	bool GifBegin(const char* filename, uint32_t width, uint32_t height, uint32_t delay, int32_t bitDepth = 8, bool dither = false);

	//! \brief Writes out a new frame to a GIF in progress.
	//! \note GifBegin must have been called before
	bool GifWriteFrame(const QImage* fImage, int bitDepth = 8, bool dither = false);

	//! \brief Writes the EOF code, closes the file handle, and frees temp memory used by a GIF.
	bool GifEnd();


private:

	struct GifPalette
	{
		int bitDepth;

		uint8_t r[256];
		uint8_t g[256];
		uint8_t b[256];

		// k-d tree over RGB space, organized in heap fashion
		// i.e. left child of node i is node i*2, right child is node i*2+1
		// nodes 256-511 are implicitly the leaves, containing a color
		uint8_t treeSplitElt[255];
		uint8_t treeSplit[255];
	};

	// max, min, and abs functions
	int GifIMax(int l, int r);
	int GifIMin(int l, int r);
	int GifIAbs(int i);

	// walks the k-d tree to pick the palette entry for a desired color.
	// Takes as in/out parameters the current best color and its error -
	// only changes them if it finds a better color in its subtree.
	// this is the major hotspot in the code at the moment.
	void GifGetClosestPaletteColor(GifPalette* pPal, int r, int g, int b, int& bestInd, int& bestDiff, int treeRoot = 1);
			
	void GifSwapPixels(uint8_t* image, int pixA, int pixB);
	
	// just the partition operation from quicksort
	int GifPartition(uint8_t* image, const int left, const int right, const int elt, int pivotIndex);

	// Perform an incomplete sort, finding all elements above and below the desired median
	void GifPartitionByMedian(uint8_t* image, int left, int right, int com, int neededCenter);

	// Builds a palette by creating a balanced k-d tree of all pixels in the image
	void GifSplitPalette(uint8_t* image, int numPixels, int firstElt, int lastElt, int splitElt, int splitDist, int treeNode, bool buildForDither, GifPalette* pal);

	// Finds all pixels that have changed from the previous image and
	// moves them to the fromt of th buffer.
	// This allows us to build a palette optimized for the colors of the
	// changed pixels only.
	int GifPickChangedPixels(const uint8_t* lastFrame, uint8_t* frame, int numPixels);

	// Creates a palette by placing all the image pixels in a k-d tree and then averaging the blocks at the bottom.
	// This is known as the "modified median split" technique
	void GifMakePalette(const uint8_t* lastFrame, const QImage* nextFrame, int bitDepth, bool buildForDither, GifPalette* pPal);

	// Implements Floyd-Steinberg dithering, writes palette value to alpha
	void GifDitherImage(const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, GifPalette* pPal);

	// Picks palette colors for the image using simple thresholding, no dithering
	void GifThresholdImage(const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, GifPalette* pPal);
	
	// Simple structure to write out the LZW-compressed portion of the image
	// one bit at a time
	struct GifBitStatus
	{
		uint8_t bitIndex;  // how many bits in the partial byte written so far
		uint8_t byte;      // current partial byte

		uint32_t chunkIndex;
		uint8_t chunk[256];   // bytes are written in here until we have 256 of them, then written to the file
	};

	// insert a single bit
	void GifWriteBit(GifBitStatus& stat, uint32_t bit);
	
	// write all bytes so far to the file
	void GifWriteChunk(FILE* f, GifBitStatus& stat);

	void GifWriteCode(FILE* f, GifBitStatus& stat, uint32_t code, uint32_t length);
	

	// The LZW dictionary is a 256-ary tree constructed as the file is encoded,
	// this is one node
	struct GifLzwNode
	{
		uint16_t m_next[256];
	};

	// write a 256-color (8-bit) image palette to the file
	void GifWritePalette(const GifPalette* pPal, FILE* f);

	// write the image header, LZW-compress and write out the image
	void GifWriteLzwImage(FILE* f, uint32_t left, uint32_t top, uint32_t delay, GifPalette* pPal);



	const int mkGifTransIndex = 0;
    FILE* mFile = nullptr;
	QImage* mOldImage = nullptr;
    bool mFirstFrame = true;

	uint32_t mWidth = 0;
	uint32_t mHeight = 0;
	uint32_t mDelay = 0;
};


#endif
