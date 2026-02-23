#include <string>
#include <utility>

class UniquePtr
{
private:
    std::string* m_pointer;

public:
    UniquePtr(std::string* ptr = nullptr) : m_pointer(ptr) {}
    UniquePtr(const UniquePtr& up) = delete;
    UniquePtr(UniquePtr&& up) noexcept : m_pointer(up.m_pointer) { up.m_pointer = nullptr; }
    ~UniquePtr() { delete m_pointer; }

    UniquePtr& operator=(const UniquePtr& up) = delete;
    UniquePtr& operator=(UniquePtr&& up) noexcept;
    std::string& operator*() const { return *m_pointer; }
    std::string* operator->() const { return Get(); }
    operator bool() const { return m_pointer; }

    std::string* Get() const { return m_pointer; }
    std::string* Release();
    void Reset(std::string* ptr = nullptr) { delete m_pointer; m_pointer = ptr; }
    void Swap(UniquePtr& up) { std::swap(m_pointer, up.m_pointer); }
};

UniquePtr& UniquePtr::operator=(UniquePtr&& up) noexcept
{
    if (this == &up)
        return *this;

    delete m_pointer;

    m_pointer = up.m_pointer;
    up.m_pointer = nullptr;

    return *this;
}

std::string* UniquePtr::Release()
{
    std::string* ptr = m_pointer;
    m_pointer = nullptr;
    return ptr;
}

UniquePtr MakeUnique(const std::string& str)
{
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str)
{
    return UniquePtr(new std::string(std::move(str)));
}

void Swap(UniquePtr& lhs, UniquePtr& rhs)
{
    lhs.Swap(rhs);
}