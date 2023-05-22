/*
이 알고리즘은 single source -> single destination 에 사용되는 최적화 알고리즘이다. A*가 optimal 조건을 만족하지 않는 다는 것을 감안한다면 이보다 나은 대안은 없다.

이 알고리즘은 다익스트라와 유사하지만, destination에 도달하면 탐색을 종료한다.
Vist을 체크 하는 위치와 final을 체크하는 위치가 매우 중요하다
Final 이전 노드 중 최소 dist를 가지는 minPreFinal에 대해 minPrevFinal + edge 을 pq에 넣었다고 가정하자.
그렇다면 minPrevFinal + edge가 답임을 보장할 수 있을까? prevFinal + edge' 중 더 작은 값이 있을 수 있을 것이다.

이러한 이유로 visit과 final 체크를 pq를 꺼내는 위치에서 한다. 이렇게 할 경우 마지막에 모든 prevFinal + edge가 pq에 들어가 있는 상태에서 가장 최소값을 pq에서 꺼냄으로써 답을 찾게 된다.
[출처] Direct Graph Traverse|작성자 voyager759
*/

#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define MAP_SIZE 20000
#define EDGE_SIZE 100000
#define QUEUE_SIZE 32768
#define ERR 1234567890

#define PARENT(A) ((A)>>1)
#define LEFT_CHILD(A) (((A)<<1))
#define RIGHT_CHILD(A) (((A)<<1) + 1)

typedef char cell_t;
typedef int ldist_t;
typedef int BOOL;
typedef signed char CBOOL;

typedef unsigned short pos_t;
typedef unsigned short sdist_t;

typedef struct edge_t {
	pos_t to;
	sdist_t distance;
	struct edge_t* next;
} edge_t;

typedef struct {
	unsigned short size;
	CBOOL visited[MAP_SIZE];
	edge_t* edges[MAP_SIZE];
} map_t;

typedef struct {
	ldist_t distance;
	pos_t pos;
} queueitem_t;

typedef struct {
	int count;
	queueitem_t heap[QUEUE_SIZE];
} minheap_t;

typedef struct {
	int allocated;
	edge_t pool[EDGE_SIZE];
} edgepool_t;

int getMinimumDistance(map_t* map, minheap_t* minheap);
void pushHeap(minheap_t* const minheap, const queueitem_t queueitem);
queueitem_t popHeap(minheap_t* const minheap);

map_t map;
minheap_t minheap;
edgepool_t edgepool;

inline edge_t* allocEdge() {
	return &edgepool.pool[edgepool.allocated++];
}

int main() {
	setvbuf(stdin, (char*)&minheap, _IOFBF, sizeof(minheap));

	int edges;
	scanf("%hd %d", &map.size, &edges);
	for (int point = 0; point < map.size; ++point) {
		map.visited[point] = FALSE;
		map.edges[point] = NULL;
	}

	for (int edge = 0; edge < edges; ++edge) {
		int from;
		edge_t* currentEdge = allocEdge();
		scanf("%d %hd %hd", &from, &currentEdge->to, &currentEdge->distance);
		--from;
		--currentEdge->to;
		currentEdge->next = map.edges[from];
		map.edges[from] = currentEdge;
	}
	minheap.count = 0;

	int result = getMinimumDistance(&map, &minheap);
	printf("%d\n", result);
	return 0;
}

int getMinimumDistance(map_t* map, minheap_t* minheap) {
	queueitem_t current, neighborItem;
	register ldist_t currentDist;
	current.distance = 0;
	current.pos = 0;
	pushHeap(minheap, current);
	while (minheap->count) {
		current = popHeap(minheap);
		map->visited[current.pos] = TRUE;  // 이 위치가 아니면 잘못된 결과가 나옴
		if (current.pos == map->size - 1) // 이 위치가 아니면 잘못된 결과가 나옴
			return current.distance;
		currentDist = current.distance;
		for (register edge_t* edge = map->edges[current.pos];
			edge; edge = edge->next) {
			register int to = edge->to;
			if (!map->visited[to]) {
				neighborItem.distance = currentDist + edge->distance;
				neighborItem.pos = to;
				pushHeap(minheap, neighborItem);
			}
		}
	}
	return ERR;
}

inline void pushHeap(minheap_t* const minheap, const queueitem_t queueitem) {
	register int current = minheap->count + 1, parent = PARENT(current);
	queueitem_t swaptemp;
	minheap->heap[++minheap->count] = queueitem;
	while (current > 1) {
		if (minheap->heap[parent].distance > minheap->heap[current].distance) {
			swaptemp = minheap->heap[parent];
			minheap->heap[parent] = minheap->heap[current];
			minheap->heap[current] = swaptemp;
			current = parent;
			parent = PARENT(current);
		}
		else break;
	}
}

inline queueitem_t popHeap(minheap_t* const minheap) {
	queueitem_t result = minheap->heap[1], swaptemp;
	register int current, lc, rc, smaller;
	minheap->heap[1] = minheap->heap[minheap->count--];
	current = 1; lc = LEFT_CHILD(current); rc = lc + 1;
	while (lc <= minheap->count) {
		if (lc == minheap->count)
			smaller = lc;
		else
			smaller = minheap->heap[lc].distance < minheap->heap[rc].distance ? lc : rc;
		if (minheap->heap[smaller].distance < minheap->heap[current].distance) {
			swaptemp = minheap->heap[current];
			minheap->heap[current] = minheap->heap[smaller];
			minheap->heap[smaller] = swaptemp;
			current = smaller; lc = LEFT_CHILD(current); rc = lc + 1;
		}
		else break;
	}
	return result;
}
[출처] Direct Graph Traverse|작성자 voyager759
