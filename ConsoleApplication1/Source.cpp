#include "source.h"

void fillDB()
{
    int number;
    cout << "Enter number of source --> ";
    cin >> number;
    Source tmp;
    for (size_t i = 0; i < number; i++)
    {
        editSource(tmp);
        saveSource(tmp);
    }
}

void editSource(Source& source)
{
    cout << "\n\t Enter type source ([1] - BOOK; [2] - NEWSPAPER; [3] - MAGAZINE) --> ";
    int tmp;
    cin >> tmp;
    source.type = (Type)tmp;
    cout << "\t Enter year -- > "; cin >> source.year;

    cin.ignore();
    cout << "\t Enter name -- > "; cin.getline(source.name, SIZE);

    if (source.type == Type::BOOK)
    {
        cout << "\t Enter genre -- > "; cin.getline(source.genre, SIZE);
        cout << "\t Enter author -- > "; cin.getline(source.author, SIZE);
    }
}

void saveSource(Source source, string fname)
{
    ofstream file(fname, ios_base::app | ios_base::binary);
    if (!file.is_open())
    {
        cout << "Error" << endl;
        return;
    }

    file.write((char*)&source, sizeof(Source));
    file.close();
}

void printSource(Source source)
{
    cout << "\n\t=================================== " << (source.type == Type::BOOK ? "BOOK" : (source.type == Type::MAGAZINE ? "MAGAZINE" : "NEWSPAPER")) << "===================================" << endl;
    cout << "\t\t Name   :: " << source.name << endl;
    if (source.type == Type::BOOK) {
        cout << "\t\t Author :: " << source.author << endl;
        cout << "\t\t Genre  :: " << source.genre << endl;
    }
    cout << "\t\t Year   :: " << source.year << endl;
}

void printAllSource(Source* arr, const size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printSource(arr[i]);
    }
}

Source* readAll(int& size, string fname)
{
    ifstream file(fname);
    if (!file.is_open()) {
        cout << "Error" << endl;
        return nullptr;
    }
    file.seekg(0, ios_base::end);
    if (file.tellg() == 0)
        return nullptr;

    size = file.tellg() / sizeof(Source);
    file.seekg(0);

    Source* tmp = new Source[size];
    for (size_t i = 0; i < size; i++)
    {
        file.read((char*)&tmp[i], sizeof(Source));
    }
    file.close();
    return tmp;
}

void deleteSource(Source*& sources, int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index!" << endl;
        return;
    }
    Source* newSources = new Source[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            newSources[j++] = sources[i];
        }
    }
    delete[] sources;
    sources = newSources;
    size--;
    cout << "Source deleted successfully." << endl;
}

void sortSources(Source* arr, const size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = 0; j < length - i - 1; j++) {
            if (arr[j].type > arr[j + 1].type ||
                (arr[j].type == arr[j + 1].type && strcmp(arr[j].name, arr[j + 1].name) > 0)) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << "Sources sorted successfully." << endl;
}

void searchSource(Source* arr, const size_t length) {
    char name[SIZE];
    char author[SIZE];
    cout << "Enter the name of the source: ";
    cin.ignore();
    cin.getline(name, SIZE);
    cout << "Enter the author of the source: ";
    cin.getline(author, SIZE);

    bool found = false;
    for (size_t i = 0; i < length; i++) {
        if (strcmp(arr[i].name, name) == 0 && strcmp(arr[i].author, author) == 0) {
            printSource(arr[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "No matching source found." << endl;
    }
}

void filterSources(Source* arr, const size_t length) {
    int year;
    cout << "Enter the year to filter: ";
    cin >> year;

    for (size_t i = 0; i < length; i++) {
        if (arr[i].year == year) {
            printSource(arr[i]);
        }
    }
}

void countBooksByCategory(Source* arr, const size_t length) {
    char category[SIZE];
    cout << "Enter the category to count: ";
    cin.ignore();
    cin.getline(category, SIZE);

    int count = 0;
    for (size_t i = 0; i < length; i++) {
        if (arr[i].type == Type::BOOK && strcmp(arr[i].genre, category) == 0) {
            count++;
        }
    }
    cout << "Number of books in category '" << category << "': " << count << endl;
}

void removeNewspapersByYear(Source*& sources, int& size) {
    int year;
    cout << "Enter the year to remove newspapers: ";
    cin >> year;

    Source* newSources = new Source[size];
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        if (!(sources[i].type == Type::NEWSPAPER && sources[i].year == year)) {
            newSources[newSize++] = sources[i];
        }
    }

    delete[] sources;
    sources = newSources;
    size = newSize;

    cout << "Newspapers from year " << year << " removed." << endl;
}
