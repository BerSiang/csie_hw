#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word
{
		char key[110];
		int count;
		struct word *next;
};

struct word *add(struct word*, char*);
struct word *cut(struct word*, char*);
struct word *sort(struct word*, int);
void print(struct word*);
int cmp(const void *, const void *);


int main(int argc, char *argv[])
{
		FILE *f;
		int len=0;
		char buff[110];
		char *p;
		struct word *first=NULL;

		if(argc!=2)
		{
				printf("Option invalid\n");
				return 0;
		}

		if((f=fopen(argv[1],"r")))
		{
				while(fgets(buff,110,f)!=NULL)
				{
						//delete '\n'
						p=&buff[0];
						while(*p!='\0')
						{
								if(*p=='\n')
								{
										*p='\0';
										break;
								}
								p++;
						}

						if(buff[0]=='-')
						{
								p=&buff[1];
								first=cut(first, p);
						}
						else
						{
								p=&buff[0];
								first=add(first, p);
						}

						len++;
				}

				//empty file
				if(len==0)
				{
						printf("Terms not exists!\n");
				}
				else
				{
						first=sort(first,len);
						print(first);
				}
		}
		else
		{
				printf("Open file error!\n");
		}

		return 0;
}

struct word *add(struct word *first, char *str)
{
		struct word *current;
		struct word *find=NULL;
		current=first;

		while(current!=NULL)
		{
				if(strcmp(current->key,str)==0)
				{
						find=current;
						break;
				}
				current=current->next;
		}

		//existed
		if(find!=NULL)
		{
				(find->count)++;
				return first;
		}
		//new word
		else
		{
				struct word *new=malloc(sizeof(struct word));
				strcpy(new->key,str);
				new->count=1;

				//len>0
				if(first!=NULL)
				{
						new->next=first;
				}

				return new;
		}
}


struct word *cut(struct word *first, char *str)
{
		struct word *find=NULL;
		struct word *previous=NULL;
		struct word *current;
		current=first;

		while(current!=NULL)
		{
				if(strcmp(current->key, str)==0)
				{
						find=current;
						break;
				}

				previous=current;
				current=current->next;
		}

		//existed
		if(find!=NULL)
		{
				//delete
				if((find->count)==1)
				{
						//delete the first node
						if(find==first)
						{
								first=first->next;
						}
						else
						{
								previous->next=find->next;
						}
						free(find);
				}
				else
				{
						(find->count)--;
				}
		}

		return first;
}

void print(struct word *first)
{
		struct word *current;
		current=first;

		while(current!=NULL)
		{
				printf("%s:\t%d\n", current->key, current->count);
				current=current->next;
		}
}

struct word *sort(struct word *first, int len)
{
		//len is number of file lines
		struct word **data=malloc(len*sizeof(struct word*));
		struct word *current;
		int i=0,num=0;
		current=first;

		//save struct pointer to a pointer array
		while(current!=NULL)
		{
				data[i]=current;
				current=current->next;
				i++;
		}
		num=i;

		qsort(data,num,sizeof(struct word*),cmp);

		//reset link list
		first=data[0];
		for(i=0;i<num;i++)
		{
				data[i]->next=data[i+1];
		}

		return first;
}

int cmp(const void *a, const void *b)
{
		struct word *f=*(struct word * const *)a;
		struct word *l=*(struct word * const *)b;
		printf("<test>\n%s: %d\n%s: %d\n", f->key, f->count, l->key, l->count);

		if((f->count)>(l->count))
		{
				return -1;
		}
		else if((f->count)<(l->count))
		{
				return 1;
		}
		else
		{
				if(strcmp((f->key),(l->key))>0)
				{
						return 1;
				}
				else
				{
						return -1;
				}
		}
}

