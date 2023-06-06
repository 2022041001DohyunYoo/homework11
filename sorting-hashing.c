/*
 * sorting-hashing.c
 *
 * Sorting & Hashing
 * School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE         13 //배열 최대 길이
#define MAX_HASH_TABLE_SIZE    MAX_ARRAY_SIZE

// 배열 초기화 함수 정의 
int initialize(int **a);
int freeArray(int *a); //배열 할당 해제
void printArray(int *a);//배열 출력

int selectionSort(int *a);//선택 정렬
int insertionSort(int *a);//삽입 정렬
int bubbleSort(int *a);//버블 소팅
int shellSort(int *a);//셸 정렬
//재귀 함수를 이용한 퀵 정렬 정의 
int quickSort(int *a, int n);


//해시 코드 생성기, key % MAX_HASH_TABLE_SIZE
int hashCode(int key);

//배열 a를 해시 테이블에 저장 
int hashing(int *a, int **ht);

//해시 테이블에서 key를 검색하여 인덱스 반환
int search(int *ht, int key);


int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));//난수 시드 설정

    printf("[-----[유도현][2022041001]-----]");
    printf("\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");
        //양식

        printf("Command = ");
        scanf(" %c", &command); //명령 받기

        //커맨드를 받아서 함수를 실행 (자세한 설명은 양식에 있으니 생략)
        switch(command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);
            //퀵 소팅 전후의 배열 출력

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;
            //해싱 전후의 배열 상태 출력

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            //해시테이블 참고해서 검색
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int *temp = NULL;

    // 포인터가 NULL일 경우 메모리 할당
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  // 포인터에 할당된 배열 연결
    } else
        temp = *a;

    // 임의의 숫자를 배열에 저장
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{
    //포인터가 널이 아니면 할당해제
    if(a != NULL)
        free(a);
    return 0;
}

void printArray(int *a)
{
    //배열 비어있으면 출력
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    //배열의 위치 (인덱스) 출력
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    //배열의 요소 출력
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}


int selectionSort(int *a)
{
    int min;//최소
    int minindex;//최소값의 위치
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); //정렬 전 배열 출력

    //선택 정렬 알고리즘
    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;
        min = a[i];
        for(j = i+1; j < MAX_ARRAY_SIZE; j++)
        {
            if (min > a[j])
            {
                //현재 요소가 최소 보다 작으면 최소값을 변경
                min = a[j];
                minindex = j;
            }
        }
        //최소값을 현재 위치로 이동
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 배열 출력
    return 0;
}

int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); //정렬 전 배열 출력

    //삽입정렬 알고리즘
    //두번째 요소부터 마지막 요소까지 순회
    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];
        j = i;

        // 현재 요소를 이전 요소들과 비교하면서 적절한 위치에 삽입
        while (a[j-1] > t && j > 0)
        {
            // 이전 요소를 현재 위치로 이동
            a[j] = a[j-1];
            j--;
        }
        // 현재 요소를 적절한 위치에 삽입
        a[j] = t;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 배열 출력

    return 0; 
}

int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); //정렬 전 배열 출력

    //버블 소팅 알고리즘
    //배열 전체를 순회하며 앞뒤 요소를 비교하여 차순에 맞게 위치 교환
    for(i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 0; j < MAX_ARRAY_SIZE; j++)
        {
            // 이전 요소가 현재 요소보다 크면 위치 교환
            if (a[j-1] > a[j])
            {
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 배열 출력

    return 0;
}

int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);//정렬 전 배열 출력

    //간격 = h 만큼 떨어진 요소들을 묶어서 삽입 정렬
    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
    {
        //i를 시작으로 h만큼 떨어진 요소들을 선택해서 삽입 정렬 수행
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];
                k = j;
                //현재 선택된 요소를 이전 그룹 요소들과 비교하여 삽입할 위치 찾기
                while (k > h-1 && a[k-h] > v)
                {
                    //이전 그룹의 요소들보다 크면 이전 그룹의 요소를 현재 위치로 이동
                    a[k] = a[k-h];
                    k -= h;
                }
                //현재 요소를 해당 위치
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);//정렬 후 배열 출력

    return 0;
}

int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    //퀵 소팅 알고리즘
    if (n > 1)
    {
        v = a[n-1]; //a[n-1]을 피벗으로 선택
        i = -1;
        j = n - 1;

        while(1)//무한 루프
        {
            while(a[++i] < v);//a의 요소가 v보다 커질때까지 인덱스 증가
            while(a[--j] > v);//a의 요소가 v보다 작아질때까지 인덱스 감소

            if (i >= j) break;//i가 j보다 크거나 같으면 중지

            //a[i]와 a[j] 교체
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        //t와 a[i], a[i]와 a[n-1], a[n-1]과 t 교체
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i); //피벗 왼쪽 부분을 다시 퀵 소트
        quickSort(a+i+1, n-i-1); //피벗 오른쪽 부분을 다시 퀵 소트
    }


    return 0;
}

int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    // 해시 테이블이 NULL인 경우 메모리 할당
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  // 할당한 메모리의 주소를 전달 --> main에서 해시 테이블을 제어할 수 있도록 함
    } else {
        hashtable = *ht;    // 해시 테이블이 NULL이 아닐 경우, 테이블 재설정
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    int key = -1;
    int hashcode = -1;
    int index = -1;

    // 해시 테이블 초기화
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);


        // 해당 해시 코드 위치에 값이 없는 경우
        if (hashtable[hashcode] == -1)
        {
            hashtable[hashcode] = key;
        } else  {

            index = hashcode;

             // 충돌이 발생하면 다음 비어있는 위치를 찾아서 삽입
            while(hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
            }
            hashtable[index] = key;
        }
    }

    return 0;
}

int search(int *ht, int key)
{
    int index = hashCode(key);

    // 해시 테이블의 해당 인덱스에 값이 있으면 인덱스 반환
    if(ht[index] == key)
        return index;

    // 충돌이 발생하면 다음 위치를 찾아서 검색
    while(ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}
