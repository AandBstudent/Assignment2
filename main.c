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
  int fileFound = 0;
  printf("1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
  scanf("%d", &choice);

  switch(choice)
  {
    case 1:
      printf("Which file do you want to process?\n");
      printf("Enter 1 to pick the largest file\n");
      printf("Enter 2 to pick the smallest file\n");
      printf("Enter 3 to specify the name of a file\n");
      printf("Enter a choice from 1 to 3: ");
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

  while(!fileFound)
  {
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
            //printf("The size of the file is: %d\n", size);
            // Find file with extension csv
            // Set delimiter to a dot to split file name and file type
            char* token = strtok(aDir->d_name, ".");
            // name of file without extension
            //printf("File name is: %s\n", token);
            // end of the string
            token = strtok(NULL, " ");
            // the file type
            //printf("the file type is %s\n", token);
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
                filesize = size;
                movieTitle = aDir->d_name;
              }
            }
          }
        }
        printf("Now processing the chosen file named %s.csv\n", movieTitle);
        fileFound = 1;
        // Close Directory
        closedir(currDir);
        break;
      case 2:
        // Program finds the smalles file with the extension csv 
        // in the current directory whose name start wityh the
        // Prefix "movies_" and automatically process it
        // Program finds the largest file with the extension csv
        // in the current directory whose name starts with the 
        // Prefix "movies_" and automatically process it
        // Open Current Directory
        currDir = opendir(".");
        struct dirent *aDirS;
        struct stat dirStatS;
        int filesizeS = 1000000000;
        char *movieTitleS;

        // Go through all the entries
        while((aDirS = readdir(currDir)) != NULL)
        {
          
          // Find file that has the Prefix "movies_"
          if(strncmp(PREFIX, aDirS->d_name, strlen(PREFIX)) == 0)
          {
            stat(aDirS->d_name, &dirStat);
            int size = dirStatS.st_size;
            //printf("The size of the file is: %d\n", size);
            // Find file with extension csv
            // Set delimiter to a dot to split file name and file type
            char* token = strtok(aDirS->d_name, ".");
            // name of file without extension
            //printf("File name is: %s\n", token);
            // end of the string
            token = strtok(NULL, " ");
            // the file type
            //printf("the file type is %s\n", token);
            // Checks if the file type is csv
            if (strcmp(token, "csv") == 0)
            {
              // Get meta-data for the current entry
              //stat(aDir->d_name, &dirStat);
              //int size = dirStat.st_size;
              //printf("The size of the file is: %d\n", size);
              
              // Find the largest file
              if (filesizeS >= size)
              {
                filesizeS = size;
                movieTitleS = aDirS->d_name;
              }
            }
          }
        }
        printf("Now processing the chosen file named %s.csv\n", movieTitleS);
        fileFound = 1;
        // Close Directory
        closedir(currDir);
        break;
      case 3:
        // Program asks the user to enter the name of a file
        // Program checks if this file exists in the current directory
        // If the file is not found, print an error message
        // and repeat the instructions about picking a file.
        // Open Current Directory
        currDir = opendir(".");
        struct dirent *aDirF;
        char movieFind[30];
        printf("What file are you looking for?\n");
        scanf("%s", movieFind);
        // Go through all the entries
        while((aDirF = readdir(currDir)) != NULL)
        {
          // Prints file names
          // printf("%s\n", aDirF->d_name);
          // Find file with the same name
          if (strcmp(movieFind,aDirF->d_name) == 0)
          {
            printf("Now processing the chosen file named %s\n",movieFind);
            fileFound = 1;
          }
        }
        if (!fileFound)
        {
          printf("That file does not exist. Do better.\n");
          filechoice = 0;
        }
        
        break;
        default:
          printf("Which file do you want to process?\n");
          printf("Enter 1 to pick the largest file\n");
          printf("Enter 2 to pick the smallest file\n");
          printf("Enter 3 to specify the name of a file\n");
          printf("Enter a choice from 1 to 3: ");
          scanf("%d", &filechoice);
          break;
    }
  }
  return 0;
}