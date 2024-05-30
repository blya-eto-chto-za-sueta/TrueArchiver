            MINISTRY OF SCIENCE AND HIGHER EDUCATION OF THE RUSSIAN FEDERATION
            FEDERAL STATE AUTONOMOUS EDUCATIONAL INSTITUTION OF HIGHER EDUCATION
                    "NOVOSIBIRSK NATIONAL RESEARCH UNIVERSITY
                STATE UNIVERSITY"(NOVOSIBIRSK STATE UNIVERSITY, NSU)


### Deep Robotics
#### 15.03.06 - Mechatronics and Robotics

### EXPLANATORY NOTE "TrueArchiver"

This project is an Archiver working on the principle of Huffman codes.

## Some about programm
1. My program performs the functions of an archiver and can compress and decompress data.
2. The program is based on the Huffman data archiving algorithm.
3. "TrueArchiver" has a User-Friendly Interface (if you do something wrong, the program will say what the problem is and what to do.

## INSTRUCTIONS

First of all, place the files you want to work with in the “Debug” "TrueArchiver" folder.
1. If you want to compress file, enter the file name and name of a file-archive.
For example: 
 ```bash
'TrueArchiver.exe -c file.txt arch.newZip'
```

2. If you want to decompress file, enter the file-archive and name of file-result.
    
For example: 

``` bash
'TrueArchiver.exe -d arch.newZip file.txt'```
```
### IMPORNANT
1. "TrueArchiver" can't work with several files simultaneously.
2. You can't open and read file-archive.

### PROGRAM FLAGS AND THEIR DESCRIPTIONS
1. '-h' -help message.
2. '-c' -compress file.
3. '-d' -decompress file.


## Archive architecture:

The following data is entered in order in the archive file:


1. length of the Huffman tree (stored as a string) (in bytes); 
2. Huffman tree (string); 
3. encoded data of the source file;
4. information about the end of the file (how many bits are not used in the last byte).

The archive file has the extension “.newZip”.



## Using the program 

#### Compile the program
```bash
gcc *.c -c
gcc *.o -o TrueArchiver
```

#### First launch of the program

```bash
./TrueArchiver
```

Next, the program will tell you about its capabilities and tell you what to do next.

## Error processing
The program checks for errors when opening files, reading and writing data. The program will tell the user about possible causes of the error and ways to solve it.



