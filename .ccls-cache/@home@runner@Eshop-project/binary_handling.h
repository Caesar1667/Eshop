#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a csv file to binary file
void csv_to_binary(const char *csv_file, const char *binary_file) {
    FILE *csv = fopen(csv_file, "r");
    if (csv == NULL) {
        printf("Error opening CSV file.\n");
        return;
    }
    FILE *binary = fopen(binary_file, "wb");
    if (binary == NULL) {
        printf("Error opening binary file.\n");
        fclose(csv);
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), csv)) {
        char *token = strtok(line, ","); //assign the string right before each "," to token
        while (token != NULL) {
            int value = atoi(token);
            fwrite(&value, sizeof(int), 1, binary); //write the value to the binary file
            token = strtok(NULL, ",");
        }
    }
}