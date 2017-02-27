/**
 * Image.h
 * @author https://github.com/aaronmboyd
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>

using namespace std;

class Image
{
    public:
        Image();
        Image(const string sourceFilename, int whiteBalanceMode, double gamma,
              double brightness, double redMultiplier, double blueMultiplier,
              int fileFormat, bool interpolateRGBG, const string outputFilename);
        Image(Image &toCopy);
        ~Image();
        
        // Set methods
        void setWhiteBalance(const int whiteBalanceMode);
        void setGamma(const double gamma);
        void setBrightness(const double brightness);
        void setRedMultiplier(const double redMultiplier);
        void setBlueMultiplier(const double blueMultiplier);
        void setFileFormat(const int fileFormat);
        void setInterpolateRGBG(const bool newstate);
        void setSourceFilename(const string filename);
        void setOutputFilename(const string filename);
        
        // Get methods
        const int getWhiteBalance() const;
        const double getGamma() const;
        const double getBrightness() const;
        const double getRedMultiplier() const;
        const double getBlueMultiplier() const;
        const int getFileFormat() const;
        const bool getInterpolateRGBG() const;
        const string getSourceFilename() const;
        const string getOutputFilename() const;
        
        // File format constants
        const static int JPEG = 0;
        const static int TIFF_8 = 1;
        const static int TIFF_16 = 2;
        const static int PPM_8 = 3;
        const static int PPM_16 = 4;
        const static int PSD = 5;
        
        // White Balance constants
        const static int CAMERA = 0;
        const static int AUTO = 1;
        const static int MANUAL = 2;
        
    private:
        int whiteBalanceMode;
        double gamma;
        double brightness;
        double redMultiplier;
        double blueMultiplier;
        int fileFormat;
        bool interpolateRGBG;
        string sourceFilename;
        string outputFilename;                        
};
#endif

