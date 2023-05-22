<특징>
- 정렬 데이터(key) 크기의 제약이 있는 경우 사용 가능
- 가장 높은 성능을 자랑한다(key 중복이 없을 경우 삽입, 삭제, 참조 O(1)). 
 단 테이블의 상태가 sparse인 경우, 테이블을 순회할 때 상대적으로 비효율적. 
<알고리즘 설명>
- 헤시테이블과 거의 같다.
- 데이터(key)는 자신의 엔트리(slot)이 정해져 있음. 데이터(key)가 중복된 경우, 정렬된 상태로 체이닝(링크드 리스트) 됨
- 엔트리 마다 데이터(key)의 수를 저장하고 있을 경우, 다양한 문제에 적용 가능 
#define MAX_NUM 1000000

struct Slot {
	int count;
	Node * head;
};

struct CountingSort {

	int totalCount;
	Slot slots[MAX_NUM];
};
[출처] counting 정렬|작성자 voyager759
