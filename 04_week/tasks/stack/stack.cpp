#include <vector>
#include <algorithm>

class Stack {
public:
    Stack() {}

    void Push(int element);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

private:
    std::vector<int> m_data;
};

void Stack::Push(int element) {
    m_data.push_back(element);
}

bool Stack::Pop() {
    if (m_data.empty()) {
        return false;
    }

    m_data.pop_back();
    
    return true;
}

int& Stack::Top() {
    return m_data.back();
}

const int& Stack::Top() const {
    return (const_cast<Stack*>(this))->Top();
}

bool Stack::Empty() const {
    return m_data.empty();
}

size_t Stack::Size() const {
    return m_data.size();
}

void Stack::Clear() {
    m_data.clear();
}

void Stack::Swap(Stack& other) {
    std::swap(m_data, other.m_data);
}

bool Stack::operator==(const Stack& other) const {
    return this->m_data == other.m_data;
}

bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}