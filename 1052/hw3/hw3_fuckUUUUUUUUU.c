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

int main() {
		student *head, *current;
		head = malloc(sizeof(student));
		char *buf = malloc(1024 * sizeof(char));
		printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
		while(fgets(buf, 1024, stdin) != 0) {
				if(buf[strlen(buf) - 1] == '\n')
						buf[strlen(buf) - 1] = '\0';
				char* arg[20];
				char *deli = ",";
				int i, j;
				arg[0] = strtok(buf, deli);
				for(i = 0; arg[i] != NULL; i++) {
						arg[i + 1] = strtok(NULL, deli);
				}

				for(j = 0; j < i; j++) {
						printf("arg[%d]: %s\n", j, arg[j]);
				}
				printf("cmd:%c\n", *arg[0]);
				/*switch(*arg[0]) {
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
								break;
						case 'w':
								dataWrite(head, arg[1]);
								break;
						case 'q':
								exit(EXIT_SUCCESS);
								break;
				}*/
				if(*arg[0] == 'i') {
						printf("arg[0]: %c, add(%p, %s, %s, %s, %s)\n", *arg[0], head, arg[1], arg[2], arg[3], arg[4]);
						head = add(head, arg[1], arg[2], arg[3], arg[4]);
				}
				else if(*arg[0] == 'd') {
						printf("arg[0]: %c, delete(%p, %s)\n", *arg[0], head, arg[1]);
						head = delete(head, arg[1]);							
				}
				else if(*arg[0] == 'l') {
						printf("arg[0]: %c, listAll(%p)\n", *arg[0], head);
						listAll(head);
				}
				else if(*arg[0] == 'p') {
						printStu(head);
				}

		}
		/*head = add(head, "400410026", "henry", "0912563563", "20");
		listAll(head);
		head = delete(head, "400410026");
		listAll(head);*/
		return 0;
}

student *add(student *source, char *id, char *name, char *phone, char *age) {
		if(source->id == NULL) {
				source->id = malloc(20 * sizeof(char));
				source->id = id;
				source->name = malloc(20 * sizeof(char));
				source->name = name;
				source->phone = malloc(20 * sizeof(char));
				source->phone = phone;
				source->age = malloc(20 * sizeof(char));
				source->age = age;
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
		student *newData = (student*)malloc(1 * sizeof(student));
		previous->next = newData;
		newData->id = id;
		newData->name = name;
		newData->phone = phone;
		newData->age = age;
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
										source == NULL;
								else
									source = source->next;
						}
						previous->next = current->next;
						current->id = current->name = current->phone = current->age = NULL;
						current->next = NULL;
						free(current);
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
		target = findID(source, newID);
		if(strcmp(oldID, newID) != 0 && target) {
				printf("Update error! studentID not exists!\n");
				return 0;
		}
		target->id = newID;
		target->name = name;
		target->phone = phone;
		target->age = age;
		printStu(target);
		return 0;
}
int printStu(student *source) {
		printf("%s,%s,%s,%s\n", source->id, source->name, source->phone, source->age);
}	
int listAll(student *source) {
		student *current;
		current = source;
		while(current != NULL) {
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
				if(strcmp(current->id, target) == 0) {
						printStu(current);
				}
				else if(strcmp(current->name, target) == 0) {
						printStu(current);
				}
				else if(strcmp(current->phone, target) == 0) {
						printStu(current);
				}
				else if(strcmp(current->age, target) == 0) {
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
				sprintf(tmp, "%s,%s,%s,%d\n", current->id, current->name, current->phone, current->age);
				strcat(output, tmp);
				current = current->next;
		}
		int fd = open(fileName, O_RDWR | O_CREAT, 0644);
		write(fd, output, strlen(output));
		return fd;
}

