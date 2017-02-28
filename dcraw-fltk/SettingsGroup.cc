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
	int yPosition = 20;
	int xPositionColumn1 = 20;
	int xColumn1Inset = xPositionColumn1 + 20;
	int xPositionColumn2 = 240;
	int xColumn2Inset = xPositionColumn2 + 20;

    // Choose file button
    chooseFileButton = new Fl_Button(xPositionColumn1, yPosition, 200, 50,"Browse for raw image...");
    chooseFileButton->callback(chooseFilePressed,this);
    browseFileText = new Fl_Text_Display(xPositionColumn2, yPosition, 200, 50, "");
    filename = new Fl_Text_Buffer(1024);
    filename->text("Not selected");
    free(filename->text());
    browseFileText->buffer(filename);

	// Choose location of DCRAW
	yPosition += 70;
	chooseDCRAWFileButton = new Fl_Button(xPositionColumn1, yPosition, 200, 50, "Browse for DCRAW...");
	chooseDCRAWFileButton->callback(chooseDCRAWFilePressed, this);
	browseDCRAWFileText = new Fl_Text_Display(xPositionColumn2, yPosition, 200, 50, "");
	pathToDCRAW = new Fl_Text_Buffer(1024);
	pathToDCRAW->text("Not set");
	free(pathToDCRAW->text());
	browseDCRAWFileText->buffer(pathToDCRAW);

    // File format select
	yPosition += 70;
    fileFormatGroup = new Fl_Group(xPositionColumn1, yPosition, 440, 100,"");
	yPosition += 20;
    fileFormatText = new Fl_Button((xPositionColumn1+60), yPosition, 0, 0, "File Format");
	yPosition += 20;
    tiff_8Format = new Fl_Round_Button((xPositionColumn1 + 20), yPosition, 20, 20, "TIFF (8 bit)");
	tiff_8Format->type(FL_RADIO_BUTTON);
	tiff_8Format->callback(fileFormatChanged,this);

	yPosition += 20;
    tiff_16Format = new Fl_Round_Button((xPositionColumn1 + 20), yPosition, 20, 20, "TIFF (16 bit)");
	tiff_16Format->type(FL_RADIO_BUTTON);
	tiff_16Format->callback(fileFormatChanged,this);

	yPosition -= 20;
    ppm_8Format = new Fl_Round_Button(xPositionColumn2, yPosition, 20, 20, "PPM (8 bit)");
	ppm_8Format->type(FL_RADIO_BUTTON);
	ppm_8Format->callback(fileFormatChanged,this);

	yPosition += 20;
    ppm_16Format = new Fl_Round_Button(xPositionColumn2, yPosition, 20, 20, "PPM (16 bit)");
	ppm_16Format->type(FL_RADIO_BUTTON);
	ppm_16Format->callback(fileFormatChanged,this);

    fileFormatGroup->add(fileFormatText);
    fileFormatGroup->add(tiff_8Format);
    fileFormatGroup->add(tiff_16Format);
    fileFormatGroup->add(ppm_8Format);
    fileFormatGroup->add(ppm_16Format);

    fileFormatGroup->box(FL_EMBOSSED_BOX);

    // Interpolate RGBG check box
	yPosition += 60;
    interpolateRGBG = new Fl_Check_Button(xPositionColumn1, yPosition, 20, 20, "Interpolate RGBG" );

    // Gamma slider
	yPosition += 40;
    gammaInput = new Fl_Value_Slider(xPositionColumn1, yPosition, 400, 40,"Gamma");
    gammaInput->type(FL_HOR_NICE_SLIDER);
    gammaInput->minimum(0.3);
    gammaInput->maximum(1.5);
    gammaInput->value(0.6);

	// Brightness slider
	yPosition += 60;
    brightnessInput = new Fl_Value_Slider(xPositionColumn1, yPosition, 400, 40, "Brightness" );
    brightnessInput->type(FL_HOR_NICE_SLIDER);
    brightnessInput->minimum(1.0);
    brightnessInput->maximum(6.0);
    brightnessInput->value(3.5);

    // White balance mode select
	yPosition += 80;
    whiteBalanceGroup = new Fl_Group(xPositionColumn1, yPosition, 440, 240, "");

	yPosition += 20;
	whiteBalanceText = new Fl_Button((xPositionColumn1 + 80), yPosition, 0, 0, "White Balance Mode" );

	yPosition += 20;
    cameraWhiteBalance = new Fl_Round_Button(xColumn1Inset, yPosition, 20, 20, "Camera" );
    cameraWhiteBalance->type(FL_RADIO_BUTTON);
    cameraWhiteBalance->callback(whiteBalanceChanged,this);

    autoWhiteBalance = new Fl_Round_Button(xColumn1Inset + 120, yPosition, 20, 20, "Auto" );
    autoWhiteBalance->type(FL_RADIO_BUTTON);
    autoWhiteBalance->callback(whiteBalanceChanged,this);

    manualWhiteBalance = new Fl_Round_Button(xColumn1Inset + 120 + 120, yPosition, 20, 20, "Manual" );
    manualWhiteBalance->type(FL_RADIO_BUTTON);
    manualWhiteBalance->callback(whiteBalanceChanged,this);

    whiteBalanceGroup->box(FL_EMBOSSED_BOX);
	whiteBalanceGroup->add(whiteBalanceText);
    whiteBalanceGroup->add(cameraWhiteBalance);
    whiteBalanceGroup->add(autoWhiteBalance);
    whiteBalanceGroup->add(manualWhiteBalance);

    // White balance manual mode sliders
	yPosition += 40;
	redMultiplier = new Fl_Value_Slider(xColumn1Inset, yPosition, 360, 40, "Red Multiplier (1.0 = daylight)");
    redMultiplier->type(FL_HOR_NICE_SLIDER);
    redMultiplier->minimum(0.5);
    redMultiplier->maximum(2.0);
    redMultiplier->value(1.0);
    redMultiplier->deactivate();

	yPosition += 60;
    blueMultiplier = new Fl_Value_Slider(xColumn1Inset, yPosition, 360, 40, "Blue Multiplier (1.0 = daylight)");
    blueMultiplier->type(FL_HOR_NICE_SLIDER);
    blueMultiplier->minimum(0.5);
    blueMultiplier->maximum(2.0);
    blueMultiplier->value(1.0);
    blueMultiplier->deactivate();

    whiteBalanceGroup->add(redMultiplier);
    whiteBalanceGroup->add(blueMultiplier);

    // Action Buttons
	yPosition += 120;
	previewButton = new Fl_Button(xColumn1Inset, yPosition, 140, 40, "Preview" );
    previewButton->callback(previewButtonPressed,this);

	convertButton = new Fl_Button(xPositionColumn2, yPosition, 140, 40, "Convert" );
    convertButton->callback(convertButtonPressed,this);

    // Add to group (order irrelevant)
    this->add(chooseFileButton);
    this->add(browseFileText);
	this->add(chooseDCRAWFileButton);
	this->add(browseDCRAWFileText);
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
* Sets the label text box with new text
* @param text - the new text
*/
void SettingsGroup::setDCRAWBrowseFileText(const char * text)
{
	this->pathToDCRAW->text(text);
	free(pathToDCRAW->text());
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

	string file = access->filename->text();
	if (file == "Not selected")
	{
		fl_message("Please select a raw image first");
		access->activate();
		return;
	}
	free(access->filename->text());

	file = access->pathToDCRAW->text();
	if (file == "Not set")
	{
		fl_message("Please select the path to DRCRAW first");
		access->activate();
		return;
	}
	free(access->pathToDCRAW->text());

  // Convert Image for real
  Converter * theConverter = new Converter();
  theConverter->setImage(access->theImage);
  theConverter->setExecutable(access->pathToDCRAW->text());
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
   
	string file = access->filename->text();
	if (file == "Not selected")
	{
		fl_message("Please select a raw image first");
		access->activate();
		return;
	}
	free(access->filename->text());

	file = access->pathToDCRAW->text();
	if (file == "Not set")
	{
		fl_message("Please select the path to DRCRAW first");
		access->activate();
		return;
	}
	free(access->pathToDCRAW->text());

	// Convert Image
	Converter * theConverter = new Converter();
	theConverter->setImage(access->theImage);
	theConverter->setExecutable(access->pathToDCRAW->text());

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

    access->fileChooser = new Fl_File_Chooser(".","RAW Image Files (*.{crw,raw,rw2})",FL_SINGLE,"Select a file...");
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
* static callback method for DCRAW file chooser
* This method does not need to be explicitly called from the code
* Fl_Widgets that have this method set as their callback will enter
* this method on certain events
* @param theObject - the calling object
* @param data - pointer to data (usually the "this" keyword, to give this
*                                function access to non-static members of this class)
*
*/
void SettingsGroup::chooseDCRAWFilePressed(Fl_Widget * theObject, void * data)
{
	SettingsGroup * access = static_cast<SettingsGroup *>(data);

	access->dcrawFileChooser = new Fl_File_Chooser(".", "Executable (*.{exe})", FL_SINGLE, "Select path to DCRAW file...");
	access->dcrawFileChooser->show();

	while (access->dcrawFileChooser->visible())
		Fl::wait();

	if (access->dcrawFileChooser->value() != 0)
	{
		const char * pathToDCRAW = access->dcrawFileChooser->value();
		access->setDCRAWBrowseFileText(pathToDCRAW);
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
