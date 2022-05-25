#define _crt_secure_no_warnings
#pragma warning(disable : 4996)
#include <stdio.h>
#include <time.h>


int keylist[100000];
int keylist_sorted[100000];
char filename_keylist[128] = "C:\\Users\\Recarrdo\\Desktop\\sort file\\Num_list2.txt";
char filename_keylist_sorted[128] = "C:\\Users\\Recarrdo\\Desktop\\sort file\\Num_list2_sorted.txt";


// verify your sorting results with the validation sequence
int check_sorted(int* sorting_result)
{
    int verfiedResult = 0;

    // Read the sorted result of the test sequence
    FILE* fs;
    fs = fopen(filename_keylist_sorted, "r");

    if (fs == NULL)
    {
        printf("The test seqeunce file (%s) is not accessible\n", filename_keylist_sorted);
        return verfiedResult;
    }


    int index = 0;
    while (fscanf(fs, "%d", &keylist_sorted[index]) == 1)
    {
        if (sorting_result[index] == keylist_sorted[index])
        {
            verfiedResult++;
        }
        index++;
    }

    fclose(fs);

    return verfiedResult;

}

// program your bubble sorting algorithm
void bubbleSorting(int* original_list, int numofkeys)
{
    int temp;

    for (int i = 0; i < numofkeys - 1; i++)    // 요소의 개수만큼 반복
    {
        bool flag = false;
        for (int j = 0; j < numofkeys - i - 1; j++)   // 요소의 개수 - 1만큼 반복
        {
            if (original_list[j] > original_list[j + 1])          // 현재 요소의 값과 다음 요소의 값을 비교하여
            {                                 // 큰 값을
                temp = original_list[j];
                original_list[j] = original_list[j + 1];
                original_list[j + 1] = temp;            // 다음 요소로 보냄
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }
}

void merge(int* original_list, int tmp[], int start, int mid, int end)
{
    for (int i = start; i <= end; i++)
    {
        tmp[i] = original_list[i];
    }
    int part1 = start;
    int part2 = mid + 1;
    int index = start;
    while (part1 <= mid && part2 <= end)
    {
        if (tmp[part1] <= tmp[part2])
        {
            original_list[index] = tmp[part1];
            part1++;
        }
        else
        {
            original_list[index] = tmp[part2];
            part2++;
        }
        index++;
    }
    for (int i = 0; i <= mid - part1; i++)
    {
        original_list[index + i] = tmp[part1 + i];
    }
}

void mergesort(int* original_list, int tmp[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(original_list, tmp, start, mid);
        mergesort(original_list, tmp, mid + 1, end);
        merge(original_list, tmp, start, mid, end);
    }
}

// program your second sorting algorithm
void mergesort(int* original_list, int numofkeys) //merge sort
{
    int tmp[100000];
    mergesort(original_list, tmp, 0, 100000 - 1);
}

void sorting(int* original_list, int numofkeys)
{
    bubbleSorting(original_list, numofkeys);

    // yourSecondSorting(original_list, numofkeys);
    mergesort(original_list, numofkeys);
    return;
}


int main()
{

    // read the test sequence
    int numofkeys = 0;
    FILE* fs = fopen(filename_keylist, "r");
    if (fs == NULL)
    {
        printf("The test seqeunce file (%s) is not accessible\n", filename_keylist);
        return 0;
    }

    while (fscanf(fs, "%d", &keylist[numofkeys]) == 1)
    {
        numofkeys++;

    }

    fclose(fs);


    // begin sorting with the test sequence
    clock_t start, end;
    start = (double)clock();
    sorting(keylist, numofkeys);
    end = (double)clock();

    // compute the time of sorting
    float computationTime = (double)(end - start); // get the total time cost 
    printf("Total time cost(ms) : %lf \n", computationTime);


    // verify with the validation sequence
    int verifiedResult = check_sorted(keylist);

    printf("=============== RESULT =============== \n");
    if (verifiedResult == numofkeys)
    {
        printf("Your sorting algorithm resulted in the correct ascending order for the given list \n\n");
    }
    else
        printf("Your sorting algorithm failed to produce the correct ascending order for the given list \n\n");


}