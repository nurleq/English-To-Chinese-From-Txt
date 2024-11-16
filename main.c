#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024
#define MAX_LINE_LENGTH 500

void translateAndWrite(char *inputFile, char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
        perror("Failed to open input file");
        return;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        perror("Failed to open output file");
        fclose(input);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Translate each word using curl and grep
        for (char *word = strtok(line, " "); word != NULL; word = strtok(NULL, " ")) {
            char translatedLine[MAX_LINE_LENGTH];
            snprintf(translatedLine, MAX_LINE_LENGTH, "%s\n", word);

            FILE *translatedInput = fopen("temp.txt", "w");
            if (translatedInput == NULL) {
                perror("Failed to create temporary file");
                fclose(output);
                fclose(input);
                return;
            }

            fprintf(translatedInput, "%s", translatedLine);
            fclose(translatedInput);

            char command[1024];
            snprintf(command, sizeof(command), "curl -X GET \"https://translate.googleapis.com/language/translate/v2?key=YOUR_API_KEY&q=%s&target=zh-CN\" | grep 'translatedText' | sed 's/.*:\"//;s/\",\\?//'",
                    word);

            FILE *translatedOutput = popen(command, "r");
            if (translatedOutput == NULL) {
                perror("Failed to execute command");
                fclose(output);
                fclose(input);
                return;
            }

            char translatedLine[2048];
            while (fgets(translatedLine, 2048, translatedOutput)) {
                char *start = translatedLine;
                char *end = strstr(start, "\"\"");
                if (end != NULL) {
                    char translatedWord[256];
                    strncpy(translatedWord, start + 3, end - start - 3);
                    translatedWord[end - start - 4] = '\0';

                    fprintf(output, "%s ", translatedWord);
                }
            }

            pclose(translatedOutput);
        }

        // Print a newline after the line
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);
}

int main() {
    char inputFile[MAX_INPUT_SIZE];
    char outputFile[MAX_INPUT_SIZE];

    printf("Enter the path to the input English file: ");
    fgets(inputFile, MAX_INPUT_SIZE, stdin);
    inputFile[strcspn(inputFile, "\n")] = 0;

    printf("Enter the path to the output Chinese file: ");
    fgets(outputFile, MAX_INPUT_SIZE, stdin);
    outputFile[strcspn(outputFile, "\n")] = 0;

    translateAndWrite(inputFile, outputFile);

    return 0;
}