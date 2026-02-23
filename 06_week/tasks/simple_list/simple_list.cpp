#include <string>
#include <utility>

class SimpleList
{
private:
    struct Node
    {
        std::string data;
        Node* prev;
        Node* next;
    };

    Node* CopyNodes(const Node* origin) const;
    void DeleteNodes(Node* root) const;
    Node* RewindToBack(Node* root) const;

    Node* m_root;
    size_t m_size;

public:
    SimpleList() : m_root(nullptr), m_size(0) {}
    SimpleList(const SimpleList& list) : m_root(CopyNodes(list.m_root)), m_size(list.m_size) {}
    SimpleList(SimpleList&& list) noexcept : m_root(list.m_root), m_size(list.m_size) { list.m_root = nullptr; list.m_size = 0; }
    ~SimpleList() { DeleteNodes(m_root); }

    SimpleList& operator=(const SimpleList& list);
    SimpleList& operator=(SimpleList&& list) noexcept;

    size_t Size() const { return m_size; }
    bool Empty() const { return !Size(); }
    void Swap(SimpleList& list) { std::swap(m_root, list.m_root); std::swap(m_size, list.m_size); }
    void PushFront(const std::string& element) { m_root = new Node{element, nullptr, m_root}; ++m_size; }
    void PushFront(std::string&& element)  { m_root = new Node{std::move(element), nullptr, m_root}; ++m_size; }
    void PushBack(const std::string& element);
    void PushBack(std::string&& element);
    void PopFront();
    void PopBack();
    std::string& Front() { return const_cast<std::string&>(const_cast<const SimpleList*>(this)->Front()); }
    const std::string& Front() const { return m_root->data; }
    std::string& Back() { return const_cast<std::string&>(const_cast<const SimpleList*>(this)->Back()); }
    const std::string& Back() const { return RewindToBack(m_root)->data; }
    void Clear();
};

SimpleList::Node* SimpleList::CopyNodes(const SimpleList::Node* origin) const
{
    if (!origin)
        return nullptr;

    Node* root = new Node{origin->data, nullptr, nullptr};

    for (Node *it = origin->next, *it_root = root; it != nullptr; it = it->next)
    {
        it_root->next = new Node{it->data, it_root, nullptr};
        it_root = it_root->next;
    }

    return root;
}

void SimpleList::DeleteNodes(SimpleList::Node* root) const
{
    Node* it = root;

    while (it != nullptr)
    {
        Node* curr = it;
        it = it->next;
        delete curr;
    }
}

SimpleList::Node* SimpleList::RewindToBack(SimpleList::Node* root) const
{
    if (!root)
        return nullptr;

    Node* it = root;

    while (it->next != nullptr)
        it = it->next;

    return it;
}

SimpleList& SimpleList::operator=(const SimpleList& list)
{
    if (this == &list)
        return *this;

    DeleteNodes(m_root);

    m_root = CopyNodes(list.m_root);
    m_size = list.m_size;

    return *this;
}

SimpleList& SimpleList::operator=(SimpleList&& list) noexcept
{
    if (this == &list)
        return *this;

    DeleteNodes(m_root);

    m_root = list.m_root;
    m_size = list.m_size;
    list.m_root = nullptr;
    list.m_size = 0;

    return *this;
}

void SimpleList::PushBack(const std::string& element)
{
    Node* back = RewindToBack(m_root);

    if (back)
        back->next = new Node{element, back, nullptr};
    else
        m_root = new Node{element, nullptr, nullptr};

    ++m_size;
}

void SimpleList::PushBack(std::string&& element)
{
    Node* back = RewindToBack(m_root);

    if (back)
        back->next = new Node{std::move(element), back, nullptr};
    else
        m_root = new Node{std::move(element), nullptr, nullptr};

    ++m_size;
}

void SimpleList::PopFront()
{
    if (!m_root)
        return;

    Node* front = m_root;
    m_root = m_root->next;
    delete front;

    --m_size;
}

void SimpleList::PopBack()
{
    if (!m_root)
        return;

    Node* back = RewindToBack(m_root);

    if (back->prev)
    {
        back->prev->next = nullptr;
        delete back;
    }
    else
    {
        delete m_root;
        m_root = nullptr;
    }

    --m_size;
}

void SimpleList::Clear()
{
    DeleteNodes(m_root);
    m_root = nullptr;
    m_size = 0;
}

void Swap(SimpleList& lhs, SimpleList& rhs)
{
    lhs.Swap(rhs);
}