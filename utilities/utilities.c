#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include <unistd.h>
#include <sysexits.h>
#include "../libs/csvparser.h"
#include "../structures/TaskList.h"


void printHelp() {
    printf("-op | --output-preemption:      the path of the output file in which the results of the preemption's scheduler will be put\n"
                   "-on | --output-no-preemption:   the path of the output file in which the results of the no-preemption's scheduler will be put\n"
                   "-i  | --input:                  the path of the input file containing the task's list\n"
                   "-h  | --help:                   flags if the help has to be printed to the user\n");
}

/**
 * This function takes care of analyzing the parameters passed to the program:
 *  -op | --output-preemption:      the path of the output file in which the results of the preemption's scheduler will be put
    -on | --output-no-preemption:   the path of the output file in which the results of the no-preemption's scheduler will be put
    -i  | --input:                  the path of the input file containing the task's list
    -h  | --help:                   flags if the help has to be printed to the user

 * @param {int}         argc    - The number of arguments
 * @param {char**}      argv    - An array of chars with the arguments
 * @return {settings}           - A stucture containing the passed settings
 */
programArgs_t getArgsSettings(int argc, char **argv) {

    programArgs_t argsSettings;
    argsSettings.preemptionPath = NULL;
    argsSettings.noPreemptionPath = NULL;
    argsSettings.inputPath = NULL;

    const char *const short_options = "ho:i:np";

    /* An array describing valid long options. */
    const struct option long_options[] = {
            {"help",                 0, NULL, 'h'},
            {"output",               2, NULL, 'o'},
            {"output-no-preemption", 1, NULL, 'n'},
            {"output-preemption",    1, NULL, 'p'},
            {"input",                1, NULL, 'i'},
            {NULL,                   0, NULL, 0}
    };

    int nextOption;
    do {
        nextOption = getopt_long(argc, argv, short_options, long_options, NULL);
        char *path = argv[optind];
        switch (nextOption) {
            case 'h':
                printHelp();
                exit(0);
            case 'o':
                if (strcmp(optarg, "p") == 0) {
                    argsSettings.preemptionPath = path;
                } else if (strcmp(optarg, "n") == 0) {
                    argsSettings.noPreemptionPath = path;
                } else {
                    fprintf(stderr, "Error: Parameter -o%s not recognised. Use --help to find out the correct usage",
                            optarg);
                    exit(EX_USAGE);
                }
                break;
            case 'n':
                argsSettings.noPreemptionPath = optarg;
                break;
            case 'p':
                argsSettings.preemptionPath = optarg;
                break;
            case 'i':
                argsSettings.inputPath = optarg;
                break;

            case -1:
                break;

            default:
                fprintf(stderr,
                        "Error: You have to specify the parameters. Use --help to find out the correct usage\n");
                exit(EX_USAGE);
        }
    } while (nextOption != -1);

    if (argsSettings.inputPath == NULL || argsSettings.noPreemptionPath == NULL ||
        argsSettings.preemptionPath == NULL) {
        printf("ERROR: Improper use. Here's the guide:\n");
        printHelp();
        exit(EX_USAGE);
    }

    return argsSettings;
}


/**
 * getTaskListFromCSV - This function takes the path of the input csv files and returns the TaskList
 * data structure that contains all the task and instructions contained
 * @param {char*} inputFilePath  - The path of the csv to parse
 * @return {TaskList*}           - The TaskList data structure that contains all the task and instructions contained
 */
TaskList *getTaskListFromCSV(char *inputFilePath) {

    TaskList *taskList = createTaskList();

    TaskControlBlock *currentTask = NULL;

    if (access(inputFilePath, R_OK) == -1) {
        perror(inputFilePath);
        exit(EX_IOERR);
    }

    CsvParser *csvParser = CsvParser_new(inputFilePath, ",", 0);
    CsvRow *row;

    do {
        row = CsvParser_getRow(csvParser);
        if (row == NULL) {
            break;
        }

        char **rowFields = CsvParser_getFields(row);

        char *type = rowFields[0];
        if (strcmp(type, "t") == 0) {
            int taskId = atoi(rowFields[1]);
            int arrivalTime = atoi(rowFields[2]);
            currentTask = createTaskControlBlock(taskId, arrivalTime);
            addTaskToList(taskList, currentTask);
        } else if (strcmp(type, "i") == 0) {
            if (currentTask == NULL) {
                fprintf(stderr, "CSV FORMAT ERROR: The file starts with instructions without a parent task");
                exit(EX_DATAERR);
            }
            enum blockingFlag type_flag = (enum blockingFlag) atoi(rowFields[1]);
            int length = atoi(rowFields[2]);

            if (type_flag == nonBlocking) {
                currentTask->process_time += length;
            }

            addInstructionToList(currentTask->instructionList, type_flag, length);
        }
        CsvParser_destroy_row(row);
    } while (row);

    CsvParser_destroy(csvParser);

    if (taskList->head == NULL) {
        fprintf(stderr, "ERROR: Impossible to create tasklist\n");
        exit(EX_DATAERR);
    }

    return taskList;
}