void quickSort(register data* array, int s, int e) {
	register int l = s, r = e;
	register data pivot;
	
	callCnt2++;
	pivot = array[(s+e) >> 1];
	while (l <= r) {
		while (array[l] < pivot) l++;
		while (array[r] > pivot) r--;
		if (l <= r) {
			swap(&array[l], &array[r]);
			++l, --r;
		}
	}
	if (s < r) quickSort2(array, s, r);
	if(l < e) quickSort2(array, l, e);
}
