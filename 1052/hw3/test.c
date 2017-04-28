#include <stdio.h>
#include <stdlib.h>

// �ŧi�`�I���c
typedef struct ns
{
		int data;
		struct ns* next;
} node;

// �ŧi�����禡
node* create_node(int);
void insert_node(node*, node*);
void remove_node(node*);
void print_lists(node*);
void free_lists(node*);

int main(void)
{
		node head = NULL
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
				switch(*arg[0]) {
				  case 'i':
				  create_node(0);
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
				  }

		}
		// �ŧi�`�I
		node* lists = create_node(0);
		node* a = create_node(1);
		node* b = create_node(2);
		node* c = create_node(3);
		node* d = create_node(4);
		node* e = create_node(5);

		// 0 -> 5
		insert_node(lists, e);

		// 0 -> 1 -> 5
		insert_node(lists, a);

		// 1 -> 2 -> 5
		insert_node(a, b);

		// 1 -> 3 -> 2
		insert_node(a, c);

		// 5 -> 4
		insert_node(e, d);

		print_lists(lists);
		free_lists(lists);

		system("pause");
}

node* create_node(int data)
{
		// �ʺA�t�m�O����
		node* n = (node*)malloc(sizeof(node));

		n->data = data;
		n->next = NULL;

		return n;
}

void insert_node(node* n1, node* n2)
{
		n2->next = n1->next;
		n1->next = n2;
}

void remove_node(node* n1)
{
		n1->next = n1->next->next;
}

void print_lists(node* lists)
{
		node* n = lists;

		// �̧ǦL�X�`�I���e
		while (n != NULL)
		{
				printf("%d ", n->data);

				n = n->next;
		}

		printf("\n");
}

void free_lists(node* lists)
{
		// ���j�R����C�Ҧ��`�I
		if (lists->next != NULL)
		{
				free_lists(lists->next);
		}

		free(lists);
}
