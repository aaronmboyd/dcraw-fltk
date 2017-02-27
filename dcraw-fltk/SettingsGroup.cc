/**
 * class SettingsGroup
 * Extends Fl_Group
 * Represents a group of Fl_Widgets for changing the settings
 * and controlling flow of the program through events
 *
 * PUBLIC FEATURES:
 *      SettingsGroup(int x, int y, int w, int h, const char * label);
 *      ~SettingsGroup();
 *      void setImage(Image * theImage);
 *      void setBrowseFileText(char * text);
 *		void setPreview(PreviewGroup * thePreview);
 *      Image * getImage();
 *
 * @author https://github.com/aaronmboyd
 */

#include "SettingsGroup.h"

/**
 * Overloaded constructor
 * Extends Fl_Group
 * Initialises and displays the settings Fl_Widgets
 * @param x - the horizontal position
 * @param y - the vertical position
 * @param w - the width
 * @param h - the height
 * @param label - the label for this SettingsGroup
 */
SettingsGroup::SettingsGroup(int x,int y,int w,int h, const char * label) : Fl_Group(x,y,w,h,label)
{
    // Choose file button
    chooseFileButton = new Fl_Button(40,20,140,30,"Browse for file...");
    chooseFileButton->callback(chooseFilePressed,this);
    browseFileText = new Fl_Text_Display(200,20,140,40,"");
    filename = new Fl_Text_Buffer(1024);
    filename->text("None Selected");
    free(filename->text());
    browseFileText->buffer(filename);

    // File format select
    fileFormatGroup = new Fl_Group(40,65,320,100,"");
    fileFormatText = new Fl_Button(100,80,0,0,"File Format (bits per sample)");

    tiff_8Format = new Fl_Round_Button(70,95,20,20,"TIFF (8 bit)");
	tiff_8Format->type(FL_RADIO_BUTTON);
	tiff_8Format->callback(fileFormatChanged,this);

    tiff_16Format = new Fl_Round_Button(70,115,20,20,"TIFF (16 bit)");
	tiff_16Format->type(FL_RADIO_BUTTON);
	tiff_16Format->callback(fileFormatChanged,this);

    ppm_8Format = new Fl_Round_Button(210,95,20,20,"PPM (8 bit)");
	ppm_8Format->type(FL_RADIO_BUTTON);
	ppm_8Format->callback(fileFormatChanged,this);

    ppm_16Format = new Fl_Round_Button(210,115,20,20,"PPM (16 bit)");
	ppm_16Format->type(FL_RADIO_BUTTON);
	ppm_16Format->callback(fileFormatChanged,this);

    fileFormatGroup->add(fileFormatText);
    fileFormatGroup->add(tiff_8Format);
    fileFormatGroup->add(tiff_16Format);
    fileFormatGroup->add(ppm_8Format);
    fileFormatGroup->add(ppm_16Format);

    fileFormatGroup->box(FL_EMBOSSED_BOX);

    // Interpolate RGBG check box
    interpolateRGBG = new Fl_Check_Button(60,175,20,20,"Interpolate RGBG");

    // Gamma and brightness sliders
    gammaInput = new Fl_Value_Slider(60,205,260,30,"Gamma");
    gammaInput->type(FL_HOR_NICE_SLIDER);
    gammaInput->minimum(0.3);
    gammaInput->maximum(1.5);
    gammaInput->value(0.6);

    brightnessInput = new Fl_Value_Slider(60,255,260,30,"Brightness");
    brightnessInput->type(FL_HOR_NICE_SLIDER);
    brightnessInput->minimum(1.0);
    brightnessInput->maximum(6.0);
    brightnessInput->value(3.5);

    // White balance mode select
    whiteBalanceGroup = new Fl_Group(40,310,320,210,"");
    cameraWhiteBalance = new Fl_Round_Button(60,350,20,20,"Camera");
    cameraWhiteBalance->type(FL_RADIO_BUTTON);
    cameraWhiteBalance->callback(whiteBalanceChanged,this);

    autoWhiteBalance = new Fl_Round_Button(170,350,20,20,"Auto");
    autoWhiteBalance->type(FL_RADIO_BUTTON);
    autoWhiteBalance->callback(whiteBalanceChanged,this);

    manualWhiteBalance = new Fl_Round_Button(260,350,20,20,"Manual");
    manualWhiteBalance->type(FL_RADIO_BUTTON);
    manualWhiteBalance->callback(whiteBalanceChanged,this);

    whiteBalanceGroup->box(FL_EMBOSSED_BOX);
    whiteBalanceGroup->add(cameraWhiteBalance);
    whiteBalanceGroup->add(autoWhiteBalance);
    whiteBalanceGroup->add(manualWhiteBalance);

    // White balance manual mode sliders
    redMultiplier = new Fl_Value_Slider(60,390,260,30,"Red Multiplier (1.0 = daylight)");
    redMultiplier->type(FL_HOR_NICE_SLIDER);
    redMultiplier->minimum(0.5);
    redMultiplier->maximum(2.0);
    redMultiplier->value(1.0);
    redMultiplier->deactivate();

    blueMultiplier = new Fl_Value_Slider(60,450,260,30,"Blue Multiplier (1.0 = daylight)");
    blueMultiplier->type(FL_HOR_NICE_SLIDER);
    blueMultiplier->minimum(0.5);
    blueMultiplier->maximum(2.0);
    blueMultiplier->value(1.0);
    blueMultiplier->deactivate();

    whiteBalanceText = new Fl_Button(120,330,0,0,"White Balance Mode");
    whiteBalanceGroup->add(redMultiplier);
    whiteBalanceGroup->add(blueMultiplier);

    // Action Buttons
    previewButton = new Fl_Button(40,540,140,30,"Preview");
    previewButton->callback(previewButtonPressed,this);
    convertButton = new Fl_Button(220,540,140,30,"Convert");
    convertButton->callback(convertButtonPressed,this);

    // Add to group (order irrelevant)
    this->add(chooseFileButton);
    this->add(browseFileText);
    this->add(fileFormatGroup);
    this->add(interpolateRGBG);
    this->add(gammaInput);
    this->add(brightnessInput);
    this->add(whiteBalanceGroup);
    this->add(previewButton);
    this->add(convertButton);
    this->box(FL_UP_BOX);

    end();
}

/**
 * Destructor
 */
SettingsGroup::~SettingsGroup()
{
	/** Do not necessarily need to
	 *  delete Fl_Widget objects,
	 *  as their memory is handled
	 *  by their parent objects
	 */
}

/**
 * Sets a new Image for conversion
 * @param theImage - the Image to convert
 */
void SettingsGroup::setImage(Image * theImage)
{
    this->theImage = theImage;
}

/**
 * Sets the label text box with new text
 * @param text - the new text
 */
void SettingsGroup::setBrowseFileText(const char * text)
{
    this->filename->text(text);
    free(filename->text());
}

/**
 * @param thePreview - the pointer to the PreviewGroup window
 */
void SettingsGroup::setPreview(PreviewGroup * thePreview)
{
  this->thePreview = thePreview;
}

/**
 * @return the Image currently being prepared for conversion
 */
Image * SettingsGroup::getImage() const 
{
    return theImage;
}

/**
 * static callback method for conversion button
 * This method does not need to be explicitly called from the code
 * Fl_Widgets that have this method set as their callback will enter
 * this method on certain events
 * Creates a new Converter, and performs a real conversion (may take some time)
 *
 * @param theObject - the calling object
 * @param data - pointer to data (usually the "this" keyword, to give this
 *                                function access to non-static members of this class)
 *
 */

void SettingsGroup::convertButtonPressed(Fl_Widget * theObject, void * data)
{
    SettingsGroup * access = static_cast<SettingsGroup *>(data);
    access->deactivate();
    access->createImage();

  if(access->filename->text() == "None Selected")
  {
    fl_message("You have not selected a file!");
    access->activate();
    return;
  }

  // Convert Image for real
  Converter * theConverter = new Converter();
  theConverter->setImage(access->theImage);
  //theConverter->setExecutable("dcraw");
  theConverter->setExecutable("dcraw-9.27-ms-64-bit.exe");
  theConverter->run(false);
  delete theConverter;

  access->activate();
}

/**
 * static callback method for preview button
 * This method does not need to be explicitly called from the code
 * Fl_Widgets that have this method set as their callback will enter
 * this method on certain events
 * Creates a new Converter, and performs a quick conversion
 * Indicates that the PreviewGroup should load this new image
 *
 * @param theObject - the calling object
 * @param data - pointer to data (usually the "this" keyword, to give this
 *                                function access to non-static members of this class)
 *
 */
void SettingsGroup::previewButtonPressed(Fl_Widget * theObject, void * data)
{
    SettingsGroup * access = static_cast<SettingsGroup *>(data);
    access->deactivate();
    access->createImage();
   
	if(access->filename->text() == "None Selected")
    {
        fl_message("You have not selected a file!");
        access->activate();
        return;
    }

	// Convert Image
	Converter * theConverter = new Converter();
	theConverter->setImage(access->theImage);
	theConverter->setExecutable("dcraw-9.27-ms-64-bit.exe");

	// Running in preview mode will override file format and default to PPM
	theConverter->run(true);
	delete theConverter;

	// Show conversion (force it to be .PPM)
	string filename = string(access->theImage->getSourceFilename());
	int extension = filename.find_last_of(".");
	filename = filename.substr(0, extension);
	filename = filename.insert(filename.length(), ".ppm");
	access->thePreview->loadImage(filename.c_str());

	access->activate();
}

/**
 * static callback method for file chooser
 * This method does not need to be explicitly called from the code
 * Fl_Widgets that have this method set as their callback will enter
 * this method on certain events
 * @param theObject - the calling object
 * @param data - pointer to data (usually the "this" keyword, to give this
 *                                function access to non-static members of this class)
 *
 */
void SettingsGroup::chooseFilePressed(Fl_Widget * theObject, void * data)
{
    SettingsGroup * access = static_cast<SettingsGroup *>(data);

    access->fileChooser = new Fl_File_Chooser(".","RAW Image Files (*.{crw,raw})",FL_SINGLE,"Select a file...");
    access->fileChooser->show();

    while (access->fileChooser->visible())
        Fl::wait();

    if(access->fileChooser->value() != 0)
    {
      const char * filename = access->fileChooser->value();
      access->getImage()->setSourceFilename(filename);
      access->setBrowseFileText(filename);
    }

    access->redraw();
}

/**
 * static callback method for file format radio buttons
 * This method does not need to be explicitly called from the code
 * Fl_Widgets that have this method set as their callback will enter
 * this method on certain events
 * @param theObject - the calling object
 * @param data - pointer to data (usually the "this" keyword, to give this
 *                                function access to non-static members of this class)
 *
 */
void SettingsGroup::fileFormatChanged(Fl_Widget * theObject, void * data)
{
    SettingsGroup * access = static_cast<SettingsGroup *>(data);

    if(access->tiff_8Format->value() == 1)
        access->fileFormat = Image::TIFF_8;

    else if(access->tiff_16Format->value() == 1)
        access->fileFormat = Image::TIFF_16;

    else if(access->ppm_8Format->value() == 1)
        access->fileFormat = Image::PPM_8;

    else if(access->ppm_16Format->value() == 1)
        access->fileFormat = Image::PPM_16;
}

/**
 * static callback method for whiteBalance radio buttons
 * This method does not need to be explicitly called from the code
 * Fl_Widgets that have this method set as their callback will enter
 * this method on certain events
 * @param theObject - the calling object
 * @param data - pointer to data (usually the "this" keyword, to give this
 *                                function access to non-static members of this class)
 *
 */
void SettingsGroup::whiteBalanceChanged(Fl_Widget * theObject, void * data)
{
    SettingsGroup * access = static_cast<SettingsGroup *>(data);
    if(access->manualWhiteBalance->value() == 1)
    {
        access->blueMultiplier->activate();
        access->redMultiplier->activate();
        access->whiteBalanceMode = Image::MANUAL;
    }
    else
    {
        access->blueMultiplier->deactivate();
        access->redMultiplier->deactivate();
        if(access->autoWhiteBalance->value() == 1)
            access->whiteBalanceMode = Image::AUTO;
        else if(access->cameraWhiteBalance->value() == 1)
            access->whiteBalanceMode = Image::CAMERA;
    }
}

/**
 * Creates an Image object with the values represented in the GUI
 */
void SettingsGroup::createImage()
{
    // Set attributes
	theImage->setFileFormat(fileFormat);
    theImage->setWhiteBalance(whiteBalanceMode);
    theImage->setGamma(gammaInput->value());
    theImage->setBrightness(brightnessInput->value());
    theImage->setRedMultiplier(redMultiplier->value());
    theImage->setBlueMultiplier(blueMultiplier->value());

	// Set interpolate RGBG
	if(interpolateRGBG->value() == 1)
        theImage->setInterpolateRGBG(true);
    else
        theImage->setInterpolateRGBG(false);

	// Set source filename
	theImage->setSourceFilename(filename->text());

	// Set output filename
	string source = string(theImage->getSourceFilename());
	string output = source.substr(0,source.find_last_of("."));
	
	if(theImage->getFileFormat() == Image::TIFF_8 || theImage->getFileFormat() == Image::TIFF_16)
	{
		output = output.insert(output.length(),".tiff");
		theImage->setOutputFilename(output.c_str());
	}
	else if (theImage->getFileFormat() == Image::PPM_8 || theImage->getFileFormat() == Image::PPM_16)
	{
		output = output.insert(output.length(), ".ppm");
		theImage->setOutputFilename(output.c_str());
	}
}
