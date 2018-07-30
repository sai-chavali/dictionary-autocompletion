#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*void swap(int a[], int src, int dest){
	int tmp = a[src];
	a[src] = a[dest];
	a[dest] = tmp;
}
void maxKswaps(int *a, int low, int n, int k,long int *max){
	int i;
	if (k == 0){
		int num = 0;
		for (i = 0; i<n; i++)
			num=num*10+a[i];
		printf("%d", num);
		if (num > *max)
			*max = num;
		return;
	}
	if (low == n)return;
	for (i = low; i<n; i++)
		if (i!=low){
			swap(a, i, low);
			maxKswaps(a, low, n, k - 1,max);
			swap(a, low, i);
		}
		else
			maxKswaps(a, low+1, n, k,max);
}
int main(){
	long int n, k, i = 0,max,j,x;
	scanf("%d%d", &n, &k); max = n; int *a = (int *)malloc(18 * sizeof(int));
	while (n){
		a[i++] = n % 10;
		n /= 10;
	}
	for (x = 0, j = i-1; x < j; x++, j--)
		swap(a, x, j);
	a = (int *)realloc(a, i*sizeof(int));
	maxKswaps(a, 0, i, k,&max);
	printf("%d", max);
}*/
#include<string.h>
typedef struct trie{
	char *meaning;
	struct trie *children[52];//A-z,a-z
}node;
node *head = NULL;
int ctoi(char x){
	if (x>'A' && x<'Z')
		return x - 'A';
	else
		return x - 'a' + 26;
}
node * getnode(){
	node *x = (node *)malloc(sizeof(node));
	int i;
	x->meaning = NULL;
	for (i = 0; i<52; i++)
		x->children[i] = NULL;
	return x;
}
void insert(node **x, char *word, char *meaning){
	int i = 0;
	node *cur = *x;
	for (i = 0; i<strlen(word); i++){
		char c = ctoi(word[i]);
		if (!cur->children[c])
			cur->children[c] = getnode();
		cur = cur->children[c];
	}
	cur->meaning = (char *)malloc(strlen(meaning));//unable to read is the exception I am getting 
	strcpy(cur->meaning, meaning);
}
char * get_meaning(node *head, char *word){
	int i = 0;
	for (i = 0; i<strlen(word); i++){
		char c = ctoi(word[i]);
		head = head->children[c];
		if (!head)
			return NULL;
	}
	return head->meaning;
}
node * read_dict(char *filename){
	FILE *file = fopen(filename, "r");
	int c = 0;
	if (file==NULL){
		printf("Cannot open file");
		return NULL;
	}
	char word[30];
	char desc[500];//quite bad practice
	head = getnode();
	while (fscanf(file,"%s %[^\n]", word, desc)>1){
		insert(&head, word, desc);
		c++;
	}
	fclose(file);
	printf("number of words inserted :%d\n", c);
	return head;
}
void autocomplete(node *head, char *query){
	char *tmp=(char *)malloc(52+strlen(query));
	char tag[2] = { 0 };
	if (head == NULL)
		return;
	if (head->meaning)
		printf("%s\n", query);
	for (int i = 0; i < 52; i++){
		strcpy(tmp, query);
		tag[0] = ('A' + i > 'Z') ? 'a' - 26 + i : 'A' + i;
		tag[1] = '\0';
		strcat(tmp, tag);
		autocomplete(head->children[i], tmp);
	}
}
int main(){
	head = read_dict("../../../../../../../PythonCourse/practice/inputs.txt");
	char s[52];
	printf("Word you want to search:");
	scanf("%s", s);
	printf("%s\n", get_meaning(head, s));
	node *tmp = head;
	printf("Type something u want to autocomplete: ");
	scanf("%s", s);
	for (int i = 0; s[i]; i++){
		char c = ctoi(s[i]);
		tmp = tmp->children[c];
		if (!tmp)
			return 0;
	}
	autocomplete(tmp, s);
}
