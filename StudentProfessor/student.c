/*
student.c 

Michael Galloway, Fall 2023

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char **argv){
    
    while (1){
        
        //seed random number generator
        srand(time(NULL));
        
        //sleep for a random amount between 5 and 15 seconds to simulate studying
        int studyTime = (rand() % 11) + 5; // gen a num btw 5-15
 
        fprintf(stderr,"Student: Studying for %d secounds\n",studyTime);
        sleep(studyTime);

        //randomize a single digit question number: 1,2,3 or 4
        int studentQuestion = (rand() % 4) + 1; // gen a num btw 1-4
        
        //write the random question number to standard output
        fprintf(stderr,"Student: asking question: %d\n",studentQuestion);
        // convert from int to char
        char numberToString[2];
        snprintf(numberToString,2,"%d",studentQuestion);
        fprintf(stderr,"Student: waiting for answer\n");
        write(1,numberToString,2);
        

        //wait for a response from standard input
        char response[20];
        read(0,response,20); // reads from stdin up to 20 chars
        
        //print the response to stderr
        fprintf(stderr,"Student: recieved answer: %s\n",response);
        fprintf(stderr,"******************************\n");
    }
    exit(1); //clean up if program is terminated
}

