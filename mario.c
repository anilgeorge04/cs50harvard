// This program builds a pyramid (of hashes) of height specified by the user
// Example: If user inputs height 8 when prompted, the pyramid must look like this:
//          #  #
//         ##  ##
//        ###  ###
//       ####  ####
//      #####  #####
//     ######  ######
//    #######  #######
//   ########  ########

#include <cs50.h>
#include <stdio.h>

void buildpyramid(int n);

int main(void)
{
    int n = 0;
    printf("\n** MARIO ** \nYou will now build a pyramid that Mario must jump over. ");
    printf("\nInstructions: Input pyramid height must be >=1 and <=8.\n");
    do
    {
        n = get_int("Enter height: ");
    }
    while (n < 1 || n > 8);
    buildpyramid(n);
}

// Function builds the pyramid to specified height
void buildpyramid(int n)
{
    int row = 1, i = 0, j = 0, k = 0;
    // Builds row by row with 3 loops - spaces, left hashes, right hashes
    while (row <= n)
    {
        // Loop 1: Spaces on the left
        for (j = n; j > row; j--)
        {
            printf(" ");
            // printf("_");
        }
        // Loop 2: Hashes on the left
        for (i = 0; i < row; i++)
        {
            printf("#");
        }
        // Centre space
        printf("  ");
        // printf("__");
        // Loop 3: Hashes on the right
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        row++;
        printf("\n");
    }
    // printf("Mario, go jump!\n");
}
