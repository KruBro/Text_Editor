#include "main.h"

typedef enum {
    C_ADD_LINE,
    C_INSERT,
    C_DELETE,
    C_UNDO,
    C_REDO,
    C_SEARCH,
    C_REPLACE,
    C_PRINT,
    C_INVALID,
    C_EXIT
} TypesOfCommand;

/* Parse command and arguments */
void process_full_command(char *full_line, char **command, char *args[], int *argc)
{
    *argc = 0;

    *command = strtok(full_line, " ");

    while ((*argc < 10) && (args[*argc] = strtok(NULL, " ")))
    {
        (*argc)++;
    }

    args[*argc] = NULL;
}

TypesOfCommand processCommand(char *command)
{
    if (command == NULL)
        return C_INVALID;

    if (strcmp(command, "addline") == 0)
        return C_ADD_LINE;
    else if (strcmp(command, "insert") == 0)
        return C_INSERT;
    else if (strcmp(command, "delete") == 0)
        return C_DELETE;
    else if (strcmp(command, "undo") == 0)
        return C_UNDO;
    else if (strcmp(command, "redo") == 0)
        return C_REDO;
    else if (strcmp(command, "search") == 0)
        return C_SEARCH;
    else if (strcmp(command, "replace") == 0)
        return C_REPLACE;
    else if (strcmp(command, "display") == 0)
        return C_PRINT;
    else if (strcmp(command, "exit") == 0)
        return C_EXIT;
    else
        return C_INVALID;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("[ERROR] : Missing filename argument.\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    TextEditor editor;

    if (initEditor(&editor) == FAILURE)
    {
        printf("[ERROR] : Editor Initialization Failed\n");
        return 1;
    }

    printf("[SUCCESS] : Editor Initialization\n");

    if (openFile(&editor, argv[1]) == FAILURE)
    {
        printf("[ERROR] : OpenFile Failed\n");
        return 1;
    }

    printf("[SUCCESS] : File Opened Successfully\n");

    char *menu[] = {
        "addline <text> - Add a new line",
        "insert <text> - Insert text at the current cursor position",
        "delete - Delete characters from cursor",
        "undo - Undo the last operation",
        "redo - Redo the last undone operation",
        "search <text> - Search text",
        "replace <old_text> <new_text> - Replace text",
        "display - Display the editor",
        "exit - Exit the text editor"};

    char input[256];

    char *command = NULL;
    char *args[10];
    int argCount;

    printf("Text Editor\n");

    while (1)
    {
        for (int i = 0; i < 9; i++)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("Enter the Command : ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        process_full_command(input, &command, args, &argCount);

        switch (processCommand(command))
        {
        case C_ADD_LINE:
            if (argCount < 1)
            {
                printf("[ERROR] : No text provided.\n");
                break;
            }

            addLine(&editor, args[0]);
            break;

        case C_INSERT:
            if (argCount < 1)
            {
                printf("[ERROR] : No text provided.\n");
                break;
            }

            insertText(&editor, args[0]);
            break;

        case C_DELETE:
        {
            int n;
            char num_buf[32];

            printf("Enter the number of Characters you want to delete : ");

            if (fgets(num_buf, sizeof(num_buf), stdin) == NULL)
                break;

            if (sscanf(num_buf, "%d", &n) != 1)
            {
                printf("[ERROR] : Invalid input\n");
                break;
            }

            if (deleteCharacters(&editor, n) == FAILURE)
            {
                printf("[INFO] : Out of Bounds Deletion Request Detected\n");
                break;
            }

            printf("[SUCCESS] : Delete Done\n");
            break;
        }

        case C_UNDO:
            undoEdit(&editor);
            break;

        case C_REDO:
            redoEdit(&editor);
            break;

        case C_SEARCH:
        {
            if (argCount < 1)
            {
                printf("[ERROR] : Missing search text.\n");
                break;
            }

            char choice_buf[16];

            printf("To find all occurrences press [1]\n");
            printf("To find the next occurrence press [2]\n");
            printf("Choice : ");

            if (fgets(choice_buf, sizeof(choice_buf), stdin) == NULL)
                break;

            if (choice_buf[0] == '1')
            {
                findAll(&editor, args[0]);
            }
            else if (choice_buf[0] == '2')
            {
                int outPos, outLine;

                if (findText(&editor, args[0], &outPos, &outLine) == SUCCESS)
                {
                    printf("Found at Line : %d, Column : %d\n", outLine, outPos);
                }
                else
                {
                    printf("No Match Found\n");
                }
            }
            else
            {
                printf("Invalid choice.\n");
            }

            break;
        }

        case C_REPLACE:
        {
            if (argCount < 2)
            {
                printf("Usage: replace <old_text> <new_text>\n");
                break;
            }

            char choice;

            printf("Replace all occurrences? Press [1]\n");
            printf("Replace next occurrence? Press [2]\n");
            printf("Choice : ");

            scanf(" %c", &choice);
            getchar(); // consume newline

            if (choice == '1')
            {
                replaceAll(&editor, args[0], args[1]);
            }
            else if (choice == '2')
            {
                replaceText(&editor, args[0], args[1]);
            }
            else
            {
                printf("Invalid choice.\n");
            }

            break;
        }

        case C_PRINT:
            print_list(&editor);
            break;

        case C_EXIT:
            goto exit_loop;

        default:
            printf("Invalid Command\n");
            break;
        }
    }

exit_loop:
    freeEditor(&editor);
    freeStack(&editor.undoStack);
    freeStack(&editor.redoStack);

    return 0;
}