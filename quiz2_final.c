#include <stdio.h>
#include <stdlib.h> //for atoi function
#include <string.h>
#include <ctype.h>  // For isdigit function


// Structure to store questions, options, and correct answers
struct Question {
    char question[256];
    char options[4][256];
    int correctOption;
};

// Function declarations
void playQuiz(int category);
void askQuestion(struct Question q, int *score);
int loadQuestionsFromFile(struct Question questions[], int category);
int categoryMenu();
int playAgain();

int main() {
    while (1) {
        int category = categoryMenu();
        playQuiz(category);
        if (!playAgain()) {
            break;
        }
    }
    return 0;
}

void playQuiz(int category) {
    struct Question questions[10];
    int numQuestions = loadQuestionsFromFile(questions, category);
    
    if (numQuestions == 0) {
        printf("No questions found for this category.\n");
        return;
    }

    int score = 0;
    for (int i = 0; i < numQuestions; i++) {
        askQuestion(questions[i], &score);
    }
    
    printf("\nYour final score is: %d points\n", score);
}

void askQuestion(struct Question q, int *score) {
    printf("\n%s\n", q.question);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, q.options[i]);
    }
    
    int userAnswer;
    char buffer[256];
    
    while (1) {
        printf("Enter your answer (1-4): ");
        scanf("%s", buffer);  // Read input as a string to handle any input

        // Check if input is a valid integer within the range of 1-4
        if (sscanf(buffer, "%d", &userAnswer) == 1 && userAnswer >= 1 && userAnswer <= 4) {
            break;  // Valid input, break out of the loop
        } else {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
        }
    }
    
    if (userAnswer == q.correctOption) {
        printf("Correct!\n");
        *score += 5;
    } else {
        printf("Wrong! The correct answer was %d\n", q.correctOption);
    }
}


// Load questions from file based on the selected category
int loadQuestionsFromFile(struct Question questions[], int category) {
    FILE *file = fopen("A:\\language_C\\questions.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0;
    }

    char buffer[256];
    int questionCount = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        // Read question
        strcpy(questions[questionCount].question, buffer);
        
        // Read options
        for (int i = 0; i < 4; i++) {
            fgets(questions[questionCount].options[i], sizeof(buffer), file);
        }

        // Read correct answer
        fgets(buffer, sizeof(buffer), file);
        questions[questionCount].correctOption = atoi(buffer);

        // Read category
        fgets(buffer, sizeof(buffer), file);
        int questionCategory = atoi(buffer);

        // Skip empty line
        fgets(buffer, sizeof(buffer), file);

        // Check if the question belongs to the selected category
        if (questionCategory == category) {
            questionCount++;
        }

        if (questionCount == 10) {
            break;  // Only load 10 questions per category
        }
    }

    fclose(file);
    return questionCount;
}

int categoryMenu() {
    char input;
    int category;

    while (1) {
        printf("Choose a category:\n");
        printf("1. Science\n");
        printf("2. Geopolitics\n");
        printf("3. Space\n");
        printf("4. Geography\n");
        printf("Enter the number of the category (1-4): ");

        input = fgetc(stdin);  // Get a single character from user input

        // Check if the input is a digit and between '1' and '4'
        if (isdigit(input) && input >= '1' && input <= '4') {
            category = input - '0';  // Convert character to integer
            break;  // Exit loop if input is valid
        } else {
            printf("Invalid input. Please enter a number between 1 and 4.\n");

            // Consume any extra characters from the input buffer (like newline)
            while (fgetc(stdin) != '\n');
        }
    }

    return category;  // Return the valid category number
}


int playAgain() {
    char choice;
    printf("\nDo you want to play again? (y/n): ");
    scanf(" %c", &choice);
    return choice == 'y' || choice == 'Y';
}



