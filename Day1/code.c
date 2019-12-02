#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE* file;
	file = fopen("wordcount", "r");
	int val = 0;
	int sum = 0;
	int len = 0;

	while(fscanf(file, "%d\n", &val) != EOF)
	{
		len++;
	}

	fclose(file);
	file = fopen("wordcount", "r");

	for(int i=0; i<len; i++)
	{
		fscanf(file, "%d\n", &val);
		val = (val/3)-2;
		sum = sum + val;

		for(val = (val/3)-2; val > 0; val=(val/3)-2)
		{
			sum = sum + val;
		}
	}

	fclose(file);

	printf("%d", sum);

	return 0;
}
