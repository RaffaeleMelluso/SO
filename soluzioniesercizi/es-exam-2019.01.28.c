int range_of_even(int * nums, int length, int * min, int * max ){
	int i;
	
	if (nums == NULL || length <= 0 || min == NULL || max == NULL)
		return 0;

	/* usero` (*min == 1) come condizione per segnalare che tutti
	   i numeri sono dispari */
	*min = 1;
	for (i=0; i< length; i++) {
		if (~nums[i] & 1) {  /* equivale a (nums[i]%2 == 0) */
			if (*min == 1) {
				*min = *max = nums[i];
				continue; /* non necessario, solo per evitare due confronti */
			}
			if (nums[i] < *min)
				*min = nums[i];
			if (nums[i] > *max)
				*max = nums[i];
		}
	}
	if (*min == 1)
		return 0;
	else
		return 1;
}
