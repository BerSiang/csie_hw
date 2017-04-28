#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SWAP(X, Y, T) T=X,X=Y,Y=T

typedef struct student {
		char id[30];
		char name[30];
		char phone[30];
		char age[30];
}student;

//student *createNode(char*, char*, char*, char*);
//void insertNode(student*, student*);
student *add(student*, char[], char*, char*, char*);
//student *delete(student*, char*);
//int update(student*, char*, char*, char*, char*, char*);
//student *findID(student*, char*);
//int *find(student*, char*);
int printStu(student source); 
int listAll(student*);
int main() {
		student head[3000];
		char *buf = malloc(1024 * sizeof(char));
		char *p;
		char com[100];
		int i;
		printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
		while(fgets(com, 100, stdin) != 0) {
				if(com[strlen(buf) - 1] == '\n')
						com[strlen(buf) - 1] = '\0';
				/*char *arg[20];
				  arg[0] = malloc(50 * sizeof(char));
				  arg[1] = malloc(50 * sizeof(char));
				  arg[2] = malloc(50 * sizeof(char));
				  arg[3] = malloc(50 * sizeof(char));
				  arg[4] = malloc(50 * sizeof(char));
				  arg[5] = malloc(50 * sizeof(char));
				  char *deli = ",";
				  char **pSave;
				  int i, j;
				  strcpy(arg[0], strtok_r(buf, deli, pSave));
				  for(i = 0; arg[i] != NULL; i++) {
				  strcpy(arg[i + 1], strtok_r(NULL, deli, pSave));
				  }

				  for(j = 0; j < i; j++) {
				  printf("arg[%d]: %s\n", j, arg[j]);
				  }*/
				char **arg=malloc(6*sizeof(char*));

				//delete '\n' at the end of the string
				com[strlen(com)-1]='\0';

				//split command into pieces
				p=com;
				arg[0]=p;
				i=1;
				while((p=strchr(p,','))!=NULL)
				{
						*p='\0';
						p++;
						arg[i]=p;
						i++;
				}
				printf("cmd:%c\n", *arg[0]);
				switch(**arg) {
						case 'i':
								add(head, arg[1], arg[2], arg[3], arg[4]);
								break;
						case 'd':
								//head = delete(head, arg[1]);
								break;
						case 'u':
								//update(head, arg[1], arg[2], arg[3], arg[4], arg[5]);
								break;
						case 'f':
								//find(head, arg[1]);
								break;
						case 'l':
								listAll(head);
								break;
						case 's':
								//head = sort(head, arg[1]);
								break;
						case 'w':
								//dataWrite(head, arg[1]);
								break;
						case 'q':
								exit(EXIT_SUCCESS);
								break;
						default:
								break;
				}
				/*if(*arg[0] == 'i') {
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
				  }*/

				/*head = add(head, "400410026", "henry", "0912563563", "20");
				  listAll(head);*/
				//head = delete(head, "400410026");
				//listAll(head);

		}
		/*head = add(head, "400410026", "henry", "0912563563", "20");
		  listAll(head);
		  head = delete(head, "400410026");
		  listAll(head);*/
		return 0;
}
/*student *createNode(char *id, char *name, char *phone, char *age) {
		student *n = (student*)malloc(sizeof(student));

		n->id = id;
		n->name = name;
		n->phone = phone;
		n->age = age;
		n->next = NULL;

		return n;
}
void insertNode(student *n1, student *n2) {
		n2->next = n1->next;
		n1->next = n2;
}*/
student *add(student *source, char id[], char *name, char *phone, char *age) {
		int i;
		for(i = 0; i < 3000; i++) {
				if(strcmp(source[i].id, id) == 0) {
						printf("Insert error! studentID is exists!\n");
						return source;
				}
				if(source[i].id[0] == '\0') {
						strcpy(source[i].id, id);
						strcpy(source[i].name, name);
						strcpy(source[i].phone, phone);
						strcpy(source[i].age, age);
						printStu(source[i]);
						return source;
				}
		}
		return source;
}
int printStu(student source) {
		printf("%s,%s,%s,%s\n", source.id, source.name, source.phone, source.age);
		return 0;
}
int listAll(student *source) {
		int i = 0;
		while(source[i].id[0] != '\0') {
				printf("%s,%s,%s,%s\n", source[i].id, source[i].name, source[i].phone, source[i].age);
				i++;
		}
		return 0;
}
