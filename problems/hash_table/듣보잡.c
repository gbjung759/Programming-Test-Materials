// https://www.acmicpc.net/problem/1764

#define _CRT_SECURE_NO_WARNINGS
#define HASH_KEY 1000007
#define STR_SIZE 22
#include<stdio.h>
#include<malloc.h>

typedef unsigned int UINT;
typedef struct _node
{
	char str[STR_SIZE];
	struct _node* next;
} node;

node htable[HASH_KEY];

int N, M;
node* sol[500000]; int sn;

int fstrcmp(char* a, char* b)
{
	int i = 0;

	while (a[i] != 0)
	{
		if (a[i] != b[i]) break;
		i++;
	}

	return a[i] - b[i];
}


int comp(node* a, node* b)
{
	return fstrcmp(a->str, b->str);
}

int get_hash(node* a)
{
	int i;
	UINT hash, offset;
	char* str;

	str = a->str;
	hash = 0;	
	offset = 1;

	for (i = 0; str[i] != 0; i++)
	{
		hash += ((str[i] - 'a' + 1) * offset);
		offset *= 25;
	}
	return hash % HASH_KEY;
}

int add_table(node* head, node* p)
{
	while (head->next != NULL)
	{
		if (!comp(head->next, p))
			return 0;
		head = head->next;
	}
	head->next = p;
	return 1;
}

node* search_table(node* head, node* p)
{
	while (head->next != NULL)
	{
		if (!comp(head->next, p))
		{
			return head->next;
		}
		head = head->next;
	}
	return NULL;
}

node* create_node()
{
	node* p = (node*)malloc(sizeof(node));
	p->next = NULL;
	return p;
}

void b_search(node** arr, int s, int e)
{
	node* temp;
	int l, t, p;

	p = e;
	t = s;

	if (s >= e) return;

	for (l = s; l < e; l++)
	{
		if (comp(arr[l], arr[p]) < 0)
		{
			if (t != l)
			{
				temp = arr[l];
				arr[l] = arr[t];
				arr[t] = temp;
			}
			t++;
		}
	}
	if (t < p)
	{
		temp = arr[t];
		arr[t] = arr[p];
		arr[p] = temp;
	}
	b_search(arr, s, t - 1);
	b_search(arr, t + 1, e);
}


void solve()
{
	node* p, *q;
	int i, hash;

	scanf("%d %d", &N, &M);

	for (i = 0; i < N; i++)
	{
		p = create_node();
		scanf("%s", p->str);
		hash = get_hash(p);

		if (!add_table(&htable[hash], p))
		{
			free(p);
		}
	}

	for (i = 0; i < M; i++)
	{
		p = create_node();
		scanf("%s", p->str);
		hash = get_hash(p);

		q = search_table(&htable[hash], p);
		
		if (q != NULL)
		{
			sol[sn++] = q;
		}

		free(p);
	}

	b_search(sol, 0, sn - 1);
}

void destroy()
{
	int i;
	node* p, *del;
	for (i = 0; i < HASH_KEY; i++)
	{
		p = &htable[i];
		while (p->next != NULL)
		{
			del = p->next;
			p->next = p->next->next;
			if (del != NULL) free(del);
		}
	}
}

int main(void)
{
	int i;
	node* pre, *cur;
	//freopen("a.txt", "r", stdin);

	solve();
	printf("%d\n", sn);

	if (sn > 0)
	{
		printf("%s\n", sol[0]->str);
		pre = sol[0];
		for (i = 1; i < sn; i++)
		{
			cur = sol[i];
			if (comp(pre, cur) != 0)
				printf("%s\n", cur->str);
			pre = cur;
		}
	}

	destroy();
	return 0;
}
[출처] [해시테이블]듣보잡|작성자 voyager759

