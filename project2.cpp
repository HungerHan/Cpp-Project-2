// Author: @Zihan Zhang
// Date: Oct. 2020
// Purpose:  implement the beginnings of three classes:
//           ColorClass, RowColumnClass, ColorImageClass 
//           to represent colors, images, and locations within an image

#include<stdio.h>
#include<iostream>
using namespace std;

const int MIN_COLOR = 0;
const int MAX_COLOR = 1000;
const int MAX_ROW = 10;
const int MAX_COL = 18;

/********************************************************************
  Class: ColorClass
  Purpose: modify color value
********************************************************************/
class ColorClass 
{
  public:
    // ColorClass default ctor: default to all white
    ColorClass();
    // ColorClass value ctor
    ColorClass(
        int inRed, 
        int inGreen, 
        int inBlue
        );
    
    // set color to black (0, 0, 0)
    void setToBlack();
    // set color to red (1000, 0, 0)
    void setToRed();
    // set color to green (0, 1000, 0)
    void setToGreen();
    // set color to blue (0, 0, 1000)
    void setToBlue();
    // set color to while (1000, 1000, 1000)
    void setToWhite();

    // set color value based on input RGB value
    bool setTo(
        int intRed, 
        int intGreen, 
        int intBlue
        );
    // set color value based on input ColorClass attributes
    bool setTo(
        ColorClass& inColor
        );

    // add color value from input ColorClass atttributes
    bool addColor(
        ColorClass& rhs
        );
    // subtract color value from input ColorClass atttributes
    bool subtractColor(
        ColorClass &rhs
        );

    // multiplies each RGB value by the adjustment factor provided
    bool adjustBrightness(
        double adjFactor
        );

    // print RGB value
    void printComponentValues();

  private:
    int redVal;    // amount of red in a color
    int greenVal;  // amount of green in a color
    int blueVal;   // amount of blue in a color

    // Helper Function to clipp color
    int clippColor(
        int color, 
        bool &flag
        );

};

// ColorClass default ctor to white
ColorClass::ColorClass()
{
  redVal = 1000;
  greenVal = 1000;
  blueVal = 1000;
}

// ColorClass value ctor
ColorClass::ColorClass(
  int intRed, 
  int intGreen, 
  int intBlue
    )
{
  redVal = intRed;
  greenVal = intGreen;
  blueVal = intBlue;
}


/********************************************************************
  Class: RowColumnClasss
  Purpose: uniquely identify a specific pixel within an image
********************************************************************/
class RowColumnClass
{
  public:
    // RowColumnClass default ctor
    // sets both the row and column value to -99999
    RowColumnClass();
    // RowColumnClass value ctor
    RowColumnClass(
    int inRow,
    int inCol
    );

    //set row & col values as provided
    void setRowCol(
        int inRow,
        int inCol
        );
    // set row value as provided
    void setRow(
        int inRow
        );
    // set col value as provided
    void setCol(
        int inCol
        );

    // return row value
    int getRow();
    // return col value
    int getCol();
 
    // adds the row and column index values in the input parameter
    // to the row and column index of the object the function is called on 
    void addRowColTo(
        RowColumnClass &inRowCol      
        );

    // prints this object's attribute's in the format "[<row>,<col>]" 
    void printRowCol();

  private:
    int rowVal;  // row index for image
    int colVal;  // column index for image
};

// RowColumnClass default ctor: 
// sets both the row and column value to -99999
RowColumnClass::RowColumnClass()
{
  rowVal = -99999;
  colVal = -99999;
}

// RowColumnClass value ctor
RowColumnClass::RowColumnClass(
    int inRow,
    int inCol
    )
{
  rowVal = inRow;
  colVal = inCol;
}

/********************************************************************
  Class: ColorImageClass
  Purpose:  represent a small image
********************************************************************/
class ColorImageClass
{
  public:
    // ColorImageClass default ctor: 
    // set image to full balck
    ColorImageClass(); 
    
    // initializes all image pixels to the color provided via input 
    void initializeTo(
        ColorClass &inColor
        );
  // add RGB values in each pixel by RGB values in rhsimg
    bool addImageTo(
        ColorImageClass &rhsImg
        ); 
    // add RGB values in each pixel by the sum of RGB values
    // in imagesToAdd array
    bool addImages(
        int numImgsToAdd,      
        ColorImageClass imagesToAdd []      
        );
    // the the pixel at the location according to inRowCol
    // to the RGB values according to inColor
    bool setColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &inColor
        );
    // get the RGB value at the location pixel provide in inRowCol
    // put the value in outcolor
    bool getColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &outColor
        ); 

    // print the contents of image to the screen
    void printImage();
 
 
  private:
    // 2D array of ColorClass objects:
    // 1th dimension: row dimension (max: 10)
    // 2nd dimension: col dimension (max: 18)
    ColorClass imageArray[MAX_ROW][MAX_COL];

    // Helper Function to clipp color
    // return the clipped color and set the flag
    int clippColor(
        int color, 
        bool &flag
        );
};


// ColorImageClass default ctor: 
// set image to full balck
ColorImageClass::ColorImageClass()
{
  for (int r = 0; r < MAX_ROW; r ++)
  {
    for (int c = 0; c < MAX_COL; c++)
    {
      imageArray[r][c].setToBlack();
    }
  }
}



#ifdef ANDREW_TEST  
#include "andrewTest.h"  
#else  

/********************************************************************
          main function for testing
********************************************************************/

int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  //testImage.printImage();
  //cout<<"END Original"<<endl;
  testImage.addImages(3, testImages);
  //testImage.printImage();

  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}

#endif  


/********************************************************************
        ColorClass Class Member Function Implementation
********************************************************************/

// set color to black (0, 0, 0)
void ColorClass::setToBlack()
{
  redVal = 0;
  greenVal = 0;
  blueVal = 0;
}

// set color to red (1000, 0, 0)
void ColorClass::setToRed()
{
  redVal = 1000;
  greenVal = 0;
  blueVal = 0;
}

// set color to green (0, 1000, 0)
void ColorClass::setToGreen()
{
  redVal = 0;
  greenVal = 1000;
  blueVal = 0;
}

// set color to blue (0, 0, 1000)
void ColorClass::setToBlue()
{
  redVal = 0;
  greenVal = 0;
  blueVal = 1000;
}

// set color to while (1000, 1000, 1000)
void ColorClass::setToWhite()
{
  redVal = 1000;
  greenVal = 1000;
  blueVal = 1000;
}

// set color value based on input RGB value
bool ColorClass::setTo(
    int inRed, 
    int inGreen, 
    int inBlue
    )
{
  bool flag = false;
  redVal = clippColor(inRed, flag);
  greenVal = clippColor(inGreen, flag);
  blueVal = clippColor(inBlue, flag);
  return flag;
}

// set color value based on input ColorClass attributes
bool ColorClass::setTo(
    ColorClass &inColor
    )
{
  //inColor.printComponentValues();
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;;
  return false;
}


// add color value from input ColorClass attributes
bool ColorClass::addColor(
    ColorClass &rhs
    )
{
  bool flag = false;
  redVal += rhs.redVal;
  greenVal += rhs.greenVal;
  blueVal += rhs.blueVal;
  redVal = clippColor(redVal, flag);
  greenVal = clippColor(greenVal, flag);
  blueVal = clippColor(blueVal, flag);
  return flag;
}

// subtract color value from input ColorClass atttributes
bool ColorClass::subtractColor(
    ColorClass &rhs
    )
{
  bool flag = false;
  redVal -= rhs.redVal;
  greenVal -= rhs.greenVal;
  blueVal -= rhs.blueVal;
  redVal = clippColor(redVal, flag);
  greenVal = clippColor(greenVal, flag);
  blueVal = clippColor(blueVal, flag);
  return flag;
}

// multiplies each RGB value by the adjustment factor provided
bool ColorClass::adjustBrightness(
    double adjFactor
    )
{
  bool flag = false; 
  redVal *= adjFactor;
  greenVal *= adjFactor;
  blueVal *= adjFactor;
  redVal = clippColor(int(redVal), flag);
  greenVal = clippColor(int(greenVal), flag);
  blueVal = clippColor(int(blueVal), flag);
  return flag;
}

// print RGB value
void ColorClass::printComponentValues()
{
  cout<<"R: "<<redVal<<" G: "<<greenVal<<" B: "<<blueVal;
}

// Helper Function to clipp color
int ColorClass::clippColor(
    int color, 
    bool &flag
    )
{
  if (color < MIN_COLOR)
  {
    color = MIN_COLOR;
    flag = true;
  } 
  else if (color > MAX_COLOR)
  {
    color = MAX_COLOR;
    flag = true;
  }
  return color;
}


/********************************************************************
          RowColumnClass Class Member Function Implementation
********************************************************************/

//set row & col values as provided
void RowColumnClass::setRowCol(
        int inRow,
        int inCol
        )
{
  rowVal = inRow;
  colVal = inCol;
}

// set row value as provided
void RowColumnClass::setRow(
    int inRow
    ) 
{
    rowVal = inRow;
}

// set col value as provided
void RowColumnClass::setCol(
    int inCol
    )
{
  colVal = inCol;
}
 
// return row value
int RowColumnClass::getRow()
{
  return rowVal;
}

// return col value
int RowColumnClass::getCol()
{
  return colVal;
}

// adds the row and column index values in the input parameter
// to the row and column index of the object the function is called on
void RowColumnClass::addRowColTo(
    RowColumnClass &inRowCol      
    )
{
    rowVal += inRowCol.rowVal;
    colVal += inRowCol.colVal;
}
 
// prints this object's attribute's in the format "[<row>,<col>]" 
void RowColumnClass::printRowCol()
{
  cout<<"["<<rowVal<<","<<colVal<<"]";
}

/********************************************************************
          ColorImageClass  Class Member Function Implementation
********************************************************************/

// initializes all image pixels to the color provided via input 
void ColorImageClass::initializeTo(
    ColorClass &inColor
    )
{
  for (int r = 0; r < MAX_ROW; r ++)
  {
    for (int c = 0; c < MAX_COL; c++)
    {
      imageArray[r][c].setTo(inColor);
    }
  }
}

// add RGB values in each pixel by RGB values in rhsimg
bool ColorImageClass::addImageTo(
    ColorImageClass &rhsImg
    )
{
  bool flag = false;
  for (int r = 0; r < MAX_ROW; r ++)
  {
    for (int c = 0; c < MAX_COL; c++)
    {
      flag = flag || imageArray[r][c].addColor(rhsImg.imageArray[r][c]);
    }
  }
  return flag;
}

// add RGB values in each pixel by the sum of RGB values
// in imagesToAdd array
bool ColorImageClass::addImages(
    int numImgsToAdd,
    ColorImageClass imagesToAdd []      
    )
{
  bool flag = false;
  for (int r = 0; r < MAX_ROW; r ++)
  {
    for (int c = 0; c < MAX_COL; c++)
    {
      imageArray[r][c].setToBlack();
      for (int l = 0; l < numImgsToAdd; l ++)
      {
        bool resOfAdd = false;
        resOfAdd = imageArray[r][c].addColor\
          (imagesToAdd[l].imageArray[r][c]);
        flag = flag || resOfAdd;
      }
    }
  }
  return flag;
}

// the the pixel at the location according to inRowCol
// to the RGB values according to inColor
bool ColorImageClass::setColorAtLocation(
    RowColumnClass &inRowCol,
    ColorClass &inColor
    )
{
  bool flag = false;
  flag = flag || \
  imageArray[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
  return flag;
}

// get the RGB value at the location pixel provide in inRowCol
// put the value in outcolor
bool ColorImageClass::getColorAtLocation(
    RowColumnClass &inRowCol,
    ColorClass &outColor
    )
{
    if (inRowCol.getRow() >= MAX_ROW \
        || inRowCol.getCol() >= MAX_COL)
    {
      return false;
    }
    else
    {
      outColor.setTo(imageArray[inRowCol.getRow()][inRowCol.getCol()]);

      return true;
    }
}

// print the contents of image to the screen
void ColorImageClass::printImage()
{
  for (int r = 0; r < MAX_ROW; r ++)
  {
    for (int c = 0; c < MAX_COL; c ++)
    {
      if (c == (MAX_COL - 1))
      {
        imageArray[r][c].printComponentValues();
      }
      else
      {
        imageArray[r][c].printComponentValues();
        cout<<"--";
      }
    }
    cout<<endl;
  }
}

// Helper Function to clipp color
int ColorImageClass::clippColor(
    int color, 
    bool &flag
    )
{
  if (color < MIN_COLOR)
  {
    color = MIN_COLOR;
    flag = true;
  } 
  else if (color > MAX_COLOR)
  {
    color = MAX_COLOR;
    flag = true;
  }
  return color;
}