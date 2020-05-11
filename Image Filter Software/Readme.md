**IMAGE FILTER**
This is a program to place filters on your BITMAP images. Filters included:
- Grayscale: Shifts image to Grayscale (use -g)
- Reflected: Vertical mirror image (use -r)
- Blur: Get a slightly more blurred version of your image (use -b)
- Edges: Clearly identify the edges within your image where colors change (use -e)
  
**How to use?**
1. Place your image within the "images" sub-folder
2. Compile the program
3. Execute the program using the flag for filter
4. Get your final product in "outfile.bmp" and use it as you'd like

Example: $ ./filter -g infile.bmp outfile.bmp
Takes in "infile.bmp" placed in "images" subfolder and produces filtered 'grayscale' (-g) image "outfile.bmp" (provided valid input file)

*Note:*
1. "helpers.c" contains the source code for each filter
2. Other files help compile & run the overall software using "Makefile"
