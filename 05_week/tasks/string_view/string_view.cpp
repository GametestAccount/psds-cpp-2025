#include <cstring>
#include <string>
#include <algorithm>

class StringView
{
private:
    const char* m_data;
    size_t m_length;

public:
    static constexpr size_t npos = std::string::npos;

    StringView() : m_data(nullptr), m_length(0) {}
    StringView(const std::string& str, size_t pos = 0, size_t n = npos);
    StringView(const char* c_str) : m_data(c_str), m_length((c_str) ? std::strlen(c_str) : 0) {}
    StringView(const char* c_str, size_t length);

    size_t Size() const { return m_length; }
    size_t Length() const { return Size(); }
    bool Empty() const { return !Size(); }

    char Front() const { return m_data[0]; }
    char Back() const { return m_data[m_length - 1]; }
    const char* Data() const { return m_data; }
    char operator[](size_t n) const { return m_data[n]; }

    void RemovePrefix(size_t n);
    void RemoveSuffix(size_t n);

    StringView Substr(size_t pos, size_t n = npos) const;
    size_t Find(char ch, size_t pos = 0) const;
    size_t Find(const StringView& view, size_t pos = 0) const;

    std::string ToString() const { return std::string(m_data, m_length); }
};

StringView::StringView(const std::string& str, size_t pos, size_t n) : StringView()
{
    if (pos >= str.length())
        return;

    m_data = str.data() + pos;
    m_length = std::min(str.length() - pos, n);
}

StringView::StringView(const char* c_str, size_t length) : StringView()
{
    if (!c_str || !length)
        return;
    
    m_data = c_str;
    m_length = length;
}

void StringView::RemovePrefix(size_t n)
{
    if (n < m_length)
    {
        m_data += n;
        m_length -= n;
    }
    else
    {
        m_data = nullptr;
        m_length = 0;
    }
}

void StringView::RemoveSuffix(size_t n)
{
    if (n < m_length)
    {
        m_length -= n;
    }
    else
    {
        m_data = nullptr;
        m_length = 0;
    }
}

StringView StringView::Substr(size_t pos, size_t n) const
{
    if (pos >= m_length)
        return StringView();

    return StringView(m_data + pos, std::min(m_length - pos, n));
}

size_t StringView::Find(char ch, size_t pos) const
{
    if (pos >= m_length)
        return npos;
    
    for (size_t i = pos; i <= m_length; ++i)
        if (m_data[i] == ch)
            return i;

    return npos;
}

size_t StringView::Find(const StringView& view, size_t pos) const
{
    if (view.Empty())
        return 0;

    if (pos >= m_length)
        return npos;

    const char* it = std::search(m_data + pos, m_data + m_length, view.m_data, view.m_data + view.m_length);

    if (it != (m_data + m_length))
        return it - m_data;

    return npos;
}