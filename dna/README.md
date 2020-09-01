# DNA Matcher
Written in: Python

This program identifies a person based on their DNA.

#### Quick Background
Program relies on the idea of Short Tandem Repeats (STRs) in the nucelotide sequences of the DNA to perform the match.
<a href="https://www.fbi.gov/services/laboratory/biometric-analysis/codis/codis-and-ndis-fact-sheet">CODIS DNA Databases</a> FAQ to understand DNA match better

#### How to run
It takes as its first command-line argument the name of a CSV file containing the STR counts for a list of individuals. And as its second command-line argument, it takes the name of a text file containing the DNA sequence to identify.

Sample: `python dna.py databases/large.csv sequences/1.txt`