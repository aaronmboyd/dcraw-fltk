/**
 * class PreviewGroup
 *
 * A Fl_Group which can parse and display a Fl_Image
 * in it's area
 *
 * PUBLIC FEATURES:
 *      PreviewGroup(int x, int y, int w, int h, const char * label);
 *      ~PreviewGroup();
 * 	    void loadImage(char * filename);
 */

#include "PreviewGroup.h"

/**
 * Overloaded constructor
 * Extends Fl_Group
 * Loads a default information message upon creation
 * @param x - the starting x position of the PreviewGroup
 * @param y - the starting y position of the PreviewGroup
 * @param w - the width in pixels of the PreviewGroup
 * @param h - the height in pixels of the PreviewGroup
 * @param label - the label of the PreviewGroup
 */
PreviewGroup::PreviewGroup(const int x, const int y, const int w, const int h, const char * label) : Fl_Group(x,y,w,h,label)
{
  theBox = new Fl_Box(x,y,w,h);
  loadImage("./default.bmp");
  end();
}

/**
 * Destructor
 */
PreviewGroup::~PreviewGroup()
{
}

/**
 * Loads a filename and parses the image as a Fl_Shared_Image
 * Scales the image to fit the bounds of the box
 * Shows error message and returns early if image cannot be loaded
 * @param filename - the file to load to the preview window
 */
void PreviewGroup::loadImage(const char * filename)
{
  theBox->redraw();
  if (thePreview) thePreview->release();

    thePreview = Fl_Shared_Image::get(filename);
    if (!thePreview)
    {
      fl_alert("Cannot preview that image!");
      return;
    }

    if (thePreview->w() > theBox->w() || thePreview->h() > theBox->h())
    {
      Fl_Image *temp;
      if (thePreview->w() > thePreview->h())
        temp = thePreview->copy(theBox->w(), theBox->h() * thePreview->h() / thePreview->w());
      else
        temp = thePreview->copy(theBox->w() * thePreview->w() / thePreview->h(), theBox->h());

      thePreview->release();
      thePreview = (Fl_Shared_Image *)temp;
    }

    theBox->image(thePreview);
    theBox->redraw();
}
