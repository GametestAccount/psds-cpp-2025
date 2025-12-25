#include <vector>
#include <initializer_list>
#include <algorithm>

class RingBuffer {
public:
    RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int fill);
    RingBuffer(std::initializer_list<int> il);

    void Push(int element);
    bool TryPush(int element);
    void Pop();
    bool TryPop(int& element);
    int& Front();
    int& Back();
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(size_t new_capacity);
    std::vector<int> Vector() const;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

private:
    std::vector<int> m_data;
    size_t m_start_index;
    size_t m_end_index;
    size_t m_current_count;
};

RingBuffer::RingBuffer(size_t capacity) {
    if (!capacity) {
        capacity = 1;
    }

    m_data.resize(capacity);
    m_start_index = 0;
    m_end_index = 0;
    m_current_count = 0;
}

RingBuffer::RingBuffer(size_t capacity, int fill) : RingBuffer(capacity) {
    std::fill(m_data.begin(), m_data.end(), fill);
    m_end_index = m_data.size() - 1;
    m_current_count = m_data.size();
}

RingBuffer::RingBuffer(std::initializer_list<int> il) : RingBuffer(il.size()) {
    std::copy(il.begin(), il.end(), m_data.begin());
    m_end_index = il.size() - 1;
    m_current_count = il.size();
}

void RingBuffer::Push(int element) {
    if (!Empty()) {
        m_end_index = (m_end_index + 1) % Capacity();

        if (m_end_index == m_start_index) {
            m_start_index = (m_start_index + 1) % Capacity();
        }
    }

    m_data[m_end_index] = element;

    if (!Full()) {
        ++m_current_count;
    }
}

bool RingBuffer::TryPush(int element) {
    if (!Full()) {
        Push(element);
        return true;
    }

    return false;
}

void RingBuffer::Pop() {
    if (!Empty()) {
        m_start_index = (m_start_index + 1) % Capacity();
        --m_current_count;
    }
}

bool RingBuffer::TryPop(int& element) {
    if (!Empty()) {
        element = m_data[m_start_index];
        Pop();
        return true;
    }

    return false;
}

int& RingBuffer::operator[](size_t index) {
    return m_data[(m_start_index + index) % Capacity()];
}

const int& RingBuffer::operator[](size_t index) const {
    return (const_cast<RingBuffer*>(this))->operator[](index);
}

int& RingBuffer::Front() {
    return m_data[m_end_index];
}

int& RingBuffer::Back() {
    return m_data[m_start_index];
}

bool RingBuffer::Empty() const {
    return Size() == 0;
}

bool RingBuffer::Full() const {
    return Size() == Capacity();
}

size_t RingBuffer::Size() const {
    return m_current_count;
}

size_t RingBuffer::Capacity() const {
    return m_data.size();
}

void RingBuffer::Clear() {
    m_start_index = m_end_index = m_current_count = 0;
}

void RingBuffer::Resize(size_t new_capacity) {
    if (!new_capacity) {
        new_capacity = 1;
    }

    std::vector<int> vec(new_capacity);

    if (new_capacity >= Size()) {
        for (size_t i = 0; i < Size(); ++i) {
            vec[i] = m_data[(m_start_index + i) % Capacity()];
        }

        m_end_index = Size() - 1;
    }
    else {
        size_t skip = Size() - new_capacity;

        for (size_t i = 0; i < Size(); ++i) {
            vec[i] = m_data[(m_start_index + i + skip) % Capacity()];
        }

        m_end_index = new_capacity - 1;
        m_current_count = new_capacity;
    }

    m_start_index = 0;
    m_data = vec;
}

std::vector<int> RingBuffer::Vector() const
{
    std::vector<int> vec(m_current_count);

    for (size_t i = 0; i < Size(); ++i) {
        vec[i] = m_data[(m_start_index + i) % Capacity()];
    }

    return vec;
}