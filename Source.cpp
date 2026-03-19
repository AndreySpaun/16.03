#include <iostream>
using namespace std;

class String
{
    char* ptr;
    int length;



public:

    bool Contains(const char* substring) const;
    int Count(const char* substring) const;
    void Insert(int position, const char* substring);

    const char* GetData() const
    {
        return ptr;
    }

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
        length = 0;
        Append(string.GetData());
    }

    String(const char* ptr)
    {
        length = 0;
        Append(ptr);
    }

    String(const char* ptr, const int length)
    {
        this->length = 0;
        Append(ptr, length);
    }

    ~String()
    {
        delete[] ptr;
    }

    void Print() const
    {
        cout << ptr << endl;
    }

    void Append(const String& string, int length = -1)
    {
        Append(string.GetData(), length);
    }

    void Append(const char* ptr, int length = -1)
    {
        if (length < 0)
        {
            length = 0;

            while (ptr[length] != '\0')
            {
                length++;
            }
        }

        const int new_length = this->length + length;
        char* new_ptr = new char[new_length + 1];

        for (int i = 0; i < this->length; i++)
        {
            new_ptr[i] = this->ptr[i];
        }

        for (int i = 0; i < length; i++)
        {
            new_ptr[i + this->length] = ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] this->ptr;
        this->ptr = new_ptr;
        this->length = new_length;
    }

    void Remove(const char* old_substring, const char* new_substring)
    {
        int old_substring_length = 0;
        int new_substring_length = 0;

        while (old_substring[old_substring_length] != '\0')
        {
            old_substring_length++;
        }

        while (new_substring[new_substring_length] != '\0')
        {
            new_substring_length++;
        }

        int pos = -1;

        for (int i = 0; i < length - old_substring_length + 1; i++)
        {
            bool match = true;

            for (int j = 0; j < old_substring_length; j++)
            {
                if (ptr[i + j] != old_substring[j])
                {
                    match = false;

                    break;
                }
            }

            if (match)
            {
                pos = i;
                break;
            }
        }

        if (pos == -1) return;

        int new_length = length - old_substring_length + new_substring_length;
        char* new_ptr = new char[new_length + 1];

        for (int i = 0; i < pos; i++)
        {
            new_ptr[i] = ptr[i];
        }

        for (int i = 0; i < new_substring_length; i++)
        {
            new_ptr[i + pos] = new_substring[i];
        }

        for (int i = pos + old_substring_length; i < length; i++)
        {
            new_ptr[i - old_substring_length + new_substring_length] = ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] ptr;
        ptr = new_ptr;
        length = new_length;
    }

    void Clear()
    {
        delete[] ptr;

        length = 0;
        ptr = new char('\0');
    }

    bool Contains(const char* substring) const
    {
        int sub_len = 0;
        while (substring[sub_len] != '\0') sub_len++;

        for (int i = 0; i <= length - sub_len; i++)
        {
            bool match = true;

            for (int j = 0; j < sub_len; j++)
            {
                if (ptr[i + j] != substring[j])
                {
                    match = false;
                    break;
                }
            }

            if (match) return true;
        }

        return false;
    }

    int Count(const char* substring) const
    {
        int sub_len = 0;
        while (substring[sub_len] != '\0') sub_len++;

        int count = 0;

        for (int i = 0; i <= length - sub_len; i++)
        {
            bool match = true;

            for (int j = 0; j < sub_len; j++)
            {
                if (ptr[i + j] != substring[j])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                count++;
                i += sub_len - 1; // чтобы не пересекались
            }
        }

        return count;
    }

    void Insert(int position, const char* substring)
    {
        if (position < 0 || position > length) return;

        int sub_len = 0;
        while (substring[sub_len] != '\0') sub_len++;

        int new_length = length + sub_len;
        char* new_ptr = new char[new_length + 1];

        // до позиции
        for (int i = 0; i < position; i++)
        {
            new_ptr[i] = ptr[i];
        }

        // вставка
        for (int i = 0; i < sub_len; i++)
        {
            new_ptr[position + i] = substring[i];
        }

        // остаток строки
        for (int i = position; i < length; i++)
        {
            new_ptr[i + sub_len] = ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] ptr;
        ptr = new_ptr;
        length = new_length;
    }
};

int main()
{
    String string1("Test TEXT Asd TEXT Asd");
    string1.Print(); // Test TEXT Asd TEXT Asd

    string1.Remove("TEXT", "text123");
    string1.Print(); // Test text123 Asd TEXT Asd

    // Треба: Test text123 Asd text123 Asd

    cout << string1.Contains("TEXT") << endl;
    cout << string1.Count("TEXT") << endl;

    string1.Insert(5, "INSERT ");
    string1.Print();    

    return 0;
}
