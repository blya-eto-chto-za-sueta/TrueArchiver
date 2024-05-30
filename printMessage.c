#include <stdio.h>
#include "printMessage.h"

void first_start_message() {
    printf("Hello! You are going to use \"TrueArchiver\", but don't know how to use it at all. \nI suggest you restart the program along with the -h flag to get help about the operation of this archiver.\n");

    printf("Press 'Enter' to close the first start message");
    getchar();

}
void help_message() {
    printf("Hello! Before starting work, I suggest getting to know each other a little.\n");
    printf("I am Ilya Trushkin - the author of this project and I am finishing 1st year at NSU of the Deep Robotics faculty.\n\n");
    printf("Now I'll tell you a little about my project:\n");
    printf("1) My program performs the functions of an archiver and can compress and decompress data.\n");
    printf("2) The program is based on the Huffman data archiving algorithm.\n");
    printf("3) \"TrueArchiver\" has a User-Friendly Interface (if you do something wrong, the program will say what the problem is and what to do.)\n");
    printf("\n");
    printf("----INSTRUCTIONS \"TrueArchiver\"----\n");
    printf("First of all, place the files you want to work with in the “Debug” (\"TrueArchiver\") folder.\n");
    printf("1) If you want to compress file, enter the file name and name of a file-archive.\nFor example:\n 'TrueArchiver.exe -c file.txt arch.newZip'.\n");
    printf("2) If you want to decompress file, enter the file-archive and name of file-result.\nFor example:\n 'TrueArchiver.exe -d arch.newZip file.txt'.\n\n");

    printf("----IMPORNANT----\n");
    printf("\"TrueArchiver\" can't work with several files simultaneously.\n");
    printf("You can't open and read file-archive.\n");
    printf("----PROGRAM FLAGS AND THEIR DESCRIPTIONS----\n");

    printf("1) '-h' -help message.\n");
    printf("1) '-c' -compress file.\n");
    printf("2) '-d' -decompress file.\n\n");

    printf("----REMEMBER----\n");
    printf("1) If file is too little, its file-archive can be even bigger.\n");
    printf("2) If file is quite big, it can took time to compress or decompress it.\n");

    printf("Press 'Enter' to close the instruction.");
    getchar();

}


void invalid_file_format_1() {
    printf("Wrong format of second file (it should be'.newZip')! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void invalid_file_format_2() {
    printf("Wrong format of first file (it should be'.newZip')! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void missing_file_1() {
    printf("You forgot to enter file-archive! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void missing_file_2() {
    printf("You forgot to enter file-start and file-archive! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void missing_file_3() {
    printf("You forgot to enter file-result! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void missing_file_4() {
    printf("You forgot to enter file-archive and file-result! Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void operation_not_detected() {
    printf("You forgot to write what to do or operation is unknown! The program can only:\n");
    printf("     '-c' - compress file (example: 'TrueArchiver.exe -c file.txt arch.newZip');\n");
    printf("     '-d' - decompress file (example: 'TrueArchiver.exe -d arch.newZip file.txt')\n");
    printf("Or, maybe, you entered a name of a file without any operations.\n");
    printf("Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}

void message_about_incorrect_data() {
    printf("You did something wrong! Our team is already working to identify such errors.\n");
    printf("Please, try again.\nIf you need help, run program againg and enter '-h'.");
    getchar();
}


void compress_file_start_opening_error() {
    printf("Unfortunately, file for compressing can't be opened! Check if it exists and locates in the folder 'Debug' and 'TrueArchiver'. ");
    getchar();
}

void compress_file_result_opening_error() {
    printf("Unfortunately, file in which you are going to compress previous file can't be opened! Check if it exists and locates in the folder 'Debug' and 'TrueArchiver'. ");
    getchar();
}

void decompress_file_archive_opening_error() {
    printf("Unfortunately, file for decompressing can't be opened! Check if it exists and locates in the folders 'Debug' and 'TrueArchiver'. ");
    getchar();
}

void decompress_file_result_opening_error() {
    printf("Unfortunately, file in which you are going to decompress previous file can't be opened! Check if it exists and locates in the folder 'Debug' and 'TrueArchiver'. ");
    getchar();
}

void empty_file_compress() {
    printf("File exists but has no information (nothing to archive).");
    getchar;
}

void compress_performance() {
    printf("Compressing...Please, wait...\n");
}

void compress_complited() {
    printf("\nCompressed successfully!\n");
}

void empty_file_decompress() {
    printf("File exists but has no information (nothing to dearchive).");
    getchar;
}

void decompress_performance() {
    printf("Decompressing...Please, wait...\n");
}

void decompress_complited() {
    printf("\nDecompressed successfully!\n");
}