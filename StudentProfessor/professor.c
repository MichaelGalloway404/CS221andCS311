/*
professor.c 

Michael Galloway, Fall 2023

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char **argv){

    char *prog = "student";
    char **args = NULL;

    //create two uni-directional pipes
    int prof_to_student[2];
    int student_to_prof[2];
    int child_pid;
    
    //one for professor to student, one from student to professor
    pipe(prof_to_student); 
    pipe(student_to_prof); 

    //fork to create a child process
    child_pid = fork();

    //child portion
    //need two calls to dup2, two calls to close, and a call to execv
    if (child_pid == 0) { 
      dup2(prof_to_student[0],0);  
      dup2(student_to_prof[1],1); 
      
      close(prof_to_student[1]);
      close(student_to_prof[0]);
    
      execv(prog, args);
      // NOT REACHED
    } 

    //parent portion
    //need two calls to dup2
    dup2(prof_to_student[1],1); 
    dup2(student_to_prof[0],0); 

    //close unused half of pipes
    close(prof_to_student[0]);
    close(student_to_prof[1]);

    while (1){
        
        fprintf(stderr,"\tprof: waiting for question\n");
        fflush(stderr);

        //read a question from standard input
        char response[2];
        read(0,response,2);
        fprintf(stderr,"\tprof: question read: %s\n",response);

        //choose an answer based on the question and write the response to standard output
        if(response[0] == '1'){
          write(1,"silly question",15);
        }
        else if(response[0] == '2'){
          write(1,"good question",14);
        }
        else if(response[0] == '3'){
          write(1,"smart question!",16);
        }
        else if(response[0] == '4'){
          write(1,"I don't know",13);
        }
        fprintf(stderr,"\tprof: wrote responce\n");
    }
    exit(1); //clean up if program is terminated
}

