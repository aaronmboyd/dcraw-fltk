/**
 * PreviewGroup.h
 * @author https://github.com/aaronmboyd
 */

#ifndef PREVIEWGROUP_H
#define PREVIEWGROUP_H

#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Image.H>
#include <Fl/Fl_Shared_Image.H>
#include <Fl/fl_message.H>
#include <Fl/Fl_Box.H>

using namespace std;

class PreviewGroup : public Fl_Group
{
    public:
        PreviewGroup(const int x, const int y, const int w, const int h, const char * label);
        ~PreviewGroup();
        
        void loadImage(const char * filename);

    private:
        Fl_Shared_Image * thePreview;
        Fl_Box * theBox;
};
#endif
