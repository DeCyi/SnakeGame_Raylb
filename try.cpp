// C Program to illustrate file opening
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE 256
#define BUFFER_SIZE 256

struct Book {
    char title[CHAR_SIZE];
    char author[CHAR_SIZE];
    char genre[CHAR_SIZE];
    char year[CHAR_SIZE];
    char available[CHAR_SIZE];
};

void read_file(FILE* book_file, struct Book* books) {
    char str[BUFFER_SIZE];
    char data[20][CHAR_SIZE]; // 10 columns, 20 characters each, a temporary array of strings
    char* token;

    fgets(str, BUFFER_SIZE, book_file); // skip the first line

    for (int i = 0; fgets(str, BUFFER_SIZE, book_file) != NULL; i++) // read every line while its not NULL
    {
        token = strtok(str, ",");

        for (int j = 0; token != NULL; j++)
        {
            strcpy(data[j], token);
            token = strtok(NULL, ",");
        }

        strcpy(books[i].title, data[0]);
        strcpy(books[i].author, data[1]);
        strcpy(books[i].genre, data[2]);
        strcpy(books[i].year, data[3]);
        strcpy(books[i].available, data[4]);
    }
}


int main()
{
    FILE* book_file = fopen("books.csv", "r");
    struct Book books[4];

    if (book_file == NULL)
    {
        printf("File not found\n");
        return 1;
    }


    read_file(book_file, books);



    for (int i = 0; i < 4; i++)
    {
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Genre: %s\n", books[i].genre);
        printf("Year: %s\n", books[i].year);
        printf("Available: %s\n", books[i].available);
    }



    fclose(book_file);
    return 0;
}
