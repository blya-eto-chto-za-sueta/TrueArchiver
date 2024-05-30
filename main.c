#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "printMessage.h"
#include "compress.h"
#include "decompress.h"

int correct_file_format_check(char* fileExtension);
int general_check(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    int checkFlag;
    checkFlag = general_check(argc, argv);
    return 0;
}


int correct_file_format_check(char* fileExtension) {
    int len = strlen(fileExtension);
    //required extension .newZip
    if (fileExtension[len-1] == 'p'
        && fileExtension[len-2] == 'i'
        && fileExtension[len-3] == 'Z'
        && fileExtension[len-4] == 'w'
        && fileExtension[len-5] == 'e'
        && fileExtension[len-6] == 'n' ) {
        return 1;
    }

    return 0;
}

int general_check(int argc, char* argv[]) {

    if (argv[1] == NULL){
        first_start_message();
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0) {
        help_message();
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0 && argv[2] != NULL && argv[3]!= NULL && correct_file_format_check(argv[3]) == 1) {
        compress_file(argv[2], argv[3]);
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0 && argv[2] != NULL && argv[3]!= NULL && correct_file_format_check(argv[2])) {
        decompress_file(argv[2], argv[3]);
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0 && argv[2] != NULL && argv[3]!= NULL && !correct_file_format_check(argv[3])) {
        invalid_file_format_1();
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0 && argv[2] != NULL && argv[3]!= NULL && !correct_file_format_check(argv[2])) {
        invalid_file_format_2();
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0 && argv[2] != NULL && argv[3] == NULL)
    {
        missing_file_1();
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0 && argv[2] == NULL)
    {
        missing_file_2();
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0 && argv[2] != NULL && argv[3] == NULL)
    {
        missing_file_3();
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0 && argv[2] == NULL)
    {
        missing_file_4();
        return 0;
    }

    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0  && strcmp(argv[1], "-h") != 0)
    {
        operation_not_detected();
        return 0;
    }

    else {
        message_about_incorrect_data();
        return 0;
    }
}
