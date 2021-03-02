// Graphs_Numeration_M.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

enum class Colors { WHITE, GRAY, BLACK };

void Init(int* Head, int n, int& Count)
{
    Count = 0;
    for (int i = 1; i <= n; i++)
    {
        Head[i] = 0;
        //std::cout << Head[i] << ' ';
    }
    //std::cout << std::endl;
}

void AddArc(char u, char v, int* Head, int* Adj, int* Next, int& Count)
{
    Count++;
    Adj[Count] = v - 'a' + 1;
    Next[Count] = Head[u - 'a' + 1];
    Head[u - 'a' + 1] = Count;
}

void MNumDFS(int u, Colors* Color, int* Head, int* Adj, int* Next, int* MNum, int &Cnt)
{
    if (Color[u] != Colors::WHITE)
    {
        return;
    }  
    Color[u] = Colors::GRAY;
    MNum[u - 1] = ++Cnt;
    int Cur = Head[u];
    while (Cur != 0)
    {
        int v = Adj[Cur];
        MNumDFS(v, Color, Head, Adj, Next, MNum, Cnt);
        Cur = Next[Cur];
    }
    Color[u] = Colors::BLACK;
}

void NNumDFS(int u, Colors* Color, int* Head, int* Adj, int* Next, int* NNum, int& Cnt)
{
    if (Color[u] != Colors::WHITE)
    {
        return;
    }
    Color[u] = Colors::GRAY;
    int Cur = Head[u];
    while (Cur != 0)
    {
        int v = Adj[Cur];
        NNumDFS(v, Color, Head, Adj, Next, NNum, Cnt);
        Cur = Next[Cur];
    }
    Color[u] = Colors::BLACK;
    NNum[u - 1] = Cnt;
    Cnt--;
}

int main()
{
    int n, m;
    std::ifstream input("input.txt");
    if (!input)
    {
        exit(1);
    }
    input >> n >> m;
    int* Head = new int[n + 1];
    int* Adj = new int[m + 1];
    int* Next = new int[m + 1];
    int Count;
    char u, v;

    Init(Head, n, Count);

    for (int i = 0; i < m; i++)
    {
        input >> u >> v;
        AddArc(u, v, Head, Adj, Next, Count);
    }
    input.close();

    Colors* Color = new Colors[n + 1];
    for (int i = 1; i <= n; i++)
    {
        Color[i] = Colors::WHITE;
    }
    int Cnt = 0;
    int* MNum = new int[n];
    for (int i = 1; i <= n; i++)
    {
        MNumDFS(i, Color, Head, Adj, Next, MNum, Cnt);
    }
    
    std::cout << "MNumeration: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << MNum[i] << ' ';
    }

    for (int i = 1; i <= n; i++)
    {
        Color[i] = Colors::WHITE;
    }
    Cnt = n;
    int* NNum = new int[n];
    for (int i = 1; i <= n; i++)
    {
        NNumDFS(i, Color, Head, Adj, Next, NNum, Cnt);
    }
    std::cout << "\nNNumeration: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << NNum[i] << ' ';
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
