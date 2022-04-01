/*
              
Name:   Kai Ho Chak     
Date:   March 10, 2021       
                                       
//==============================================================================

Purpose: create a computer image of the Mandelbrot set

Details: This program compute and print an image of the mandelbrot set by:

     1) prompting the user for the width of the image. Since the image 
	      will be a square, height will be the same as width, which will
	      determine the resolution of the image. For instance, if the user 
	      input 1000 as width, the image will be 1000x1000 pixels.

	   2) prompting the user for the number of iterations. Since values in 
	      the mandelbrot set will take infinitely long to calculate, a 
	      limit is set for the number of itereations. In this program, it is 
	      200. If the user enter any value more than 200, this program will 
	      proceed with the max number of iterations, namely 200. Users are 
	      suggested to enter at least 20 for better image result.

	   3) compute the mandelbrot set. Given the width and number of 
	      iterations, this program will do the following task.

	      - traverse all pixels
	      - convert all pixels into cartesian coordinate
	      - decide whether it is within the mandelbrot set
	      - print the corresponding color for each pixel

	   4) after the image is finished, the user will be prompted the name of 
	      the file. This program will create a cooresponding file type. For 
	      exmple, if "test.png" is entered, a png file name "test" will be 
	      created.

	   All prompts are proceed by functions defined in ioutil.cpp. If the 
	   user enters Ctrl-D during the prompt, program will be forced to end.
                             
Assumptions and Limitation: 

   - instead of loops, this program only uses recursive functions
	 - maximum number of iterations is set to be 200
	 - for better image result, users are  suggested to choose at least 20 
	   times of iterations
                                       
Any Known Bugs: n/a  

*/

// save diagnostic state                                              
#pragma GCC diagnostic push

// turn off specific warnings.                                        
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wconversion"
#include <Magick++.h>
using namespace Magick;

// turn the warnings back on                                          
#pragma GCC diagnostic pop

#include <iostream>
#include <cmath>
#include <cstring>
#include "ioutil.h"
using namespace std;

// constants for prompt
const char PROMPT_WIDTH[] = "Width of the image: ";
const char PROMPT_ITERATE[] = "Number of the iterations: ";
const char PROMPT_NAME[] = "Name of the file: ";
const char OVER_LIMIT[] = "Number of iterations over limit. The limit is ";
const int MAXLEN = 60;
const int MINLEN = 1;
const int limit = 200;

// helper functions
void mandelbrot (Image &image,
		 int iterate,
		 int x,
		 int y,
		 int width,
		 int height);

void print_row (Image &image,
		int iterate,
		int &x,
		int y,
		int width,
		int height);

void print_pixel (Image &image,
		  int itereate,
		  int count,
		  int x,
		  int y,
		  double z_a,
		  double z_b,
		  double c_a,
		  double c_b);

int main ()
{
    int width;
    int height;
    int iterate;
    bool eof = false;
    char filename[MAXLEN+1];
    int x = 0;
    int y = 0;
    
    // prompt user for the width
    width = readInt (PROMPT_WIDTH, eof);
    
    // proceed, if program is not forced to end
    if ( eof != true )
    {
	// create an image that is a square
	height = width; 
	Image image (Geometry (width, height), "white");

        // prompt user for the number of itertions
	iterate = readInt (PROMPT_ITERATE, eof);
	
	// proceed, if program is not forced to end
	if ( eof != true )
	{
	    // notice user if no of iterates is over the limit
	    if ( iterate > limit )
	    {
		cout << OVER_LIMIT << limit << endl;
		iterate = limit;
	    }

	    // print mandelbrot
	    mandelbrot (image, iterate, x, y, width, height);

	    // prompt user for the filename
	    readString (PROMPT_NAME, filename, MAXLEN, MINLEN, eof);

	    // proceed to creat the file, if program is not forced to end
	    if ( eof != true )
	    {
		image.write (filename);
	    }
	}
    }
    
    return 0;
} // main ends

/*
Function: mandelbrot

Purpose:  write an image of the mandelbrot set

Details:  This function writes the given image by traversing rows of image 
          recursively. For example, a 1000x1000 image will have 1000 rows.

	  The base case of this function is when this no more row to 
	  traverse. This function will do nothing.

	  The recursive case of this function is when there is still row(s)
	  to traverse. This function will print the row (by passing to 
	  print_row() to proceed) and apply the algorithm to the rest of
	  the rows.

Input:
          iterate   - an integer that is the  number of iterations requested
	  x         - an integer that is the current number of column (by pixel)
	  y         - an integer that is the current number of row (by pixel)
	  width     - an integer that is the width of the image
	  height    - an integer that is the height of the image
Output:
          image     - an image that the the function writes on
Return:
          n/a

*/

void mandelbrot (Image &image,
		 int iterate,
		 int x,
		 int y,
		 int width,
		 int height)
{
    // base case: no more row
    // do nothing
    
    // recursive case: 1 or more row
    // print the current row 
    // apply to next row
    if ( y < height )
    {
	print_row (image, iterate, x, y, width, height); 
	mandelbrot (image, iterate, x, y+1, width, height);
    }
	
    return;
} // mandelbrot ends

/*
Function: print_row

Purpose:  write a given row of the image of the mandelbrot set

Details:  This function writes only the given row of the image by traversing 
          each pixel in the row recursively. For example, a 1000x1000 image will
	  have 1000 columns, so each row has 1000 pixel.

	  The base case of this function is when the current pixel is the final 
	  column in the row. This function will print the pixel (by passing to
	  print_pixel()) and reset the number of column back to 0 (and send back
	  to the caller).

	  The recursive case of this function is when there is still column(s)
	  to traverse. This function will also print the pixel (by passing to 
	  print_pixel()) and apply the algorithm to the rest of pixels of the 
	  current row.

	  To print the current pixel each time, this function also convert its
	  pixel coordinates (x,y) to its corresponding complex values displayed  
	  on cartesian coordinates (a,b). The algorithm is as follows:

	  For any complex values a+bi, a represents the real component and b 
	  represents the complex component, where a is on the x-axis and b is on
	  the y-axis.

	    a = "minimum value of a" + (x / width) * "number of units on x-axis"
	    b = "maximum value of b" - (y / height) * "number of units on y-axis"

	  In our case, the maximum and minimum value of a are 0.5 and -1.5, while 
	  those of b are 1 and -1. Take pixel (3,3) in a 1000x1000 image as 
	  example, we have

	    a = -1.5 + 3/1000 * (0.5-(-1.5))
	      = -1.5 + 3/1000 * 2
	      = -1.494

	    b = 1 - 3/1000 * (1-(-1))
	      = 1 - 3/1000 * 2
	      = 0.994
	      
	  The complex value is -1.494 + 0.994i, which is represented in cartesian
	  coordinates as (-1.494, 0.994).

Input:
          iterate   - an integer that is the  number of iterations requested
	  y         - an integer that is the current number of row (by pixel)
	  width     - an integer that is the width of the image
	  height    - an integer that is the height of the image
Output:
          image     - an image that the the function writes on
	  x         - an integer that is the current number of column (by pixel)
Return:
          n/a

*/

void print_row (Image &image,
		 int iterate,
		 int &x,
		 int y,
		 int width,
		 int height)
{
    const double a_low = -1.5; // lowest real component
    const double a_high = 0.5; // highest real component
    const double b_low = -1.0; // lowest complex component
    const double b_high = 1.0; // highest complex component
    int count = 1;

    // convert from pixel coordinates (x, y)
    // to its  corresponding complex values on cartesian coordinates (a, b)
    double a_unit = a_high - a_low; // unit of real components
    double b_unit  = b_high - b_low; // unit of imaginary components
    double a = a_low + (x/static_cast<double>(width)) * a_unit; // real component
    double b = b_high - (y/static_cast<double>(height)) * b_unit; // complex component

    // print the current pixel
    print_pixel (image, iterate, count, x, y, a, b, a, b);

    // base case: final pixel on current row
    // update column number
    if ( x == width - 1 )
    {
	x = 0;
    }
    // recursive case: 1 or more pixels on current row
    // apply to next pixel
    else if ( x != width -1 )
    {
	x++;
	print_row (image, iterate, x, y, width, height);
    }
    return;
} // print_row ends

/*
Function: print_pixel

Purpose:  write a given pixel of the image of the Mandelbrot set

Details:  This function writes only the given pixel of the image by determining
          whether pixel is within the mandelbrot set.
	  
	  To determine, this function calculate the value of the Mandelbrot
	  function Z_n:
	  
	         Z_{n+1} = Z_n^2 + c

		 where c is a complex number a + bi, 
		 and Z_0 = 1.

	  A complex number c is in the Mandelbrot set if the sequence described 
	  (z0, z1, …) does not reach infinity. 

	  To simplify matters, it has been shown that any of the above sequences 
	  that contains a value whose distance from the origin (using the 
	  Pythagorean Theorem) is 2 or more will end up as infinity. Therefore 
	  a complex number c is in the Mandelbrot set if the sequence does not 
	  contain any values that are more than 2 from the origin. For example, 


	  This function calculate this function recursively, with two base cases
	  and one recursive case.
	  
	  The first base case is when the distance of the value of is more than 2.
	  This function will determine the pixel as out of Mandelbrot set and 
	  will print the corresponding colors.
	  
	     The design of this color mapping gives areas farthest from the 
	     Mandelbrot set a darker tone. For areas closer to the the set, 
	     it would gradually become green-and-blueish and eventually pink 
	     and white, with an aesthetics of "Night Sakura in Tokyo".

	     While users can enter any number of interger under the limit. It 
	     is suggested to enter least 20, as the first 20 iterations will 
	     bring the color from black to green-and-blusish color.
 
	 The second base case is when the number of iterations reach the target
	 but the distance of the value to the origin sill remains under 2. This
	 function wil determine the pixel as within the Mandelbrot set and 
	 will print the corresponding color, which is black.

	 The recursive case is when the distance of the value to the origin is
	 under 2 but the number of iteretions hasn't reach the target. This 
	 function will calculate the values of the next sequence and apply the 
	 algorithm to the rest of the sequences. The calculation is as follows:
	 
	    for any sequence n, the complex value is

	         z_n = z_{n-1}^2 + c
		     = z_{n-1}^2 + (c_a + c_b*i)
		     = (z_a + z_b*i)^2 + (c_a + c_b*i)
		     = (z_a)^2 + 2(z_a)(z_b*i) + (z_b)^2 + c_a + (c_b*i)
		     = [(z_a)^2 + (z_b)^2 + c_a] + [2(z_a)(z_b*i) + (c_b*i)]
		     = [(z_a)(z_a) + (z_b)(z_b) + c_a] + [2(z_a)(z_b) + c_b]*i

	    from these, we can get the value of z_n in a form of a+bi, the real 
	    and complex components of which can be respectively passed to the 
	    next sequence for resursive calculation, where
	    
	     z_{n+1} = [(z_a)(z_a) + (z_b)(z_b) + c_a] + [2(z_a)(z_b) + c_b]*i
	               + (c_a + c_b*i)
	  
Input:
          iterate   - an integer that is the  number of iterations requested
	  x         - an integer that is the current number of column (by pixel)
	  y         - an integer that is the current number of row (by pixel)
	  z_a       - a double that is the real component of the current sequence
	              of function, such that z_n = z_a + z_bi
	  z_b       - a double that is the complex component of the current 
	              sequence of function, such that z_n = z_a + z_bi
	  c_a       - a double that is the real component of the complex number
	              c, such that z_{n+1} = z_n^2 + c 
	  c_b       - a double that is the complex component of the complex 
	              number c, such that z_{n+1} = z_n^2 + c
Output:
          image     - an image that the the function writes on
Return:
          n/a

*/
    
void print_pixel (Image &image,
		  int iterate,
		  int count, 
		  int x,
		  int y,
		  double z_a,
		  double z_b,
		  double c_a,
		  double c_b)
{
    const double min_iterate = 20.0;
    Color outer;
    double inc;
    double hue;
    double temp;
    double dist_pow =  z_a*z_a + z_b*z_b;

    // base case 1: distance of complex number to origin is 2 or more
    // print pixel according to number of iterations
    if ( dist_pow >= 4 )
    {
	    
	// minimum iterations
	if ( count <= min_iterate )
	{
	    hue = ( count / min_iterate ) * 0.25;
	    inc = ( count / min_iterate ) * 0.75;
	    outer = ColorHSL ((0.45+hue), inc, inc);
	}
	// after minimum iteratations
	else
	{		    
	    hue = ( (count-min_iterate) * (0.3 / (iterate-min_iterate)) );
	    inc = ( (count-min_iterate) * (0.25 / (iterate-min_iterate)) );
	    outer = ColorHSL ((0.7+hue), (0.75+inc), (0.75+inc));
	}
	image.pixelColor (x, y, outer);
    }
    else
    {	
	// base case 2: distance less than 2 & iterations reach limit
	// print pixel
	if ( count == iterate )
	{
	    image.pixelColor (x, y, "black");
	}
	// recursive case: distance less than 2 & iterations hasn't reach limit
	// (1) calculate the new values for next sequence
	// (2) apply the algorithm for the rest of the sequences
	else
	{
	    temp = (z_a*z_a) - (z_b*z_b) + c_a;
	    z_b = 2*z_a*z_b + c_b;
	    z_a = temp;
	    print_pixel (image, iterate, count+1, x, y, z_a, z_b, c_a, c_b);
  	}
    }
    
    return;
} // print_pixel ends

