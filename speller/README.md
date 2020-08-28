# Spell Checker
This program identifies spelling errors in an (input) text file, by checking against a dictionary of words (input or default). It does this efficiently using a simple **Hash Table**.

#### Actions Performed

- Load words from a dictionary (insert into a hash table)
- Check for words from an input text file in the dictionary (search hash table)
- List the misspelt words (not found in hash table)

Other outputs: load time, search time, unload time, size of dictionary, size of file

#### How to use
- Run the makefile using "make" or "make speller" (uses clang to compile). This combines the binaries from dictionary.c and speller.c
- To run the program after building, you can optionally pass in your own dictionary file. If not passed, it picks a default dictionary file "dictionaries/large" which contains 143,091 words

Run command: `./speller [dictionary] text`

- Example 1: `./speller dictionaries/small texts/cat.txt`
    picks small as input dictionary file to load into hash table and check for words in cat.txt input file

- Example 2: `./speller texts/lalaland.txt`
    uses the default dictionaries/large to check words within lalaland.txt input file 

##### Build on
- Feel free to use any text files as input for the spell check and your custom dictionary depending on your use case
- Adjust the table size (i.e. number of slots in the hash table) depending on your dictionary and input file

---
##### Credit: Hash algorithm

- Rob Edwards, San Diego State University: [Hash functions for Strings](https://www.youtube.com/watch?v=jtMwp0FqEcg)
- Blog: <a href = https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/>Why hash functions use prime numbers?</a>
 