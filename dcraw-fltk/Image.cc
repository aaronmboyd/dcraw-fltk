/**
 * class Image
 * An abstract representation of the source / output file
 * names and various attributes and options for an image
 * conversion
 *
 * PUBLIC FEATURES:
 *      Image();
 *       Image(string sourceFilename, int whiteBalanceMode, double gamma,
 *             double brightness, double redMultiplier, double blueMultiplier,
 *             int fileFormat, bool interpolateRGBG, string outputFilename);
 *       Image(Image &toCopy);
 *       ~Image();
 *
 *       // Set methods
 *       void setWhiteBalance(int whiteBalanceMode);
 *       void setGamma(double gamma);
 *       void setBrightness(double brightness);
 *       void setRedMultiplier(double redMultiplier);
 *       void setBlueMultiplier(double blueMultiplier);
 *       void setFileFormat(int fileFormat);
 *       void setInterpolateRGBG(bool newstate);
 *       void setSourceFilename(string filename);
 *       void setOutputFilename(string filename);
 *
 *       // Get methods
 *       int getWhiteBalance();
 *       double getGamma();
 *       double getBrightness();
 *       double getRedMultiplier();
 *       double getBlueMultiplier();
 *       int getFileFormat();
 *       bool getInterpolateRGBG();
 *       string getSourceFilename();
 *       string getOutputFilename();
 *
 *       // File format constants
 *       const static int JPEG = 0;
 *       const static int TIFF_24 = 1;
 *       const static int TIFF_48 = 2;
 *       const static int PPM_24 = 3;
 *       const static int PPM_48 = 4;
 *       const static int PSD = 5;
 *
 *       // White Balance constants
 *       const static int CAMERA = 0;
 *       const static int AUTO = 1;
 *       const static int MANUAL = 2;
 */

#include "Image.h"

/**
 * Default constructor
 */
Image::Image()
{
   // Set defaults
   whiteBalanceMode = AUTO;
   gamma = 0.6;
   brightness = 3.5;
   redMultiplier = 1.0;
   blueMultiplier = 1.0;
   interpolateRGBG = true;
   fileFormat = PPM_16;
   sourceFilename = "";
   outputFilename = "";
}

/**
 * Overloaded Constructor
 * @param sourceFilename - the source for the image
 * @param whiteBalanceMode - the white balance mode
 * @param gamma - the gamma value for this image
 * @param brightness - the brightness for this image
 * @param redMultiplier - the red multiplier for manual white balance
 * @param blueMultiplier - the blue multiplier for manual white balance
 * @param fileFormat - the requested output file format
 * @param interpolateRGBG - 4-color interpolation selection
 * @param outputFilename - the requested output filename (based only on file format)
 */
Image::Image(const string sourceFilename, const int whiteBalanceMode, const double gamma,
             const double brightness, const double redMultiplier, const double blueMultiplier,
             const int fileFormat, const bool interpolateRGBG, const string outputFilename)
{
    setWhiteBalance(whiteBalanceMode);
    setGamma(gamma);
    setBrightness(brightness);
    setRedMultiplier(redMultiplier);
    setBlueMultiplier(blueMultiplier);
    setFileFormat(fileFormat);
    setInterpolateRGBG(interpolateRGBG);
    setSourceFilename(sourceFilename);
    setOutputFilename(outputFilename);
}

/**
 * Copy constructor
 * @param toCopy - the Image object to make a copy of
 */
Image::Image(Image &toCopy)
{
    whiteBalanceMode = toCopy.whiteBalanceMode;
    gamma = toCopy.gamma;
    brightness = toCopy.brightness;
    redMultiplier = toCopy.redMultiplier;
    blueMultiplier = toCopy.blueMultiplier;
    fileFormat = toCopy.fileFormat;
    interpolateRGBG = toCopy.interpolateRGBG;
    sourceFilename = toCopy.sourceFilename;
    outputFilename = toCopy.outputFilename;
}

/**
 * Destructor
 */
Image::~Image()
{}

/**
 * @param whiteBalanceMode - the white balance mode
 */
void Image::setWhiteBalance(const int whiteBalanceMode)
{
    this->whiteBalanceMode = whiteBalanceMode;
}

/**
 * @param gamma - value for gamma
 */
void Image::setGamma(const double gamma)
{
    this->gamma = gamma;
}

/**
 * @param brightness - value for brightness
 */
void Image::setBrightness(const double brightness)
{
    this->brightness = brightness;
}

/**
 * @param redMultiplier - value for red multiplier with manual white balance
 */
void Image::setRedMultiplier(const double redMultiplier)
{
    this->redMultiplier = redMultiplier;
}

/**
 * @param blueMultiplier - value for blue multiplier with manual white balance
 */
void Image::setBlueMultiplier(const double blueMultiplier)
{
    this->blueMultiplier = blueMultiplier;
}

/**
 * @param fileFormat - value for the file format (see Image.h for format constants)
 */
void Image::setFileFormat(const int fileFormat)
{
    this->fileFormat = fileFormat;
}

/**
 * @param newstate - set to true to turn on 4-color RGBG interpolation, false otherwise
 */
void Image::setInterpolateRGBG(const bool newstate)
{
    this->interpolateRGBG = newstate;
}

/**
 * @param filename - the original source filename for this Image (probably .RAW or .CRW extension)
 */
void Image::setSourceFilename(const string filename)
{    
	this->sourceFilename = filename;
}

/**
 * @param filename - the required output filename (currently based on the original filename plus a new extension)
 */
void Image::setOutputFilename(const string filename)
{    
	this->outputFilename = filename;
}

/**
 * @return the white balance mode for this Image
 */
const int Image::getWhiteBalance() const
{
    return whiteBalanceMode;
}

/**
 * @return the gamma value for this Image
 */
const double Image::getGamma() const
{
    return gamma;
}

/**
 * @return the brightness value for this Image
 */
const double Image::getBrightness() const
{
    return brightness;
}

/**
 * @return the red multiplier value for this Image
 */
const double Image::getRedMultiplier() const
{
    return redMultiplier;
}

/**
 * @return the blue multiplier value for this Image
 */
const double Image::getBlueMultiplier() const
{
    return blueMultiplier;
}

/**
 * @return the file format for this Image
 */
const int Image::getFileFormat() const
{
    return fileFormat;
}

/**
 * @return the interpolateRGBG selection (true for on, false otherwise)
 */
const bool Image::getInterpolateRGBG() const
{
    return interpolateRGBG;
}

/**
 * @return the filename for this image
 */
const string Image::getSourceFilename() const
{
    return sourceFilename;
}

/**
 * @return the requested output filename for this image
 */
const string Image::getOutputFilename() const
{
    return outputFilename;
}
