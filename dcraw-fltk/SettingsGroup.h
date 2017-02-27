/**
 * SettingsGroup.h
 * @author https://github.com/aaronmboyd
 */

#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_File_Chooser.H>
#include <Fl/Fl_Check_Button.H>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Round_Button.H>
#include <Fl/Fl_Check_Button.H>
#include <Fl/Fl_Text_Display.H>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/fl_message.H>
#include "Image.h"
#include "Converter.h"
#include "PreviewGroup.h"
#include <string>

using namespace std;

class SettingsGroup : public Fl_Group
{
    public:
        SettingsGroup(const int x, const int y, const int w, const int h, const char * label);
        ~SettingsGroup();
        void setImage(Image * theImage);
        void setBrowseFileText(const char * text);
        void setPreview(PreviewGroup * thePreview);
        Image * getImage() const;   

    private:
        // Instance variables
        Image * theImage;
        int fileFormat;
        int whiteBalanceMode;
        PreviewGroup * thePreview;

        // FLTK Widgets
        Fl_Button * convertButton;
        Fl_Button * previewButton;
        Fl_Button * chooseFileButton;
        Fl_Button * whiteBalanceText;
        Fl_Button * fileFormatText;
        Fl_Text_Display * browseFileText;
        Fl_Text_Buffer * filename;

        Fl_Check_Button * interpolateRGBG;

        Fl_Value_Slider * gammaInput;
        Fl_Value_Slider * brightnessInput;
        Fl_Value_Slider * redMultiplier;
        Fl_Value_Slider * blueMultiplier;

        Fl_Round_Button * cameraWhiteBalance;
        Fl_Round_Button * autoWhiteBalance;
        Fl_Round_Button * manualWhiteBalance;
        Fl_Round_Button * jpegFormat;
        Fl_Round_Button * tiff_8Format;
        Fl_Round_Button * tiff_16Format;
        Fl_Round_Button * ppm_8Format;
        Fl_Round_Button * ppm_16Format;
        Fl_Round_Button * psdFormat;
               
        Fl_File_Chooser * fileChooser;        

        Fl_Group * whiteBalanceGroup;
        Fl_Group * fileFormatGroup;
        
        // Callback methods
        static void convertButtonPressed(Fl_Widget * theObject, void * data);
        static void previewButtonPressed(Fl_Widget * theObject, void * data);
        static void chooseFilePressed(Fl_Widget * theObject, void * data);
        static void fileFormatChanged(Fl_Widget * theObject, void * data);
        static void whiteBalanceChanged(Fl_Widget * theObject, void * data);

        // Other private methods
        void createImage();       
};
#endif
