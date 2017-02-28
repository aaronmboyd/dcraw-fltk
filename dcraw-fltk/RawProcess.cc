/**
 * class RawProcess
 *
 * Main entry program for a simple GUI interface
 * for the dcraw raw image conversion program
 * Utilises the FLTK libraries
 *
 * PUBLIC FEATURES:
 *	 int main(int argc, char **argv)
 *
 * @author https://github.com/aaronmboyd
 */

#include "Image.h"
#include "SettingsGroup.h"
#include "PreviewGroup.h"
#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>

using namespace std;

// Window size constants
const static int WIDTH = 1200;
const static int HEIGHT = 800;
const static int X = 500;
const static int Y = 200;
const static int SETTINGS_WIDTH = 480;
const static int SETTINGS_HEIGHT = 780;
const static int SETTINGS_X = 10;
const static int SETTINGS_Y = 10;
const static int PREVIEW_WIDTH = 680;
const static int PREVIEW_HEIGHT = 780;
const static int PREVIEW_X = 500;
const static int PREVIEW_Y = 10;

int main(int argc, char **argv)
{
    Fl_Window * theWindow = new Fl_Window(X,Y,WIDTH,HEIGHT,"dcraw-fltk");

    fl_register_images();

    PreviewGroup * thePreview = new PreviewGroup(PREVIEW_X,PREVIEW_Y,PREVIEW_WIDTH,PREVIEW_HEIGHT,"");
    SettingsGroup * theSettings = new SettingsGroup(SETTINGS_X,SETTINGS_Y,SETTINGS_WIDTH,SETTINGS_HEIGHT,"");

    theSettings->setImage(new Image());
    theSettings->setPreview(thePreview);

    theWindow->add(theSettings);
    theWindow->end();
    theWindow->show(argc, argv);

    Fl::run();

    delete theSettings;
    delete thePreview;
    delete theWindow;

    return 0;
}
