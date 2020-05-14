This program reads through a raw file from a memory card "card.raw" in blocks of 512 bytes, and recovers .JPEG files from the raw file by recognizing the standard header format for JPEG files

Assumptions: 
1. JPEG files are stored back to back in the raw file
2. The JPEG files are block-aligned to 512 bytes
