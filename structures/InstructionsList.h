//
// Created by Matteo Cardellini on 17/04/18.
//

#include "Instruction.h"

#ifndef OS_PROJECT_INSTRUCTIONSLIST_H
#define OS_PROJECT_INSTRUCTIONSLIST_H

typedef struct {
    Instruction *head;
    Instruction *lastItem;
    int nOfElements;
} InstructionList;

#endif //OS_PROJECT_INSTRUCTIONSLIST_H
