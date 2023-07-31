#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* pArray;
};

// Compute the hash function
int hash(int x)
{
	return x % 15;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i,j;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(&pHashArray[i] != NULL){
			printf("Index %d ->", i);
			for(j=0;j<hashSz;j++){
				printf("id: %d, name: %c, order: %d ->", pHashArray[i].pArray[j].id,pHashArray[i].pArray[j].name,pHashArray[i].pArray[j].order);
			}
			printf("\n\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int hashSz = 15;
	int i;
	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
    
	//memory allocation
	struct HashType *pHashArray = malloc(sizeof(struct HashType)* hashSz);

	for(i=0;i<hashSz;i++){
		pHashArray[i].pArray = malloc(sizeof(struct RecordType) * (recordSz/hashSz)+1);
	}

	for(i=0;i<recordSz;i++){
		int count = 0;
		//if record exists then create an index and place inside the hash array
		if(pHashArray != NULL && pRecords != NULL){
			int index = hash(pRecords[i].id);
			pHashArray[index].pArray[count] = pRecords[i];
		}
	}

	displayRecordsInHash(pHashArray, hashSz);

	return 0;
	}
}