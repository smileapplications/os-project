#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"


void printHelp() {
    printf("-op | --output-preemption:      the path of the output file in which the results of the preemption's scheduler will be put\n"
                   "-on | --output-no-preemption:   the path of the output file in which the results of the no-preemption's scheduler will be put\n"
                   "-i  | --input:                  the path of the input file containing the task's list\n"
                   "-h  | --help:                   flags if the help has to be printed to the user");
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
settings getArgsSettings(int argc, char **argv) {

    settings argsSettings;

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
                abort();
            case 'o':
                if (strcmp(optarg, "p") == 0) {
                    argsSettings.preemptionPath = path;
                } else if (strcmp(optarg, "n") == 0) {
                    argsSettings.noPreemptionPath = path;
                } else {
                    fprintf(stderr, "Error: Parameter -o%c not recognised. Use --help to find out the correct usage",
                            optarg);
                }
                break;

            case 'i':
                argsSettings.inputPath = optarg;
                break;

            case -1:
                break;

            default:
                fprintf(stderr,
                        "Error: You have to specify the parameters. Use --help to find out the correct usage\n");
                abort();
        }
    } while (nextOption != -1);

    return argsSettings;
}