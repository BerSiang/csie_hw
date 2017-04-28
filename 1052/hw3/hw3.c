#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SWAP(X, Y, T) T=X,X=Y,Y=T

typedef struct student {
		char *id;
		char *name;
		char *phone;
		char *age;
		struct student *next;
}student;

student *add(student*, char*, char*, char*, char*);
student *delete(student*, char*);
int update(student*, char*, char*, char*, char*, char*);
student *findID(student*, char*);
int *find(student*, char*);
int printStu(student *source); 
int listAll(student*);
student *sort(student*, char*);
int dataWrite(student*, char*);
int freeStu(student*);

int main() {
		student *head;
		head = malloc(sizeof(student));
		char *buf = malloc(1024 * sizeof(char));
		printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
		while(fgets(buf, 1024, stdin) != 0) {
				if(buf[strlen(buf) - 1] == '\n')
						buf[strlen(buf) - 1] = '\0';
				char* arg[20];
				char *deli = ",";
				int i;
				arg[0] = strtok(buf, deli);
				for(i = 0; arg[i] != NULL; i++) {
						arg[i + 1] = strtok(NULL, deli);
				}

				switch(*arg[0]) {
						case 'i':
								head = add(head, arg[1], arg[2], arg[3], arg[4]);
								break;
						case 'd':
								head = delete(head, arg[1]);
								break;
						case 'u':
								update(head, arg[1], arg[2], arg[3], arg[4], arg[5]);
								break;
						case 'f':
								find(head, arg[1]);
								break;
						case 'l':
								listAll(head);
								break;
						case 's':
								head = sort(head, arg[1]);
								listAll(head);
								break;
						case 'w':
								dataWrite(head, arg[1]);
								break;
						case 'q':
								exit(EXIT_SUCCESS);
								break;
				}
		}
		return 0;
}

student *add(student *source, char *id, char *name, char *phone, char *age) {
		if(source->id == NULL) {
				source->id = malloc(50 * sizeof(char));
				strcpy(source->id, id);
				source->name = malloc(50 * sizeof(char));
				strcpy(source->name, name);
				source->phone = malloc(50 * sizeof(char));
				strcpy(source->phone, phone);
				source->age = malloc(50 * sizeof(char));
				strcpy(source->age, age);
				source->next = NULL;
				printStu(source);
				return source;
		}
		student *current, *previous;
		current = source;
		while(current != NULL) {
				if(strcmp(current->id, id) == 0) {
						printf("Insert error! studentID is exists!\n");
						return source;
				}
				previous = current;
				current = current->next;
		}
		student *newData = malloc(sizeof(student));
		previous->next = newData;
		newData->id = malloc(50 * sizeof(char));
		strcpy(newData->id, id);
		newData->name = malloc(50 * sizeof(char));
		strcpy(newData->name, name);
		newData->phone = malloc(50 * sizeof(char));
		strcpy(newData->phone, phone);
		newData->age = malloc(50 * sizeof(char));
		strcpy(newData->age, age);
		newData->next = NULL;
		printStu(newData);
		return source;
}
student *delete(student *source, char *id) {
		student *current, *previous;
		current = source;
		if(source->id == NULL) {
				printf("Delete error! studentID not exists!\n");
				return source;
		}
		while(current != NULL) {
				if(strcmp(current->id, id) == 0) {
						printStu(current);
						if(current == source) {
								if(source->next == NULL)
										source = NULL;
								else
									source = source->next;
						}
						previous->next = current->next;
						freeStu(current);
						return source;
				}
				previous = current;
				current = current->next;
		}
		printf("Delete error! studentID not exists!\n");
		return source;
}
int update(student *source, char *oldID, char *newID, char* name, char* phone, char *age) {
		student *target;
		target = findID(source, oldID);
		if((strcmp(oldID, newID) != 0 && findID(source, newID)) || target == NULL) {
				printf("Update error! studentID not exists!\n");
				return 0;
		}
		strcpy(target->id, newID);
		strcpy(target->name, name);
		strcpy(target->phone, phone);
		strcpy(target->age, age);
		printStu(target);
		return 0;
}
int printStu(student *source) {
		printf("%s,%s,%s,%s\n", source->id, source->name, source->phone, source->age);
		return 0;
}	
int listAll(student *source) {
		student *current;
		current = source;
		while(current != NULL && current->id != NULL) {
				printf("%s,%s,%s,%s\n", current->id, current->name, current->phone, current->age);
				current = current->next;
		}
		return 0;
}
student *findID(student* source, char* id) {
		student *current;
		current = source;
		while(current != NULL) {
				if(strcmp(current->id, id) == 0) {
						return current;
				}
				current = current->next;
		}
		return 0;
}
int *find(student *source, char *target) {
		student *current;
		current = source;
		while(current != NULL) {
				if(strstr(current->id, target) != NULL) {
						printStu(current);
				}
				else if(strcasestr(current->name, target) != NULL) {
						printStu(current);
				}
				else if(strcasestr(current->phone, target) != NULL) {
						printStu(current);
				}
				else if(strcasestr(current->age, target) != NULL) {
						printStu(current);
				}
				current = current->next;
		}
		return 0;
}
student *sort(student *source, char *column) {
		student *current, *previous;
		current = source;
		int change = 1;
		while(change) {
				change = 0;
				current = source;
				previous = NULL;
				while(current != NULL) {
						if(current->next == NULL) break;
						char *compTarget = 0, *compNextTarget = 0;
						if(strcasecmp(column, "studentID") == 0) {
								compTarget = current->id;
								compNextTarget = current->next->id;
						}
						else if(strcasecmp(column, "name") == 0) {
								compTarget = current->name;
								compNextTarget = current->next->name;
						}
						else if(strcasecmp(column, "phone") == 0) {
								compTarget = current->phone;
								compNextTarget = current->next->phone;
						}
						else if(strcasecmp(column, "age") == 0) {
								compTarget = current->age;
								compNextTarget = current->next->age;
						}
						if(strcmp(compTarget, compNextTarget) > 0) {
								student *t = current->next->next;
								if(current == source) {
										source = current->next;
								}
								else {
										previous->next = current->next;
								}
								current->next->next = current;
								current->next = t;
								change = 1;
						}
						previous = current;
						current = current->next;
				}
		}
		return source;
}
int dataWrite(student *source, char *fileName) {
		char* output = malloc(1000000 * sizeof(char));
		char* tmp = malloc(1000000 * sizeof(char));
		student *current = source;
		while(current != NULL) {
				sprintf(tmp, "%s,%s,%s,%s\n", current->id, current->name, current->phone, current->age);
				strcat(output, tmp);
				current = current->next;
		}
		int fd = open(fileName, O_RDWR | O_CREAT, 644);
		if(write(fd, output, strlen(output)) == -1) {
				printf("Write error!\n");
		}
		else {
				printf("Writing file successful!\n");
		}
		return fd;
}
int freeStu(student *source) {
		free(source->id);
		source->id = NULL;
		free(source->name);
		source->name = NULL;
		free(source->phone);
		source->phone = NULL;
		free(source->age);
		source->age = NULL;
		return 0;
}
