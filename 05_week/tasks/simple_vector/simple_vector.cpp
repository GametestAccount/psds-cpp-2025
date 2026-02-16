#include <algorithm>
#include <initializer_list>

class SimpleVector
{
private:
    size_t m_size;
    size_t m_capacity;
    int* m_array;

public:
    SimpleVector() : m_size(0), m_capacity(0), m_array(nullptr) {}
    SimpleVector(size_t size, int value);
    SimpleVector(size_t size) : SimpleVector(size, 0) {}
    SimpleVector(std::initializer_list<int> il);
    SimpleVector(const SimpleVector& vec);
    SimpleVector(SimpleVector&& vec) noexcept;
    ~SimpleVector() { delete[] m_array; }

    SimpleVector& operator=(const SimpleVector& vec);
    SimpleVector& operator=(SimpleVector&& vec) noexcept;
    bool operator==(const SimpleVector& vec) const;
    bool operator!=(const SimpleVector& vec) const { return !(*this == vec); }

    size_t Size() const{ return m_size; }
    size_t Capacity() const { return m_capacity; }
    bool Empty() const { return !Size(); }

    const int* Data() const { return m_array; }
    const int& operator[](size_t n) const { return m_array[n]; }
    int& operator[](size_t n) { return const_cast<int&>(const_cast<const SimpleVector*>(this)->operator[](n)); }

    const int* begin() const { return m_array; }
    const int* end() const { return m_array + m_size; }
    int* begin() { return const_cast<int*>(const_cast<const SimpleVector*>(this)->begin()); }
    int* end() { return const_cast<int*>(const_cast<const SimpleVector*>(this)->end()); }

    void Clear() { m_size = 0; }
    void Swap(SimpleVector& vec);
    void Reserve(size_t capacity);
    void Resize(size_t size, int value = 0);

    void PushBack(int value);
    void PopBack();
    int* Insert(const int* pos, int value);
    int* Insert(size_t pos, int value) { return Insert(begin() + pos, value); }
    int* Erase(const int* pos);
    int* Erase(size_t pos) { return Erase(begin() + pos); }
};

SimpleVector::SimpleVector(size_t size, int value) : m_size(size), m_capacity(size), m_array(new int[size])
{
    std::fill(begin(), end(), value);
}

SimpleVector::SimpleVector(std::initializer_list<int> il) : m_size(il.size()), m_capacity(il.size()), m_array(new int[il.size()])
{
    std::copy(il.begin(), il.end(), begin());
}

SimpleVector::SimpleVector(const SimpleVector& vec) : m_size(vec.m_size), m_capacity(vec.m_size), m_array(new int[vec.m_size])
{
    std::copy(vec.begin(), vec.end(), begin());
}

SimpleVector::SimpleVector(SimpleVector&& vec) noexcept : m_size(vec.m_size), m_capacity(vec.m_capacity), m_array(vec.m_array)
{
    vec.m_size = 0;
    vec.m_capacity = 0;
    vec.m_array = nullptr;
}

SimpleVector& SimpleVector::operator=(const SimpleVector& vec)
{
    if (this == &vec)
        return *this;
        
    delete[] m_array;

    m_size = vec.m_size;
    m_capacity = m_size;
    m_array = new int[m_capacity];

    std::copy(vec.begin(), vec.end(), begin());

    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& vec) noexcept
{
    if (this == &vec)
        return *this;

    delete[] m_array;

    m_size = vec.m_size;
    m_capacity = vec.m_capacity;
    m_array = vec.m_array;

    vec.m_size = 0;
    vec.m_capacity = 0;
    vec.m_array = nullptr;

    return *this;
}

bool SimpleVector::operator==(const SimpleVector& vec) const
{
    if (m_size != vec.m_size)
        return false;

    return std::equal(begin(), end(), vec.begin(), vec.end());
}

void SimpleVector::Swap(SimpleVector& vec)
{
    std::swap(m_size, vec.m_size);
    std::swap(m_capacity, vec.m_capacity);
    std::swap(m_array, vec.m_array);
}

void SimpleVector::Reserve(size_t capacity)
{
    if (m_capacity >= capacity)
        return;

    int* array = new int[capacity];
    std::copy(begin(), end(), array);
    delete[] m_array;

    m_capacity = capacity;
    m_array = array;
}

void SimpleVector::Resize(size_t size, int value)
{
    if (m_size == size)
        return;

    if (m_size < size)
    {
        Reserve(size);
        std::fill(m_array + m_size, m_array + size, value);
    }

    m_size = size;
}

void SimpleVector::PushBack(int value)
{
    if (!m_capacity)
        Reserve(1);
    else if (m_capacity == m_size)
        Reserve(m_capacity * 2);

    m_array[m_size++] = value;
}

void SimpleVector::PopBack()
{
    if (!Empty())
        --m_size;
}

int* SimpleVector::Insert(const int* pos, int value)
{
    if ((pos < begin()) || (pos > end()))
        return end();
        
    ptrdiff_t offset = pos - m_array;

    Reserve(m_size + 1);
    ++m_size;
    std::shift_right(m_array + offset, m_array + m_size, 1);
    m_array[offset] = value;

    return m_array + offset;
}

int* SimpleVector::Erase(const int* pos)
{
    if ((pos < begin()) || (pos > end()))
        return end();

    ptrdiff_t offset = pos - m_array;

    std::shift_left(m_array + offset, m_array + m_size, 1);
    --m_size;
        
    return m_array + offset;
}

void swap(SimpleVector& lhs, SimpleVector& rhs)
{
    lhs.Swap(rhs);
}