# This program builds a pyramid (of hashes) of height specified by the user
# Example: If user inputs height 8 when prompted, the pyramid must look like this:
#          #  #
#         ##  ##
#        ###  ###
#       ####  ####
#      #####  #####
#     ######  ######
#    #######  #######
#   ########  ########

def main():
    while True:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break

    buildpyramid(height)


def buildpyramid(h):
    row = 1
    # Build 1 row at a time
    while row <= h:
        # spaces on left
        for _ in range(h, row, -1):
            print(" ", end="")

        # hashes on left
        for _ in range(row):
            print("#", end="")

        # centre space gap of 2
        print("  ", end="")

        # hashes on right
        for _ in range(row):
            print("#", end="")

        row += 1
        print()


main()
