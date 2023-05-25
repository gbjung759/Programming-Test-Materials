#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* table;

int* createTable(char* string, int stringLen) {

	int j;
	table = (int*)malloc(sizeof(int) * (stringLen + 1));
	table[0] = -1;

	for (int i = 1; i < stringLen + 1; i++) 
		table[i] = 0;

	j = 0;

	for (int k = 1; k < stringLen; k++) {

		while (string[j] != string[k] && j > 0) {
			j = table[j];
		}

		if (string[j] == string[k]) {
			table[k+1] = ++j;
		}
	}

	return table;
}

void KMP(char *string, char *pattern) {

	int* table;

	int stringLen = strlen(string);
	int patternLen = strlen(pattern);
	int distance = 0, idx = 0, cnt = 0;
	int findFlag = 0;

	// 최대 경계 너비 테이블 채우기
	table = createTable(pattern, patternLen);

	while(1) {
		idx = 0;

		// 허용 범위를 벗어나면 반복문 나가기
		if (distance + patternLen > stringLen)
			break;

		while(string[idx+distance] == pattern[cnt]){
			cnt++; // 일치 갯수 증가
			idx++;// 인덱스 증가

			if (cnt == patternLen) {
				printf("%d번째에서 찾기 완료!\n", distance+1);
				findFlag = 1;
				break;
			}
		}

		distance = distance + (cnt - table[cnt]); // 이동거리 계산
		cnt = 0; // 일치 갯수 초기화
	}

	if (findFlag == 0)
		printf("해당 패턴을 찾지 못했습니다.\n");
}


int main() {

	char* string = "ABAABACABAACCABACABACABAACABACABAAC";
	char* pattern = "ABACABAAC";

	KMP(string, pattern);	

}
