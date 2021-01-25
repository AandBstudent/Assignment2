#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define PREFIX "movies_"
#define POSTFIX "csv"

/* struct for movie data */
struct movie
{
  char *title;
  char *year;
  char *rating;
  char *languages;
  struct movie *next;
};

/* Parse the current line which is space delimited and create a
*   movie struct with the data in this line
*/
struct movie *createMovie(char *currLine)
{
    // Memory allocation, Remember to free at the end of program
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    // CSV, Comma Seperated Values----V
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The second token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // Set the next node to NULL in the newly created movie entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified line.
*/
struct movie *processFile(char *filePath)
{
  // Open the specified file for reading only
  FILE *movieFile = fopen(filePath, "r");

  // Variables
  char *currLine = NULL;
  size_t len = 0;
  ssize_t nread;
  char *token;

  // The head of the linked list
  struct movie *head = NULL;
  // The tail of the linked list
  struct movie *tail = NULL;

  // Read the file line by line
  while ((nread = getline(&currLine, &len, movieFile)) != -1)
  {
      // Get a new movie node corresponding to the current line
      struct movie *newNode = createMovie(currLine);

      // is this the first node in the linked list?
      if (head == NULL)
      {
          // This is the first node in the linked list
          // Set the head and tthe tail to this node
          head = newNode;
          tail = newNode;
      }
      else
      {
          // This is not the first node.
          // Add this node to the list and advance the tail
          tail->next = newNode;
          tail = newNode;
      }
  }
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given movie
*/
char *printMovie(struct movie* aMovie)
{
  char *title = aMovie->title;
  char *newLine = "\n";
  strcat(title, newLine);
  return title;
}

/*
* Print the link list of mooovies with the year 
*/
void printMovieList(struct movie *list, char *path)
{
  char *tempTXT = ".txt";
  // Create root for file
  char temp = *path;
  char *newFilePath = calloc(strlen(path)+1, sizeof(char));
  strcpy(newFilePath,path);
  while(list != NULL)
  {
    int fd;
    // Get the year of the movie
    char *yearC = list->year;
    // Copies into the pathname
    strcat(newFilePath, yearC);
    // Format is YEAR.txt.
    strcat(newFilePath, tempTXT);
    // Open a file for with read/write permissions for owner and read for group.
    // Append if it already exists.
    fd = open(newFilePath, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);
    write(fd,printMovie(list),strlen(list->title));
    // Restart file pathname
    strcpy(newFilePath, path);
    list = list->next;
    close(fd);
  }
}

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
        char *tempString = ".csv";
        strcat(movieTitle, tempString);
        printf("Now processing the chosen file named %s\n", movieTitle);
        // Create the name of the file
        char fileName[256];
        char src[10];
        char dest[10];
        char num[11];
        char slash[2];
        strcpy(src, "renaudtp");
        strcpy(dest, ".movies.");
        strcat(src, dest);        
        long int randomNum = random();
        int length = snprintf(NULL, 0, "%ld", randomNum);
        char *str = malloc(length+1);
        snprintf(str, length + 1, "%ld", randomNum);
        strcat(src, str);
        char *pathname = src;
        // Make a new directory
        mkdir(pathname, 0750);
        // renaudtp.movies.randomnumber
        // With permissions rwxr-x--- / 0750
        // Print a message with the name of the directory that was created
        printf("Directory %s has been created.\n", src);
        struct movie *list = processFile(movieTitle);
        // Skip Title, Year
        list = list->next;
        strcpy(slash, "/");
        strcat(pathname, slash);
        printMovieList(list, pathname);
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
        char *tempString2 = ".csv";
        strcat(movieTitleS, tempString2);
        printf("Now processing the chosen file named %s\n", movieTitleS);
        // Create the name of the file
        char fileName2[256];
        char src2[10];
        char dest2[10];
        char num2[11];
        strcpy(src2, "renaudtp");
        strcpy(dest2, ".movies.");
        strcat(src2, dest2);        
        long int randomNum2 = random();
        int length2 = snprintf(NULL, 0, "%ld", randomNum2);
        char *str2 = malloc(length2+1);
        snprintf(str2, length2 + 1, "%ld", randomNum2);
        strcat(src2, str2);
        char *pathname2 = src2;
        // Make a new directory
        mkdir(pathname2, 0750);
        // renaudtp.movies.randomnumber
        // With permissions rwxr-x--- / 0750
        // Print a message with the name of the directory that was created
        printf("Directory %s has been created.\n", src2);
        struct movie *listS = processFile(movieTitleS);
        // Skip Title, Year
        listS = listS->next;
        strcpy(slash, "/");
        strcat(pathname2, slash);
        printMovieList(listS, pathname2);
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
            // Create the name of the file
            char fileName3[256];
            char src3[10];
            char dest3[10];
            char num3[11];
            strcpy(src3, "renaudtp");
            strcpy(dest3, ".movies.");
            strcat(src3, dest3);        
            long int randomNum3 = random();
            int length3 = snprintf(NULL, 0, "%ld", randomNum3);
            char *str3 = malloc(length+1);
            snprintf(str3, length3 + 1, "%ld", randomNum3);
            strcat(src3, str3);
            char *pathname3 = src3;
            // Make a new directory
            mkdir(pathname3, 0750);
            // renaudtp.movies.randomnumber
            // With permissions rwxr-x--- / 0750
            // Print a message with the name of the directory that was created
            printf("Directory %s has been created.\n", src3);
            struct movie *list3 = processFile(movieFind);
            // Skip Title, Year
            list3 = list3->next;
            strcpy(slash, "/");
            strcat(pathname3, slash);
            printMovieList(list3, pathname3);
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