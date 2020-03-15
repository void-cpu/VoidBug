#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class Getmax
{
    /**
     * 此类的方法如下：
     *  即得到的stack.top()即为结果，即为最大值的所求
    **/
public:
    void pushStack(int number)
    {
        stack1.push(number);
        if (stack2.empty())
            stack2.push(number);
        else if (number >= stack2.top())
            stack2.push(number);
    }

    int popStack()
    {
        int num1;
        if (stack1.top() == stack2.top())
        {
            stack1.pop();
            num1 = stack2.top();
            stack2.pop();
        }
        else
        {
            num1 = stack1.top();
            stack1.pop();
        }
        return num1;
    }

private:
    stack<int> stack1, stack2;
};

class Getmin
{
    /**
     * 此类的方法如下：
     *  即得到的stack.top()即为结果，即为最小值的所求
    **/
public:
    void pushStack(int number)
    {
        stack1.push(number);
        if (stack2.empty())
            stack2.push(number);
        else if (number <= stack2.top())
            stack2.push(number);
    }

    int popStack()
    {
        int num1;
        if (stack1.top() == stack2.top())
        {
            stack1.pop();
            num1 = stack2.top();
            stack2.pop();
        }
        else
        {
            num1 = stack1.top();
            stack1.pop();
        }
        return num1;
    }

private:
    stack<int> stack1, stack2;
};

class QueueToStack
{
private:
    queue<int> Date, Help;

public:
    void QueueToStack_push(int x)
    {
        /**
         *我不能确定返回的是那个队列，
         * 但是我一定确定的是一定是导致后的队列的队列的顶端即为所求
        **/
        if (!Date.empty())
        {
            Help.push(x);
            while (!Date.empty())
            {
                Help.push(Date.front());
                Date.pop();
            }
        }
        else
        {
            Date.push(x);
            while (!Help.empty())
            {
                Date.push(Help.front());
                Help.pop();
            }
        }
    }

    void QueueToStack_pop()
    {
        if (!Date.empty() && Help.empty())
            cout << "The Stack is empty." << endl;
        else if (!Date.empty())
            Date.pop();
        else
            Help.pop();
    }

    bool QueueToStack_empty()
    {
        return (Date.empty() && Help.empty());
    }

    int QueueToStack_top()
    {
        if (!Date.empty() && Help.empty())
            cout << "The Stack is empty" << endl;
        else if (!Date.empty())
            return Date.front();
        else
            return Help.front();
    }
};

class StackToQueue
{
private:
    stack<int> Datestack, Helpskack;

public:
    void StackToQueue_push(int x)
    {
        if (!Datestack.empty())
        {
            Helpskack.push(x);
            while (!Datestack.empty())
            {
                Helpskack.push(Datestack.top());
                Datestack.pop();
            }
        }
        else
        {
            Datestack.push(x);
            while (!Helpskack.empty())
            {
                Datestack.push(Helpskack.top());
                Helpskack.pop();
            }
        }
    }

    void StackToQueue_pop()
    {
        if (!Datestack.empty() && Helpskack.empty())
            cout << "The Queue is empty" << endl;
        else if (!Datestack.empty())
            Datestack.pop();
        else
            Helpskack.pop();
    }

    bool StackToQueue_empty()
    {
        return (Datestack.empty() && Helpskack.empty());
    }

    int top()
    {
        if (!Datestack.empty())
            return Datestack.top();
        else
            Helpskack.top();
    }
};

class Pet
{
    /**
     *宠物的基类 
    **/
public:
    Pet(string type) { this->type = type; }
    string getPetType() { return type; }

private:
    string type;
};

class Dog : public Pet
{
    /**
     *派生类=>继承于宠物类=>狗这个类
    **/
public:
    Dog() : Pet("dog") {}
};

class Cat : public Pet
{
    /**
     *派生类=>继承于宠物类=>猫这个类
    **/
public:
    Cat() : Pet("cat") {}
};

class PetStamp
{
public:
    PetStamp(Pet p, long count) : pet(p) { this->count = count; }
    Pet getPet() { return pet; }
    long getCount() { return count; }
    string getPetType() { return pet.getPetType(); }

private:
    Pet pet;
    long count;
};

class CatDogQue
{
public:
    CatDogQue()
    {
        count = 0;
    }

    void push(Pet pet)
    {
        if ("dog" == pet.getPetType())
            dogQ.push(PetStamp(pet, count++));
        else if ("cat" == pet.getPetType())
            catQ.push(PetStamp(pet, count++));
        else
            cout << "err,not dog or cat!";
        return;
    }

    Pet popAll()
    {
        if (!catQ.empty() && !dogQ.empty())
        {
            if (dogQ.front().getCount() < catQ.front().getCount())
            {
                Pet tmp = dogQ.front().getPet();
                dogQ.pop();
                return tmp;
            }
            else
            {
                Pet tmp = catQ.front().getPet();
                catQ.pop();
                return tmp;
            }
        }
        else if (!catQ.empty())
        {
            Pet tmp = catQ.front().getPet();
            catQ.pop();
            return tmp;
        }
        else if (!dogQ.empty())
        {
            Pet tmp = dogQ.front().getPet();
            dogQ.pop();
            return tmp;
        }
        else
            cout << "Error,empty queue!";
    }

    Dog popDog()
    {
        if (!dogQ.empty())
        {
            Pet tmpP = dogQ.front().getPet();
            Dog tmpD;
            Pet *pd = &tmpD;
            *pd = tmpP;

            dogQ.pop();
            return tmpD;
        }
        else
            cout << "Error,empty dog queue!";
    }

    Cat popCat()
    {
        if (!catQ.empty())
        {
            Pet tmpP = catQ.front().getPet();
            Cat tmpC;
            Pet *pc = &tmpC;
            *pc = tmpP;

            catQ.pop();
            return tmpC;
        }
        else
            cout << "Error,empty cat queue!";
    }

    bool isEmpty() { return dogQ.empty() && catQ.empty(); }

    bool isDogEmpty() { return dogQ.empty(); }

    bool isCatEmpty() { return catQ.empty(); }

private:
    queue<PetStamp> dogQ;
    queue<PetStamp> catQ;
    long count;
};

class RotationPrintArray
{
public:
    void spiralOrderPrint(vector<vector<int> > matrix)
    {
        /**
         * 打印完一圈然后再去打印一圈
        **/
        int tR = 0, tC = 0, dR = matrix.size() - 1, dC = matrix[0].size() - 1;
        while (tR <= dR && tC <= dC)
            printEdge(matrix, tR++, tC++, dR--, dC--);
    }

private:
    void printEdge(vector<vector<int> > m, int tR, int tC, int dR, int dC)
    {
        /**
         * 当tr==dr时候，说明这个数组只有一行
         * 当tC==dC时候，说明这个数组只有一列
         * 如果都不是呢，
         * curC=tC,curR=tR;即curC为左上角的纵坐标，curR为右上角的纵坐标。
        **/
        if (tR == dR)
        {
            for (int i = tC; i <= dC; i++)
                cout << m[tR][i] << " ";
        }
        else if (tC == dC)
        {
            for (int i = tR; i < dR; i++)
                cout << m[tC][i] << " ";
        }
        else
        {
            int curC = tC, curR = tR;
            while (curC != dC)
                cout << m[tR][curC++] << " ";
            while (curR != dR)
                cout << m[curR++][dC] << " ";
            while (curC != tC)
                cout << m[dR][curC--] << " ";
            while (curR != tR)
                cout << m[curR--][tC] << " ";
        }
    }
};

class RotationPrintArray90
{
public:
    void spiralOrderPrint(vector<vector<int> > matrix)
    {
        int tR = 0, tC = 0, dR = matrix.size() - 1, dC = matrix[0].size() - 1;
        while (tR <= dR && tC <= dC)
            printEdgeprintEdge(matrix, tR++, tC++, dR--, dC--);
    }
    void Rotate(vector<vector<int> > &matrix)
    {
        if (matrix.empty())
            return;
        else
        {
            int tmp, m = matrix.size(), n = matrix[0].size();
            for (int i = 0; i < m / 2; i++)
                for (int j = i + 1; j < n - i; j++)
                {
                    tmp = matrix[i][j];
                    matrix[i][j] = matrix[n - 1 - j][i];
                    matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                    matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
                    matrix[j][n - 1 - i] = tmp;
                }
        }
    }

private:
    void printEdgeprintEdge(vector<vector<int> > m, int tR, int tC, int dR, int dC)
    {
        int times = dC - tC;
        int tmp = 0;
        for (int i = 0; i != times; i++)
        {
            tmp = m[tR][tC + i];
            m[tR][tC + i] = m[dR - i][tC];
            m[dR - i][tC] = m[dR][dC - i];
            m[dR][dC - i] = m[tR + i][dC];
            m[tR + i][dC] = tmp;
        }
    }
};
class Print
{
public:
    void PrintZhi(vector<vector<int> > Array)
    {
        int Aa, Ab, Ba, Bb, ENDR = Array.size() - 1, ENDC = Array[0].size() - 1;
        bool FormUp = false;

        while (Aa != ENDR + 1)
        {
            PrintLeven(Array, Aa, Ab, Ba, Bb, FormUp);
            Aa = Ab == ENDC ? Aa + 1 : Aa;
            Ab = Ab == ENDC ? Ab : Ab + 1;
            Bb = Bb == ENDR ? Bb + 1 : Bb;
            Ba = Ba == ENDR ? Ba : Ba + 1;
            FormUp = !FormUp;
        }
        cout << endl;
    }

private:
    vector<vector<int> > Array;

    vector<int> printMatrix(vector<vector<int> > Array, int n, int m)
    {
        vector<int> ans;
        int dir = 1;

        for (int i = 0; i < n; i++)
        {
            if (dir > 0)
            {
                for (int j = 0; j < m; j++)
                    ans.push_back(Array[i][j]);
            }
            else
            {
                for (int j = m - 1; j >= 0; j--)
                    ans.push_back(Array[i][j]);
            }

            dir = -1 * dir;
        }

        return ans;
    }
    void PrintLeven(vector<vector<int> > Array, int tr, int tc, int dr, int dc, bool f)
    {
        if (f)
        {
            while (tr != dr + 1)
            {
                cout << Array[tr++][tc--] << " ";
            }
        }
        else
        {
            while (dr != tr - 1)
            {
                cout << Array[dr--][dc++] << " ";
            }
        }
    }
};