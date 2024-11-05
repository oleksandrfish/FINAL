#include <iostream>
#include "source.h"
using namespace std;

int main()
{
    int size = 0;
    Source* sources;

    int choice;
    while (true)
    {
        cout << "\t [1] - fill db; \n\t [2] - print db; \n\t [3] - add source; \n\t [4] - delete source; \n\t [5] - sort sources; \n\t [6] - search source; \n\t [7] - filter sources; \n\t [8] - count books by category; \n\t [9] - remove newspapers by year; \n\t [0] - exit; \n\t\t Enter :: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            fillDB();
            break;
        case 2: {
            sources = readAll(size);
            if (sources == nullptr) {
                cout << "File not found !!! " << endl;
            }
            printAllSource(sources, size);
            break;
        }
        case 3: {
            Source tmp;
            editSource(tmp);
            saveSource(tmp);
            break;
        }
        case 4: {
            int index;
            cout << "Enter index of the source to delete (0 to " << size - 1 << "): ";
            cin >> index;
            if (sources != nullptr) {
                deleteSource(sources, size, index);
            }
            break;
        }
        case 5: {
            if (sources != nullptr) {
                sortSources(sources, size);
            }
            break;
        }
        case 6: {
            if (sources != nullptr) {
                searchSource(sources, size);
            }
            break;
        }
        case 7: {
            if (sources != nullptr) {
                filterSources(sources, size);
            }
            break;
        }
        case 8: {
            if (sources != nullptr) {
                countBooksByCategory(sources, size);
            }
            break;
        }
        case 9: {
            if (sources != nullptr) {
                removeNewspapersByYear(sources, size);
            }
            break;
        }
        }
        if (choice == 0) break;
    }
    delete[] sources;
}
