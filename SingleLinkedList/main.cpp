#include <algorithm>
#include <iostream>
#include "SingleLinkedList.h"

using namespace std;

int main()
{
    //auto list = SingleLinkedList<int>();
    //list.Add(1);
    //list.Add(2);
    //list.Add(3);

    const SingleLinkedList<int> list = { 1, 2, 3 };

    cout << list << endl;

    cout << endl << "for_each:" << endl;
    for_each(list.cbegin(), list.cend(), [](const int item) { cout << item << endl; });

    cout << endl << "iterator:" << endl;
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
};
