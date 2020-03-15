#include <iostream>
#include <stdlib.h>
using namespace std;
#define MaxLenght 10000

class Sorts
{
public:
    void maxSelectSort(int Array[], int lenght)
    {
        for (int i = 0; i < lenght; i++)
        {
            for (int j = i + 1; j < lenght; j++)
                if (Array[i] < Array[j])
                    swap(Array, i, j);
        }
    }
    void minSelectSort(int Array[], int lenght)
    {
        for (int i = 0; i < lenght; i++)
        {
            for (int j = i + 1; j < lenght; j++)
                if (Array[i] > Array[j])
                    swap(Array, i, j);
        }
    }

    void PrintArray(int Array[], int Lenght)
    {
        for (int i = 0; i < Lenght; i++)
            std::cout << Array[i] << " ";
    }

    void maxBubbleSort(int Array[], int lenght)
    {
        for (int i = 0; i < lenght - 1; i++)
        {
            for (int j = 0; j < lenght - 1; j++)
                if (Array[j] < Array[j + 1])
                    swap(Array, j, j + 1);
        }
    }
    void minBubbleSort(int Array[], int lenght)
    {
        for (int i = 0; i < lenght - 1; i++)
        {
            for (int j = 0; j < lenght - 1; j++)
                if (Array[j] > Array[j + 1])
                    swap(Array, j, j + 1);
        }
    }

    void minInsertionSort(int Array[], int lenght)
    {
        for (int i = 1; i < lenght; i++)
        {
            for (int j = i - 1; j >= 0 && Array[j] > Array[j + 1]; j--)
                swap(Array, j, j + 1);
        }
    }
    void maxInsertionSort(int Array[], int lenght)
    {
        for (int i = 1; i < lenght; i++)
        {
            for (int j = i - 1; j >= 0 && Array[j] < Array[j + 1]; j--)
                swap(Array, j, j + 1);
        }
    }

    void MergerSort(int Array[], int Lenght)
    {
        int *Arrayhelp = new int[Lenght];
        mergeSortHelper(Array, Arrayhelp, 0, Lenght - 1);
        delete[] Arrayhelp;
    }

    void QuickSort(int Array[], int Left, int Right)
    {
        if (Left < Right)
        {
            int Mid = patition_Sort(Array, Left, Right);
            QuickSort(Array, Left, Mid);
            QuickSort(Array, Mid + 1, Right);
        }
    }

    void RandQuickSort(int *Array, int Left, int q)
    {
        if (Left < q)
        {
            int Right = random_patition(Array, Left, q);
            RandQuickSort(Array, Left, Right - 1);
            RandQuickSort(Array, Right + 1, q);
        }
    }

    void heapSort(int Array[], int Lenght)
    {
        for (int i = Lenght / 2 - 1; i >= 0; i--)
            adjust(Array, Lenght, i);
        // 调整大根堆,将当前最大的放置到数组末尾,将未完成排序的部分继续进行堆排序
        for (int i = Lenght - 1; i >= 1; i--)
        {
            swap(Array, 0, i);
            adjust(Array, i, 0);
        }
    }

    void CountSort(int Array[], int n)
    {
        string errorstring = "你输入的数据过大，本算法适用于极小规模运算";
        if (n > 100)
        {
            cout << errorstring;
            return;
        }
        int *sorted_arr = new int[n], *count_arr = new int[MaxLenght], i;
        //初始化计数数组,统计i的次数
        for (i = 0; i < MaxLenght; i++)
            count_arr[i] = 0;
        for (i = 0; i < n; i++)
            count_arr[Array[i]]++;

        //对所有的计数累加,逆向遍历源数组（保证稳定性），根据计数数组中对应的值填充到先的数组中
        for (i = 1; i < 100; i++)
            count_arr[i] += count_arr[i - 1];
        for (i = n; i > 0; i--)
        {
            sorted_arr[count_arr[Array[i - 1]] - 1] = Array[i - 1];
            count_arr[Array[i - 1]]--;
        }

        for (int i = 0; i < n; i++)
            Array[i] = sorted_arr[i];
        delete[] sorted_arr, count_arr;
    }

    /**
        函数说明：
            实现基数排序
        参数说明：
            data：数据数组
            n：data数组的最高位
    **/
    void RadixSort(int Array[], int n)
    {
        int d = maxbit(Array, n), radix = 1, TempHelp[MaxLenght], count[MaxLenght];
        for (int i = 0; i < d; i++)
        {
            /**
                * 首先进行清桶的操作,
                * 统计每个桶中含有数字的数量,
                * 将tmp中的位置依次分配给每个桶,
                * 意思就是为每个桶里面还有的数量都留下够用的空间
            **/
            for (int j = 0; j < 10; j++)
                count[j] = 0;
            for (int j = 0; j < n; j++)
            {
                int k = (Array[j] / radix) % 10;
                count[k]++;
            }
            for (int j = 1; j < 10; j++)
                count[j] += count[j - 1];
            /**
                * 这里想不明白可以理解为相邻两个数位之间的差表示的就是给这个桶分配的空间；
            **/
            /**
                * 将桶中的记录依次收集到tmp中,
                * 得到他在哪一个桶里面,因为上面已经给这个桶留下了相应的空间，
                * 所以只需要一次向后减1，就可以排到适当的位置
            **/
            for (int j = n - 1; j >= 0; j--)
            {
                int k = (Array[j] / radix) % 10;
                TempHelp[count[k] - 1] = Array[j];
                count[k]--;
            }
            /**
                * 将临时数组的内容复制到data数组中
            **/
            for (int j = 0; j < n; j++)
                Array[j] = TempHelp[j];
            radix *= 10;
        }
    }

private:
    int maxbit(int Array[], int n)
    {
        int max_num = 1, num = 10;
        for (int i = 0; i < n; i++)
        {
            while (Array[i] >= num)
            {
                num *= 10;
                max_num++;
            }
        }
        return max_num;
    }

    void swap(int Array[], int i, int j)
    {
        int temp = Array[i];
        Array[i] = Array[j];
        Array[j] = temp;
    }

    void Merger(int Array[], int Arrayhelp[], int Left, int Mid, int Right)
    {
        int i = Left, j = Mid + 1, k = Left;
        while (k <= Right)
        {
            if (i > Mid)
                Arrayhelp[k++] = Array[j++];
            else if (j > Right)
                Arrayhelp[k++] = Array[i++];
            else
                Arrayhelp[k++] = Array[i] > Array[j] ? Array[j++] : Array[i++];
        }
        for (int k = Left; k <= Right; k++)
            Array[k] = Arrayhelp[k];
    }
    void mergeSortHelper(int Array[], int Arrayhelp[], int Left, int Right)
    {
        if (Left >= Right)
            return;
        int Mid = (Left + Right) / 2;
        mergeSortHelper(Array, Arrayhelp, Left, Mid);
        mergeSortHelper(Array, Arrayhelp, Mid + 1, Right);
        Merger(Array, Arrayhelp, Left, Mid, Right);
    }

    int patition_Sort(int Array[], int Left, int Right)
    {
        int i = Left, j = Right + 1, temp = Array[Left];
        /*i为左半部分的第一个下标 ,j为右半部分的第一个下标 ，temp为//第一个元素 。whille循环功能是从左到右找更大的，从右到左找更小的。*/
        while (true)
        {
            /*检查数组是否有序，如果无序，则i和j分别存储前面比a[p]大，后面比a[p]小的元素的值*/
            while (i < Right && Array[++i] < temp)
                ;
            while (Array[--j] > temp)
                ;
            if (i >= j)
                break; /*数组无序*/
            swap(Array, i, j);
        }
        swap(Array, j, Left);
        return j;
    }

    int random_patition(int Array[], int Left, int Right)
    {
        int tempHelp, i = Left - 1, k = Left + rand() % (Right - Left + 1);
        //仍然将随机的枢轴交换到最后
        swap(Array, Right, k);
        tempHelp = Array[Right];
        /*保证左边的值永远比temp小,如果是比第i项大，好，去交换值，这样据保证了左半部分一定是有顺序的，而右面却没有  */
        for (int j = Left; j <= Right - 1; j++)
            if (Array[j] <= tempHelp)
                swap(Array, ++i, j);
        //最后主元交换，因为当结束后所有数据都有序了，但是第i+项和末尾项应该位置是相反的，及最后的那一项即为所求项。
        swap(Array, i + 1, Right);
        return ++i;
    }

    void adjust(int Array[], int Lenght, int indexs)
    {
        int Leftindex = 2 * indexs + 1, Rightindex = 2 * indexs + 2, maxIdx = indexs;
        if (Leftindex < Lenght && Array[Leftindex] > Array[maxIdx])
            maxIdx = Leftindex;
        if (Rightindex < Lenght && Array[Rightindex] > Array[maxIdx])
            maxIdx = Rightindex;
        if (maxIdx != indexs)
        {
            swap(Array, maxIdx, indexs);
            adjust(Array, Lenght, maxIdx);
        }
    }
};

class Others
{
public:
    void Patitions(int Array[], int len, int number)
    {
        int p = 0, left = 0, right = len - 1;
        while (p <= right)
        {
            if (Array[p] < number)
                swap(Array, p++, left);
            else if (Array[p] > number)
                swap(Array, p, right--);
            else
                p++;
        }
    }

    int LittleSums(int a[], int len)
    {
        int *b = new int[len], Liltlesum = littlesum(a, b, 0, len - 1);
        delete[] b;
        return Liltlesum;
    }

    int GetMax(int *Array, int Leftindex, int Rightindex)
    {
        if (Leftindex == Rightindex)
            return Array[Leftindex];
        int minndex = (Leftindex + Rightindex) / 2;
        return max(GetMax(Array, Leftindex, minndex), GetMax(Array, minndex + 1, Rightindex));
    }

    int GetMin(int *Array, int Leftindex, int Rightindex)
    {
        if (Leftindex == Rightindex)
            return Array[Leftindex];
        int minndex = (Leftindex + Rightindex) / 2;
        return min(GetMin(Array, Leftindex, minndex), GetMin(Array, minndex + 1, Rightindex));
    }

    void rendom(int Array[], int Lenght)
    {
        for (int k = 0; k < Lenght; k++)
        {
            Array[k] = rand() % Lenght;
        }
    }

    int maxGap(int Array[], int lenght)
    {
        /***
	        * minArr的作用是记录每个桶中的最小数
	        * maxArr的作用是记录每个桶中的最大数
	        * hasNum的作用是记录桶中是否有数
	        * MaxGap=>记录最大差值 
	        * LastMax=>记录当前空桶的上一个桶的最大值
	        * i=>循环变量
	        * while的作用是，可能会有多个空桶，遍历桶，找到其中的空桶
	    ***/
        int minnumber = GetMin(Array, 0, lenght - 1), maxnumber = GetMax(Array, 0, lenght - 1), *minArr = new int[lenght + 1], *maxArr = new int[lenght + 1];
        bool hasNum[lenght + 1] = {0};

        /*
		    求出每一个数所在的桶的编号
	    */

        for (int i = 0; i < lenght; ++i)
        {
            int bocketID = bocketNum(Array, i, minnumber, maxnumber, lenght);
            minArr[bocketID] = hasNum[bocketID] ? min(minArr[bocketID], Array[i]) : Array[i];
            maxArr[bocketID] = hasNum[bocketID] ? max(maxArr[bocketID], Array[i]) : Array[i];
            hasNum[bocketID] = true;
        }

        int MaxGap = 0, LastMax = 0, i = 0;

        while (i < lenght + 1)
        {
            while (i < lenght + 1 && hasNum[i])
                i++;
            if (i == lenght + 1)
                break;
            LastMax = maxArr[i - 1];
            while (i < lenght + 1 && !hasNum[i])
                i++;
            if (i == lenght + 1)
                break;
            MaxGap = max(MaxGap, minArr[i] - LastMax);
        }
        delete[] minArr, maxArr;
        return MaxGap;
    }

private:
    int mergeSum(int a[], int b[], int l, int m, int r)
    {
        int Sum = 0, i = l, j = m + 1, k = l;
        while (k <= r)
        {
            if (i > m)
                b[k++] = a[j++];
            else if (j > r)
                b[k++] = a[i++];
            else
            {
                if (a[i] > a[j])
                    b[k++] = a[j++];
                else
                {
                    Sum += a[i] * (r - j + 1);
                    b[k++] = a[i++];
                }
            }
        }

        for (int k = l; k <= r; k++)
            a[k] = b[k];
        return Sum;
    }

    /*
        t(n)=at(n/b)+O(n^d);
        n为数据总量，b为平均分成几份，a为出现的次数，O（n^d）为额外时间复杂度
        if(log(b,a))>d=>O(nlog(b,a);
        else if(log(b,a)==d)=>O(n^d*log(b,a));
        else log(b,a)<d =>O(n^d);
        master前提：你划分的子过程的规模是一样的。
    */

    int littlesum(int a[], int b[], int l, int r)
    {
        if (l >= r)
            return 0;
        int m = (l + r) / 2;
        return littlesum(a, b, l, m) + littlesum(a, b, m + 1, r) + mergeSum(a, b, l, m, r);
    }

    void swap(int Array[], int i, int j)
    {
        int temp = Array[i];
        Array[i] = Array[j];
        Array[j] = temp;
    }

    int bocketNum(int a[], int i, int min, int max, int len)
    {
        return (a[i] - min) * len / (max - min);
    }
};
#include <iostream>
#include <stack>
using namespace std;

class MyStack
{
public:
    /**
        *类的作用：实现栈的基本功能。 
        * MyStack函数功能:初始化栈空间
        *deleteMyStack函数功能:回收栈空间内存
        *clearStack函数功能:清空栈
        *stackEmpty函数功能:判空栈，若空返回true
        *stackFull函数功能:判满栈，若满返回true
        *stackLength函数功能:栈中元素个数
        *push(elem)函数功能:元素入栈，栈顶上升
        *stackpop(char &elem)函数功能:元素出栈，栈顶下降
        *stackTraverse(bool isFromBottom)函数功能:遍历栈中元素 isFromBottom=1，从栈底遍历 
        **m_pBuffer 栈空间指针 
        *m_isize 栈容量
        * m_itop 栈顶，也是栈中元素个数
    * **/

    MyStack(int size)
    {
        m_isize = size;
        m_pBuffer = new char[size];
        m_itop = 0;
    }

    ~MyStack() { delete[] m_pBuffer; }

    void clearStack() { m_itop = 0; }

    bool stackEmpty() { return 0 == m_itop ? true : false; }

    bool stackFull() { return m_isize == m_itop ? true : false; }

    int stackLength() { return m_itop; }

    void stackpush(char elem)
    {
        if (stackFull())
            return;
        m_pBuffer[m_itop] = elem;
        m_itop++;
    }

    void stackpop(char &elem)
    {
        if (stackEmpty())
            return;
        m_itop--;
        elem = m_pBuffer[m_itop];
        return;
    }

    void stackTraverse(bool isFromBottom)
    {
        if (isFromBottom)
            for (int i = 0; i < m_itop; i++)
                cout << m_pBuffer[i] << " ";
        else
            for (int i = m_itop - 1; i >= 0; i--)
                cout << m_pBuffer[i] << " ";
    }

private:
    char *m_pBuffer;

    int m_isize, m_itop;
};
