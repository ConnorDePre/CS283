#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
int reverse_string(char *buff, int len, int str_len);
int word_print(char *buff, int len, int str_len);
//add additional prototypes here
int str_len(char *);



int setup_buff(char *buff, char *user_str, int len){

    //Uses str_len to find out how big user_str is, if user_str is > 50 than the program exits.
    int userLen = str_len(user_str);
    if(userLen > len){
        printf("The user supplied string is too large\n");
        return -1;
    }


    //The while loop will iterate through the user_str until getting to the null terminated char.
    //i is the current index of user_str.
    //total is used to find out the length of buff after the chars of user_str have been added onto buff.
    int i = 0;
    int total = 0;
    while (*(user_str + i) != '\0'){
        //These two if string check to see if there were multiple white spaces in a row, if there were then
        //nothing will be added to the total and nothing will be added to the buffer.
        if(*(user_str + i) == ' '){
            //printf("user_str: %c\n", *(user_str + i));
            //printf("preUser_str: %c\n", *(user_str + i - 1));
            if(*(user_str + i - 1) == ' '){
                i++;
            }else{        
                *(buff + total) = *(user_str + i);
                total++;
                i++;
            }
        }
        else{
            *(buff + total) = *(user_str + i);
            total++;
            i++;
        }
        //printf("str: %s\n", buff);
    }
    //This is used to find out how many periods are needed to add, then memset will fill out the remaining empty
    //space in the buffer with periods.
    int totalPeriods = len - total;
    memset(buff + total, '.', totalPeriods * sizeof(char));

    return total;
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){

    int totalWords = 0;
    for(int i = 0; i < str_len; i++){
        if(*(buff + i) == ' ' && i < str_len - 1){
            totalWords++;
        }
    }
    totalWords++;

    return totalWords;
}

int reverse_string(char *buff, int len, int str_len){
    int i = 0;
    char curIndex;
    while(i < (str_len / 2)){
        curIndex = *(buff + i);
        *(buff + i) = *(buff + str_len - 1 - i);
        *(buff + str_len - 1 - i) = curIndex;
        i++;
    }

    return 1;
}

int word_print(char *buff, int len, int str_len){
    int total_len = 0;
    int curWord = 1;
    printf("Word Print\n");
    printf("----------\n");
    printf("%d. ", curWord);
    for(int i = 0; i < str_len; i++){
        if(*(buff + i) == ' ' && i < str_len - 1){
            printf(" (%d)\n", total_len);
            total_len = 0;
            curWord++;
            printf("%d. ", curWord);
        }
        else{
            printf("%c", *(buff + i));
            total_len++;
        }
    }

    printf(" (%d)\n", total_len);

    return 1;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

//Take a string and returns the length of the entire string
int str_len(char *str){
    int total = 0;
    int i = 0;
    while (*(str + i) != '\0'){
        total++;
        i++;
    }
    return total;
}




int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      This is safe because the if statement first checks to see if there are < 2 inputs, so if arv[1] does
    //      not exist then program exits.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //  #2 Document the purpose of the if statement below
    //      This is checking to see if a string was provided to be used with the command and if not then it prints
    //      The help message and exits the program
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = malloc(sizeof(char) * BUFFER_SZ);

    if (buff == NULL) {
        printf("Malloc Failed.\n");
        exit(99);
    }



    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
            rc = reverse_string(buff, BUFFER_SZ, user_str_len);
            if (rc < 0){
                printf("Error reversing the string, rc = %d", rc);
                exit(2);
            }

            printf("Reversed Sring: ");
            for (int i = 0; i < user_str_len; i++){
                printf("%c", *(buff + i));
            }
            printf("\n");
            break;
        case 'w':
            rc = word_print(buff, BUFFER_SZ, user_str_len);
            if (rc < 0){
                printf("Error with word print, rc = %d", rc);
                exit(2);
            }
            break;
        case 'x':
            if (argc < 5){
                usage(argv[0]);
                exit(1);
            }
            printf("Not Implemented!\n");
            exit(2);
            break;
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that
//          the buff variable will have exactly 50 bytes?
//
//
//          This is good practice because that variable is 50 for this assignment/exercise, but if
//          we needed to change that to say 35 we would have to go through every single thing we wrote and change
//          50 to 35, but since we used a variable each time, we would just have to change the value of that variable                                           