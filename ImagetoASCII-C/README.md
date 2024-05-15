This is one of my favorite projects! This C program converts ppm images (only supports type p6 ppm images as of 5/24) into ASCII art. It uses the equation (0.2126 * red) + (0.7152 * green) + (0.0722 * blue) to find the "brightness" of a pixel. 
To use this program, pass the ppm file to the program's executable as a command line argument, like this:
./a.out pic.ppm
I have also attatched a screenshot showing the program running with an image of a stop sign.
Note that if you try to use an image that is too large, the characters won't fit on your terminal and the ASCII art will be warped. 
