#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Command.h"

void initializeCommandList(CommandList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}

/* General purpose */
void insertCommand(CommandList *list, char *line) {
	Command *command = malloc(sizeof(Command));

	if(line[strlen(line)-1] == '\n') {
		line[strlen(line)-1] = '\0';
	}
	
	strcpy(command->line, line);

	if(list->count < CAPACITY) {
		if(list->count == 0) {
			list->head = command;
			list->tail = command;
			list->head->prev = NULL;
			list->head->next = NULL;
		} else {
			command->prev = NULL;
			command->next = list->head;
			list->head->prev = command;
			list->head = command;
		}
		(list->count)++;
	} else {
		Command *temp = NULL;

		command->prev = NULL;
		command->next = list->head;
		list->head->prev = command;
		list->head = command;
		
		temp = list->tail;
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		free(temp);
	}
}

/* File importing purpose only (Insert at tail) */
void constructCommand(CommandList *list, char *line) {
	Command *command = malloc(sizeof(Command));

	strcpy(command->line, line);

	if(list->count == 0) {
		list->head = command;
		list->tail = command;
		list->head->prev = NULL;
		list->head->next = NULL;
	} else {
		command->prev = list->tail;
		command->next = NULL;
		list->tail->next = command;
		list->tail = command;
	}

	(list->count)++;
}

void freeCommandList(CommandList *list) {
	Command *cur = list->head;
	Command *next = NULL;
	int i = 0;
	
	while(i < list->count) {
		next = cur->next;
		free(cur);
		cur = next;
		i++;
	}
}

void initializeWorkList(WorkList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}

void insertWork(WorkList *list, char *args, Mode mode) {
	Work *work = malloc(sizeof(Work));

	strcpy(work->args, args);
	work->mode = mode;

	if(list->count == 0) {
		work->prev = NULL;
		work->next = NULL;
		list->head = work;
		list->tail = work;
	} else {
		work->prev = list->tail;
		work->next = NULL;
		list->tail->next = work;
		list->tail = work;
	}

	(list->count)++;
}

void freeWorkList(WorkList *list) {
	Work *cur = list->head;
	Work *next = NULL;
	int i = 0;

	while(i < list->count) {
		next = cur->next;
		free(cur);
		cur = next;
		i++;
	}
}