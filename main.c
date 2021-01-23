#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define PREFIX "movies_"
#define POSTFIX "csv"



int main(void) {
  DIR* currDir;
  int choice;
  int filechoice;
  printf("1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
  scanf("%d", &choice);

  switch(choice)
  {
    case 1:
      printf("Which file do you want to process?\n");
      printf("Enter 1 to pick the largest file\n");
      printf("Enter 2 to pick the smallest file\n");
      printf("Enter 3 to specify the name of a file\n");
      printf("Enter a choice from 1 to 3:");
      scanf("%d", &filechoice);
      break;
    case 2:
      printf("Program Terminated....I'll be back.\n");
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("nah son, try again!\n");
      break;
  }

  switch(filechoice)
  {
    case 1:
      // Program finds the largest file with the extension csv
      // in the current directory whose name starts with the 
      // Prefix "movies_" and automatically process it
      // Open Current Directory
      currDir = opendir(".");
      struct dirent *aDir;
      struct stat dirStat;
      int filesize = 0;
      char *movieTitle;

      // Go through all the entries
      while((aDir = readdir(currDir)) != NULL)
      {
        
        // Find file that has the Prefix "movies_"
        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0)
        {
          stat(aDir->d_name, &dirStat);
          int size = dirStat.st_size;
          printf("The size of the file is: %d\n", size);
          // Find file with extension csv
          // Set delimiter to a dot to split file name and file type
          char* token = strtok(aDir->d_name, ".");
          // name of file without extension
          printf("File name is: %s\n", token);
          // end of the string
          token = strtok(NULL, " ");
          // the file type
          printf("the file type is %s\n", token);
          // Checks if the file type is csv
          if (strcmp(token, "csv") == 0)
          {
            // Get meta-data for the current entry
            //stat(aDir->d_name, &dirStat);
            //int size = dirStat.st_size;
            //printf("The size of the file is: %d\n", size);
            
            // Find the largest file
            if (filesize <= size)
            {

            }
          }
        }
        
      }
      printf("Now processing the chosen file named %s", movieTitle);
      // Close Directory
      closedir(currDir);
      break;
    case 2:
      // Program finds the smalles file with the extension csv 
      // in the current directory whose name start wityh the
      // Prefix "movies_" and automatically process it
      break;
    case 3:
      // Program asks the user to enter the name of a file
      // Program checks if this file exists in the current directory
      // If the file is not found, print an error message
      // and repeat the instructions about picking a file.
      break;
    default:
      break;
  }
  return 0;
}