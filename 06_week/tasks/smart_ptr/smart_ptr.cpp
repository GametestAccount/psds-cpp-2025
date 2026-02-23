#include <string>
#include <utility>

class SharedPtr
{
private:
    friend class WeakPtr;

    struct SharedData
    {
        std::string* pointer;
        size_t ref_count;
        size_t weak_ref_count;
    };

    static SharedData* CreateSD(std::string* ptr) { return (!ptr) ? nullptr : new SharedData{ptr, 1, 0}; }
    static void TryToDeleteSD(SharedData* sd);

    SharedData* m_sd;

public:
    SharedPtr(std::string* ptr = nullptr) : m_sd(CreateSD(ptr)) {}
    SharedPtr(const SharedPtr& sp);
    SharedPtr(SharedPtr&& sp) noexcept : m_sd(sp.m_sd) { sp.m_sd = nullptr; }
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& sp);
    SharedPtr& operator=(SharedPtr&& sp) noexcept;
    std::string& operator*() const { return *(m_sd->pointer); }
    std::string* operator->() const { return Get(); }
    operator bool() const { return (m_sd) ? static_cast<bool>(m_sd->pointer) : false; }

    std::string* Get() const { return (m_sd) ? m_sd->pointer : nullptr; }
    void Reset(std::string* ptr = nullptr);
    void Swap(SharedPtr& sp) { std::swap(m_sd, sp.m_sd); }
    size_t UseCount() const { return (m_sd) ? m_sd->ref_count : 0; }
};

void SharedPtr::TryToDeleteSD(SharedPtr::SharedData* sd)
{
    if (sd->ref_count == 0)
    {
        delete sd->pointer;
        sd->pointer = nullptr;

        if (sd->weak_ref_count == 0)
            delete sd;
    }
}

SharedPtr::SharedPtr(const SharedPtr& sp) : m_sd(sp.m_sd)
{
    if (m_sd)
        ++m_sd->ref_count;
}

SharedPtr::~SharedPtr()
{
    if (m_sd)
    {
        --m_sd->ref_count;
        TryToDeleteSD(m_sd);
    }
}

SharedPtr& SharedPtr::operator=(const SharedPtr& sp)
{
    if (this == &sp)
        return *this;

    if (m_sd)
    {
        --m_sd->ref_count;
        TryToDeleteSD(m_sd);
    }

    m_sd = sp.m_sd;
    if (m_sd)
        ++m_sd->ref_count;

    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& sp) noexcept
{
    if (this == &sp)
        return *this;

    if (m_sd)
    {
        --m_sd->ref_count;
        TryToDeleteSD(m_sd);
    }

    m_sd = sp.m_sd;
    sp.m_sd = nullptr;

    return *this;
}

void SharedPtr::Reset(std::string* ptr)
{
    if (m_sd)
    {
        --m_sd->ref_count;
        TryToDeleteSD(m_sd);
    }

    m_sd = CreateSD(ptr);
}

class WeakPtr
{
private:
    SharedPtr::SharedData* m_sd;

public:
    WeakPtr() : m_sd(nullptr) {}
    WeakPtr(const SharedPtr& sp);
    WeakPtr(const WeakPtr &wp);
    WeakPtr(WeakPtr&& wp) noexcept : m_sd(wp.m_sd) { wp.m_sd = nullptr; }
    ~WeakPtr();

    WeakPtr& operator=(const WeakPtr& wp);
    WeakPtr& operator=(WeakPtr&& wp) noexcept;

    void Reset();
    void Swap(WeakPtr& wp) { std::swap(m_sd, wp.m_sd); }
    size_t UseCount() const { return (m_sd) ? m_sd->ref_count : 0; }
    bool Expired() const { return (m_sd) ? !m_sd->pointer : true; }
    SharedPtr Lock() const;
};

WeakPtr::WeakPtr(const SharedPtr& sp) : m_sd(sp.m_sd)
{
    if (m_sd)
        ++m_sd->weak_ref_count;
}

WeakPtr::WeakPtr(const WeakPtr &wp) : m_sd(wp.m_sd)
{
    if (m_sd)
        ++m_sd->weak_ref_count;
}

WeakPtr::~WeakPtr()
{
    if (m_sd)
    {
        --m_sd->weak_ref_count;
        SharedPtr::TryToDeleteSD(m_sd);
    }
}

WeakPtr& WeakPtr::operator=(const WeakPtr& wp)
{
    if (this == &wp)
        return *this;

    if (m_sd)
    {
        --m_sd->weak_ref_count;
        SharedPtr::TryToDeleteSD(m_sd);
    }

    m_sd = wp.m_sd;
    if (m_sd)
        ++m_sd->weak_ref_count;

    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& wp) noexcept
{
    if (this == &wp)
        return *this;

    if (m_sd)
    {
        --m_sd->weak_ref_count;
        SharedPtr::TryToDeleteSD(m_sd);
    }
    
    m_sd = wp.m_sd;
    wp.m_sd = nullptr;

    return *this;
}

void WeakPtr::Reset()
{
    if (m_sd)
        --m_sd->weak_ref_count;

    m_sd = nullptr;
}

SharedPtr WeakPtr::Lock() const
{
    SharedPtr sp;

    if (m_sd)
    {
        if (m_sd->pointer)
        {
            sp.m_sd = m_sd;
            ++sp.m_sd->ref_count;
        }
    }

    return sp;
}

SharedPtr MakeShared(const std::string& str)
{
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str)
{
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& lhs, SharedPtr& rhs)
{
    lhs.Swap(rhs);
}

void Swap(WeakPtr& lhs, WeakPtr& rhs)
{
    lhs.Swap(rhs);
}