/**
 * class Converter
 * Performs the necessary system calls to drive the dcraw
 * (or any other conversion program) executable
 * Reads in Image parameters and then creates the appropriate
 * system arguments
 *
 * PUBLIC FEATURES:
 *       Converter();
 *       Converter(string theExecutable, string theArguments);
 *       Converter(Converter &toCopy);
 *       ~Converter();
 *       void setExecutable(string theExecutable);
 *       void setArguments(string theArguments);
 *       void setImage(Image * toConvert);
 *       int run(bool preview);
 *       string getExecutable();
 *       string getArguments();
 *       Image * getImage();
 *
 * @author https://github.com/aaronmboyd
 */

#include "Converter.h"
#include "Image.h"
#include <iostream>

using namespace std;

/**
 * Default constructor
 */
Converter::Converter()
{
    theExecutable = "";
    theArguments = "";
}

/**
 * Constructor
 * @param theExecutable - the name of the dcraw executable to run
 * @param theArguments - the arguments to run dcraw with
 */
Converter::Converter(string theExecutable, string theArguments)
{
    this->theExecutable = theExecutable;
    this->theArguments = theArguments;
}

/**
 * Copy Constructor
 * @param toCopy - the Converter to make a copy of
 */
Converter::Converter(Converter &toCopy)
{
    theExecutable = toCopy.theExecutable;
    theArguments = toCopy.theArguments;
    theImage = toCopy.theImage;
}

/**
 * Destructor
 */
Converter::~Converter()
{}

/**
 * Sets the executable for conversion
 * @param theExecutable - the name of the dcraw executable to run
 */
void Converter::setExecutable(const string theExecutable)
{
    this->theExecutable = theExecutable;
}

/**
 * Sets the arguments for conversion
 * @param theArguments - the arguments to run dcraw with
 */
void Converter::setArguments(const string theArguments)
{
    this->theArguments = theArguments;
}

/**
 * Sets the image to convert
 * @param toConvert - the Image to convert
 */
void Converter::setImage(Image * toConvert)
{
    this->theImage = toConvert;
}

/**
 * Performs the Image conversion
 * See dcraw Unix man page here https://www.cybercom.net/~dcoffin/dcraw/dcraw.1.html
 * @param preview - true if only a preview (quick option), false otherwise
 */
int Converter::run(bool preview)
{
	ostringstream args(ostringstream::out);
	ostringstream convert(ostringstream::out);

	if(preview)
		// -h
		// Output a half - size color image. Twice as fast as -q 0.
		args << "-h" << " "; 
	else
		// Add versbose messaging 
		args << "-v" << " ";

	// Add interpolate 4-colour RGBG if required
	if(theImage->getInterpolateRGBG())
		args << "-f" << " ";

	// Add white balance mode to arguments
	switch(theImage->getWhiteBalance())
	{
		case Image::CAMERA:
			// -w
			// Use the white balance specified by the camera. If this is not found, print a warning and use another method.
			args << "-w" << " "; 
			break;
		case Image::AUTO:
			// -a
			// Calculate the white balance by averaging the entire image. 
			args << "-a" << " "; 
			break;
		case Image::MANUAL:
			// Set manual red and blue multipliers
			args << "-r" << " " << theImage->getRedMultiplier() << " ";
			args << "-l" << " " << theImage->getBlueMultiplier() << " ";
			break;
	}

	// -g power toe_slope 
	// Set the gamma curve, by default BT.709 (-g 2.222 4.5).
	// If you prefer sRGB gamma, use (-g 2.4 12.92). For a simple power curve, set the toe slope to zero.
	args << "-g" << " " << theImage->getGamma() << " 0 "; 

	// -b brightness
	//	Divide the white level by this number, 1.0 by default.
	args << "-b" << " " << theImage->getBrightness() << " ";

	// Add fileformat to arguments
	// Only not in preview mode (which defaults to PPM)
	if (!preview)
	{
		switch (theImage->getFileFormat())
		{
			case Image::JPEG:
				// Not implemented
				break;
			case Image::TIFF_8:
				args << "-T" << " ";
				break;
			case Image::TIFF_16:
				args << "-T -6" << " ";
				break;
			case Image::PPM_8:
				// Nothing to do - 8bit PPM is the default format
				break;
			case Image::PPM_16:
				args << "-6" << " ";
				break;
			case Image::PSD:
				// Not implemented
				break;
		}
	}

	// Store arguments, clear string stream
	setArguments(args.str());

	ostringstream final;

 	// Add executable
    final << getExecutable() << " ";
    // Add arguments
    final << getArguments();
    // Add source filename
    final << theImage->getSourceFilename();

	// Make system call
	try
	{
		cout << "About to system call " << final.str();
		system(final.str().c_str());
	}
	catch(...)
	{
		return -1;
	}

	return 0;
}

/**
 * Gets the arguments for conversion
 * @return the arguments
 */
const string Converter::getArguments() const
{
    return theArguments;
}

/**
 * Gets the name of the executable for conversion
 * @return the executable name
 */ 
const string Converter::getExecutable() const
{
    return theExecutable;
}

/**
 * Gets the Image for conversion
 * @return the Image
 */
const Image * Converter::getImage() const
{
    return theImage;
}
