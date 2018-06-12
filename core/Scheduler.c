//
// Created by Matteo Cardellini on 10/06/18.
//

#include "../structures/TaskList.h"
#include "../structures/StateList.h"
#include "../structures/TaskControlBlock.h"
#include "../structures/Instruction.h"
#include <stddef.h>
#include <printf.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int pc = 0;


//SPN: Shortest Process Time
TaskControlBlock *selectionFunctionSPN(StateList *readyList) {
    StateListElement *currentElement = readyList->front;
    StateListElement *selectedElement = NULL;
    if (currentElement == NULL) {
        return NULL;
    }
    int minProcessTime = currentElement->task->process_time;
    while (currentElement != NULL) {
        int currentTaskProcessTime = currentElement->task->process_time;
        if (currentTaskProcessTime <= minProcessTime) {
            minProcessTime = currentTaskProcessTime;
            selectedElement = currentElement;
        }
        currentElement = (StateListElement *) currentElement->previous;
    }
    removeFromList(readyList, selectedElement);
    return selectedElement->task;
}

int i = 0;

//SRT: Shortest Remaining Time
TaskControlBlock *selectionFunctionSRT(StateList *readyList) {
    i++;
    StateListElement *currentElement = readyList->front;
    StateListElement *selectedElement = NULL;
    if (currentElement == NULL) {
        return NULL;
    }
    int minRemainingTime = currentElement->task->process_time - currentElement->task->execution_time;
    while (currentElement != NULL) {
        int currentTaskRemainingTime = currentElement->task->process_time - currentElement->task->execution_time;
        if (currentTaskRemainingTime <= minRemainingTime) {
            minRemainingTime = currentTaskRemainingTime;
            selectedElement = currentElement;
        }
        currentElement = (StateListElement *) currentElement->previous;
    }
    removeFromList(readyList, selectedElement);
    return selectedElement->task;
}

void tickAllBlockedTasks(StateList *blockedList, StateList *readyList) {

    StateListElement *currentElement = blockedList->front;

    while (currentElement != NULL) {
        TaskControlBlock *currentTask = currentElement->task;
        printf("\tTask #%d: Ha bisogno ancora di %d clock\n", currentTask->id, currentTask->pc->length);

        if (currentTask->pc->length == 1) {
            StateListElement *endedElement = currentElement;
            currentElement = (StateListElement *) endedElement->previous;
            removeFromList(blockedList, endedElement);
            pushToStateList(readyList, endedElement->task);
            printf("\tTask #%d: Terminato I/O\n", endedElement->task->id);
        } else {
            currentTask->pc->length--;
            currentElement = (StateListElement *) currentElement->previous;
        }
    }


}

int getRandomLenght(int maxLenght) {
    srand((unsigned int) time(NULL));
    return maxLenght;
    return rand() % maxLenght + 1; //TODO: Ricordati di rimuoverlo
}

void Scheduler(TaskList *taskList, bool isPreemptive) {

    TaskControlBlock *nextTaskToArrive = taskList->head;
    TaskControlBlock *runningTask = NULL;
    Instruction *currentInstruction = NULL;

    StateList *readyList = createStateList();
    StateList *blockedList = createStateList();

    while (pc < 100) { //TODO: SAFE. Remember to remove it

        //TODO: Guardare il caso in cui due task arrivano assieme

        printf("PC #%d\n", pc);

        while (nextTaskToArrive != NULL && nextTaskToArrive->arrival_time == pc) {
            changeTaskState(nextTaskToArrive, state_ready);
            pushToStateList(readyList, nextTaskToArrive);
            nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
            if (isPreemptive && runningTask != NULL) {
                //Se siamo in modalità preemptive, secondo l'algoritmo SRT, devo rischedulare ad ogni arrivo
                pushToStateList(readyList, runningTask);
                changeTaskState(runningTask, state_ready);
                runningTask = NULL;
            }
        }

        if (readyList->nOfElements == 0 && blockedList->nOfElements == 0 && nextTaskToArrive == NULL &&
            runningTask == NULL) {
            break;
        }


        if (runningTask == NULL) {
            runningTask = isPreemptive ? selectionFunctionSRT(readyList) : selectionFunctionSPN(readyList);

            if (runningTask == NULL) {
                goto TICK;
            }

            if (runningTask->pc == NULL) {
                currentInstruction = runningTask->instructionList->head;
            } else {
                if (runningTask->pc->length == 0) {
                    if (runningTask->pc->next == NULL) {
                        changeTaskState(runningTask, state_exit);
                        runningTask = NULL;
                        goto TICK;
                    } else {
                        currentInstruction = (Instruction *) runningTask->pc->next;
                    }
                } else {
                    currentInstruction = runningTask->pc;
                }
            }
        }

        runningTask->pc = currentInstruction;

        if (runningTask->state != state_running) {
            changeTaskState(runningTask, state_running);
        }

        if (currentInstruction->type_flag == nonBlocking) {
            currentInstruction->length--;
            runningTask->execution_time++;

            if (currentInstruction->length > 0) {
                printf("\tTask #%d: Eseguo calcolo\n", runningTask->id);
                goto TICK;
            }

            if (currentInstruction->next != NULL) {
                printf("\tTask #%d: Nuova istruzione\n", runningTask->id);
                currentInstruction = (Instruction *) currentInstruction->next;
            } else {
                printf("\tTask #%d: Terminato\n", runningTask->id);
                currentInstruction = NULL;
                runningTask = NULL;
            }
            goto TICK;
        }

        if (currentInstruction->type_flag == blocking) {
            currentInstruction->length = getRandomLenght(currentInstruction->length);
            changeTaskState(runningTask, state_blocked);
            pushToStateList(blockedList, runningTask);
            runningTask = NULL;
            currentInstruction = NULL;
        }

        TICK:
        tickAllBlockedTasks(blockedList, readyList);


        pc++; //TODO: Magari mettilo in fondo ?
    }

    printf("END\n");
}
