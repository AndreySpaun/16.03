#include <iostream>
using namespace std;

class String
{
    char* ptr;
    int length;

public:
    int GetLength() const
    {
        return length;
    }

    String()
    {
        length = 0;
        ptr = new char('\0');
    }

    String(const String& string)
    {
        this->length = string.GetLength();

        this->ptr = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->ptr[i] = string.ptr[i];
        }

        this->ptr[length] = '\0';
    }

    String(char* ptr)
    {
        length = 0;

        while (ptr[length] != '\0')
        {
            length++;
        }

        this->ptr = new char[length + 1];

        for (int i = 0; i < length; i++) {
            this->ptr[i] = ptr[i];
        }

        this->ptr[length] = '\0';
    }

    String(char* ptr, int length)
    {
        this->length = length;

        this->ptr = new char[length + 1];

        for (int i = 0; i < length; i++) {
            this->ptr[i] = ptr[i];
        }

        this->ptr[length] = '\0';
    }

    ~String()
    {
        delete[] ptr;
    }

    void Print() const
    {
        cout << ptr << endl;
    }

    void Append(const String& string)
    {
        int new_length = string.GetLength() + length;
        char* new_ptr = new char[new_length + 1];

        for (int i = 0; i < length; i++)
        {
            new_ptr[i] = string.ptr[i];
        }

        for (int i = 0; i < string.GetLength(); i++)
        {
            new_ptr[i + length] = new_ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] ptr;
        ptr = new_ptr;
        length = new_length;
    }

    void Append(const char* ptr)
    {
        int ptr_length = 0;

        while (ptr[ptr_length] != '\0')
        {
            ptr_length++;
        }

        int new_length = ptr_length + length;
        char* new_ptr = new char[new_length + 1];

        for (int i = 0; i < length; i++)
        {
            new_ptr[i] = this->ptr[i];
        }

        for (int i = 0; i < ptr_length; i++)
        {
            new_ptr[i + length] = ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] this->ptr;
        this->ptr = new_ptr;
        length = new_length;
    }

    void Clear()
    {
        delete[] ptr;

        length = 0;
        ptr = new char('\0');
    }
};

int main()
{
    String string;

    int length = 8;

    const char* ptr = "My text1";
    char ptr2[] = "My text2";

    String var1(ptr, length);
    String var2(ptr2);

    var1.Print();
    var2.Print();

    String var3(var2);
    var3.Print();

    var1.Append(var2);
    var1.Print();

    var2.Append(" | Test");
    var2.Print();

    string.Print();
    string.Append("Firs string");
    string.Print();

    var1.Print();
    var1.Clear();
    var1.Print();

    cout << "--------";

    return 0;
}