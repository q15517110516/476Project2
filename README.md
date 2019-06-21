# Project 2: Shapefinder
In this one you are building a command line tool which allows users to provide the filename of an image and 3 flags: --shape or -s followed by a shape value (square, rectangle, circle, etc.) and the flag --color or -c followed by a color (like #ff00ff or black) the third flag is -o which allows the user to specify the name of the output image (like output.ppm).

The program needs to create a new image file (at the location specified in the -o flag) which is the original image with a rectangle drawn around and shapes found in the image that match the -s flag. (Detect a square in the image and draw a colored rectangle around it in the output image).

For the image format, make this work with .ppm (or .pbm or .pgm).

I will accept a project which only works on black and white images which only contain clean rectangles. But it's extra credit to those that accept more shapes than just rectangles, and more for more difficult images, yet more for more difficult image formats.

## Project 2 Milestones
This project has many layers so here are some steps towards the simplest layer:

* Convert an image into .ppm format using a tool like ImageMagick (convert input.png output.ppm), this is for you to test with.
* You might even hand craft a small image with just the shape you want.
* Ingest the image and detect pixel data. Since we're using plaintext image formats it's a success just to cout the lines of the image.
* Make your 'flag' system work well, just practice reading in all three and displaying the values that the user provides. Then try to detect valid values or provide error messages.
* Practice creating an image. Try replacing all pixels of color1 with color2 (ignoring the shape part of the program for now).
* On the algorithm side I'm ok if you use OpenCV is a third-party library. But do document the dependencies of your code so the next red-team can compile and run your code. I'm also fine if you start with just black and white rectangles and find the corners and draw in them.
