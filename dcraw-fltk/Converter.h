/**
 * Converter.h
 * @author https://github.com/aaronmboyd
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "Image.h"

using namespace std;

class Converter
{
    public:
        Converter();
        Converter(string theExecutable, string theArguments);
        Converter(Converter &toCopy);
        ~Converter();
        void setExecutable(const string theExecutable);
        void setArguments(const string theArguments);
        void setImage(Image * toConvert);
        int run(bool preview);
        const string getExecutable() const;
        const string getArguments() const;
        const Image * getImage() const;
    private:
        string theExecutable;
        string theArguments;
        Image * theImage;
};
#endif
