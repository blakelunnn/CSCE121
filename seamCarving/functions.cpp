#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
    // TODO(student): create a seam
    int *arr = new int[length];
	for(int i = 0; i < length; ++i){
		arr[i] = 0;
	}
	return arr;
}

void deleteSeam(int* seam) {
    // TODO(student): delete a seam
    delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): load an image
    ifstream ifs (filename);
	if (!ifs.is_open())
	{
		cout << "Error: failed to open input file - " << filename << endl;
		return false;
	}
	
	char type[2];
	ifs >> type; 
	if (type[0] != 'P')
	{  
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
	if(type[1] != '3')
	{
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
	
	int width2 = 0;
	int height2 = 0;
	ifs >> width2;
	if(ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	ifs	>> height2;
	if(ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (width2 != width)
	{ 
		cout << "Error: input width (" << width << ") does not match value in file (" << width2 << ")" << endl;
		return false;
	}
	if (height2 != height)
	{ 
		cout << "Error: input height (" << height << ") does not match value in file (" << height2 << ")" << endl;
		return false;
	}
	
	
	
	int maxColorValue = 0;
	ifs >> maxColorValue;
	if(ifs.fail()){
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (maxColorValue != 255) {
		cout << "Error: file is not using RGB color values." << endl;
		return false;
	}
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++)
		{
			if(!ifs.eof())
			{
				ifs >> image[col][row].r;
				if(ifs.fail())
				{
					if(!ifs.eof())
						cout << "Error: read non-integer value" << endl;
					else
						cout << "Error: not enough color values" << endl;
					return false;
				}
			} 
			else
			{
				cout << "Error: not enough color values" << endl;
				return false;
			}
			
			
			if(!ifs.eof())
			{
				ifs >> image[col][row].g;
				if(ifs.fail())
				{
					if(!ifs.eof())
						cout << "Error: read non-integer value" << endl;
					else
						cout << "Error: not enough color values" << endl;
					return false;
				}
			} 
			else
			{
				cout << "Error: not enough color values" << endl;
				return false;
			} 
			
			
			
			if(!ifs.eof())
			{
				ifs >> image[col][row].b;
				if (ifs.fail())
				{
					if(!ifs.eof())
					{
						string temp;
						ifs >> temp;
						cout << "Error: read non-integer value" << endl;
					} 
					else
						cout << "Error: not enough color values" << endl;
					return false;
				}
			} 
			else
			{
				cout << "Error: not enough color values" << endl;
				return false;
			}
			
			
			
			// check if number is in valid range
			if((image[col][row].r < 0) || (image[col][row].r > 255))
			{
				cout << "Error: invalid color value " << image[col][row].r << endl;
				return false;
			}
			if((image[col][row].g < 0) || (image[col][row].g > 255))
			{
				cout << "Error: invalid color value " << image[col][row].g << endl;
				return false;
			}
			if((image[col][row].b < 0) || (image[col][row].b > 255))
			{
				cout << "Error: invalid color value " << image[col][row].b << endl;
				return false;
			}
		}
	}
	
	string temp2;
	ifs >> temp2;
	if(!ifs.eof())
	{
		cout << "Error: too many color values" << endl;
		return false;
	}
	
	ifs.close();
	return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): output an image
    ofstream ofs (filename);
	if(!ofs.is_open())
	{
		cout << "Error: failed to open output file - " << filename << endl;
		return false;
	}
	
	
	ofs << "P3" << endl;
	cout << width << " " << height << endl; 
	cout << "255" << endl;
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			ofs << image[col][row].r << " " << image[col][row].g << " " << image[col][row].b << " ";
			
	return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
    // TODO(student): compute the energy of a pixel
    int row1 = row - 1;
	int row2 = row + 1;
	int col1 = column - 1;
	int col2 = column + 1;
	
	if(row == height - 1)
			row2 = 0;
	else
		if (row == 0)
			row1 = height - 1;
	
	if(column == width - 1)
			col2 = 0;
	else
		if (column == 0)
			col1 = width - 1;
	
	int rowDiffRed = image[column][row2].r - image[column][row1].r;
	int rowDiffGreen = image[column][row2].g - image[column][row1].g;
	int rowDiffBlue = image[column][row2].b - image[column][row1].b;
	int rowSum = pow(rowDiffRed, 2.0) + pow(rowDiffGreen, 2.0) + pow(rowDiffBlue, 2.0);
	
	int colDiffRed = image[col2][row].r - image[col1][row].r;
	int colDiffGreen = image[col2][row].g - image[col1][row].g;
	int colDiffBlue = image[col2][row].b - image[col1][row].b;
	int colSum = pow(colDiffRed, 2.0) + pow(colDiffGreen, 2.0) + pow(colDiffBlue, 2.0);
	
	return colSum + rowSum;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
    // TODO(student): load a vertical seam
	int totalEnergy = energy(image, start_col, 0, width, height);
	int left;
	int center;
	int right;
	seam[0] = start_col;
	
	for(int col = 1; col < height; col++)
	{
		if(start_col == 0) // if nothing to left
		{
			center = energy(image, start_col, col, width, height);
			right = energy(image, start_col + 1, col, width, height);
			left = center + right;
		}
		else if (start_col == width - 1) // if nothing to right
		{
			center = energy(image, start_col, col, width, height);
			left = energy(image, start_col - 1, col, width, height);
			right = center + left;
		}
		else
		{
			center = energy(image, start_col, col, width, height);
			left = energy(image, start_col - 1, col, width, height);
			right = energy(image, start_col + 1, col, width, height);
		}
		
		if(left < center && left < right) // cases
		{
			start_col--;
			seam[col] = start_col;
			totalEnergy += left;
		}
		else if(center < left && center < right)
		{
			seam[col] = start_col;
			totalEnergy += center;
		}
		else if(right < center && right < left)
		{
			start_col++;
			seam[col] = start_col;
			totalEnergy += right;
		}
		else if(left == center && left < right)
		{
			seam[col] = start_col;
			totalEnergy += center;
		}
		else if(center == right && center < left)
		{
			seam[col] = start_col;
			totalEnergy += center;
		}
		else if(right == left && right < center)
		{
			start_col++;
			seam[col] = start_col;
			totalEnergy += right;
		}
		else if(center == left && center == right) // normal
		{
			seam[col] = start_col;
			totalEnergy += center;
		}
	}
	return totalEnergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
    // TODO(student): load a horizontal seam
    int totalEnergy = energy(image, 0, start_row, width, height);
	int left;
	int center;
	int right;
	seam[0] = start_row;
	
	for(int row = 1; row < width; row++)
	{
		if(start_row == 0) // if nothing to left
		{
			center = energy(image, row, start_row, width, height);
			right = energy(image, row, start_row + 1, width, height);
			left = center + right;
		}
		else if (start_row == width - 1) // if nothing to right
		{
			center = energy(image, row, start_row, width, height);
			left = energy(image, row, start_row - 1, width, height);
			right = center + left;
		}
		else
		{
			center = energy(image, row, start_row, width, height);
			left = energy(image, row, start_row - 1, width, height);
			right = energy(image, row, start_row + 1, width, height);
		}
		
		if(left < center && left < right) // cases
		{
			start_row--;
			seam[row] = start_row;
			totalEnergy += left;
		}
		else if(center < left && center < right)
		{
			seam[row] = start_row;
			totalEnergy += center;
		}
		else if(right < center && right < left)
		{
			start_row++;
			seam[row] = start_row;
			totalEnergy += right;
		}
		else if(left == center && left < right)
		{
			seam[row] = start_row;
			totalEnergy += center;
		}
		else if(center == right && center < left)
		{
			seam[row] = start_row;
			totalEnergy += center;
		}
		else if(right == left && right < center)
		{
			start_row++;
			seam[row] = start_row;
			totalEnergy += right;
		}
		else if(center == left && center == right) // normal
		{
			seam[row] = start_row;
			totalEnergy += center;
		}
	}
	return totalEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min vertical seam
	int* minSeam = createSeam(height);
	int* temp = createSeam(height);
	int temp2 = loadVerticalSeam(image, 0, width, height, minSeam);
    
	for(int col = 1; col < width; col++)
		if(loadVerticalSeam(image, col, width, height, temp) < temp2)
			temp2 = loadVerticalSeam(image, col, width, height, minSeam);
	
	deleteSeam(temp);
	return minSeam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min horizontal seam
    int* minSeam = createSeam(width);
	int* temp = createSeam(width);
	int temp2 = loadHorizontalSeam(image, 0, width, height, minSeam);
    
	for(int row = 1; row < height; row++)
		if(loadVerticalSeam(image, row, width, height, temp) < temp2)
			temp2 = loadVerticalSeam(image, row, width, height, minSeam);
	
	deleteSeam(temp);
	return minSeam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
    // TODO(student): remove a vertical seam
    for (int row = 0; row < height; row++)
        for (int col = verticalSeam[row]; col < width - 1; col++)
            image[col][row] = image[col + 1][row];
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
    // TODO(student): remove a horizontal seam
    for (int row = 0; row < width; row++)
        for (int col = horizontalSeam[row]; col < height - 1; col++)
            image[row][col] = image[row][col + 1];
}
