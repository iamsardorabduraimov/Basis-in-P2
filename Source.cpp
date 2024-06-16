/*
  -----------------------------------------------------------------------------------------------------------------
  | Условие задачи:                                                                                               |
  | Во входном файле заданы несколько функций. Образуют ли они базис?                                             |
  | Сначала во входном файле записано число - количество функций, далее все функции, каждая в отдельной строке.   |
  -----------------------------------------------------------------------------------------------------------------
 */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string>
#include<string.h>

using namespace std;

#pragma warning(disable:4996)

int ves(int n)
{
    int res = 0, i = 0;

    while (n)
    {
        res += n % 2;
        n /= 2;
    }

    return res;
}

int linear_fun(int* arr, int n)
{
    int ans = 1, i, k, len, num, * array, counter, index, index2, res = 0;
    len = 1 << n;

    num = (len * (len + 1)) / 2;

    array = (int*)malloc(num * sizeof(int));

    for (i = 0; i < len; ++i)
    {
        array[i] = arr[i];
    }

    counter = len - 1;
    index = len;
    index2 = 0;

    for (i = 0; i < len - 1; ++i)
    {
        for (k = 0; k < counter; ++k)
        {
            array[index] = (array[index2] + array[index2 + 1]) % 2;
            ++index2;
            ++index;
        }
        --counter;
        ++index2;
    }

    index = len;
    counter = 2;
    index2 = 0;
    --len;

    for (i = 0; i < index; ++i)
    {
        if (index2 == 0)
        {
            if (array[num - 1] == 1)
            {
                res = ves(len);
                if (res > 1) ans = 0;
            }
            index2 = 1;
            --num;
        }
        else
        {
            num -= counter;
            if (array[num] == 1)
            {
                res = ves(len);
                if (res > 1) ans = 0;
            }

            ++counter;
        }

        --len;
    }

    free(array); array = NULL;

    return ans;
}

int monotone(int* array, int n)
{
    int res = 1, k, index, first = 0;

    index = n / 2;

    while (index)
    {
        for (k = 0; k < n / 2; ++k)
        {
            if (array[first] > array[first + index])
            {
                res = 0;
            }
            //printf("%d %d %d %d ", array[first], array[first + index], first, first + index);

            ++first;

            if (first % index == 0)
            {
                first += index;
            }


        }
        //printf("\n");

        index /= 2;
        first = 0;
    }


    return res;
}




int main(int argc, char* argv[])
{
    FILE* f, * g;
    int n, i, error = 0, znachnost = 0, res = 0, * t0, * t1, * s, * m, * l, * fun, kolvoarg, k, len = 0, lsum = 0, t0sum = 0, t1sum = 0, ssum = 0, msum = 0;
    char* num;

    if (argc == 3)
    {
        f = fopen(argv[1], "r");

        if (f != NULL)
        {
            if (fscanf(f, "%d", &n) == 1)
            {
                if (n > 0)
                {
                    if (n < 5)
                    {
                        t0 = (int*)malloc(n * sizeof(int));
                        t1 = (int*)malloc(n * sizeof(int));
                        s = (int*)malloc(n * sizeof(int));
                        m = (int*)malloc(n * sizeof(int));
                        l = (int*)malloc(n * sizeof(int));

                        for (i = 0; i < n; ++i)
                        {
                            fscanf(f, "%d%d", &znachnost, &kolvoarg);

                            len = 1 << kolvoarg;
                            fun = (int*)calloc(len, sizeof(int));
                            num = (char*)malloc((len + 2) * sizeof(char));

                            fgets(num, len + 2, f);
                            //puts(num);
                            //printf("\n5");

                            for (k = 0; k < len; ++k)
                            {
                                if (num[k+1] == '1')
                                {
                                    ++fun[k];
                                }

                            }
                            //fscanf(f, "%c%c", &endofstr, &endofstr2);

                            //printf("%c %c\n", endofstr, endofstr2);


                            if (fun[0] == 0) t0[i] = 1;// checking whether this function belongs to class t0
                            else t0[i] = 0;

                            if (fun[len - 1] == 1)t1[i] = 1;// checking whether this function belongs to class t1 
                            else t1[i] = 0;

                            // checking whether the function is self-dual or not
                            for (k = 0; k < len / 2; ++k)
                            {
                                if (fun[len - k - 1] + fun[k] == 1)
                                {
                                    s[i] = 1;
                                }
                                else
                                {
                                    s[i] = 0;
                                    break;
                                }
                            }

                            //checking whether the function is linear or not
                            l[i] = linear_fun(fun, kolvoarg);

                            //checking whether the function is monotone or not
                            m[i] = monotone(fun, len);

                            //printf("%d %d %d %d %d\n", t0[i], t1[i], s[i], l[i], m[i]);

                            free(fun); fun = NULL;
                            free(num); num = NULL;
                        }

                        for (i = 0; i < n; ++i)
                        {
                            ssum += s[i];
                            lsum += l[i];
                            msum += m[i];
                            t0sum += t0[i];
                            t1sum += t1[i];
                        }

                        if (ssum < n && lsum < n && msum < n && t0sum < n && t1sum < n)
                        {
                            res = 1;
                        }

                        //printf("%d\n", res);

                        if (res == 1 && n > 1)
                        {
                            for (i = 0; i < n; ++i)
                            {
                                ssum -= s[i];
                                lsum -= l[i];
                                msum -= m[i];
                                t0sum -= t0[i];
                                t1sum -= t1[i];
                                if (ssum < n - 1 && lsum < n - 1 && msum < n - 1 && t0sum < n - 1 && t1sum < n - 1)
                                {
                                    res = 0;
                                }
                                ssum += s[i];
                                lsum += l[i];
                                msum += m[i];
                                t0sum += t0[i];
                                t1sum += t1[i];
                                //printf("%d\n", res);
                            }
                        }

                        g = fopen(argv[2], "w");

                        if (g != NULL)
                        {
                            fprintf(g, "%d", res);
                            fclose(g); g = NULL;
                        }
                        else error = -6;

                        free(t0); t0 = NULL;
                        free(t1); t1 = NULL;
                        free(s); s = NULL;
                        free(m); m = NULL;
                        free(l); l = NULL;
                    }
                    else
                    {
                        g = fopen(argv[2], "w");

                        if (g != NULL)
                        {
                            fprintf(g, "%d", res);
                            fclose(g); g = NULL;
                        }
                        else error = -6;
                    }
                }
                else error = -4;
            }
            else error = -3;

            fclose(f); f = NULL;
        }
        else error = -2;
    }
    else error = -1;



    return error;
}


