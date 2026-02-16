#include <string>
#include <format>
#include <utility>

class Tracer
{
private:
    int m_id;
    std::string m_name;

public:
    static inline size_t count = 0;
    static inline size_t default_ctor = 0;
    static inline size_t str_ctor = 0;
    static inline size_t copy_ctor = 0;
    static inline size_t move_ctor = 0;
    static inline size_t copy_assign = 0;
    static inline size_t move_assign = 0;
    static inline size_t dtor = 0;
    static inline size_t alive = 0;

    static void ResetStats();

    Tracer();
    Tracer(const std::string& name);
    Tracer(const Tracer& tracer);
    Tracer(Tracer&& tracer) noexcept;
    ~Tracer();

    Tracer& operator=(const Tracer& tracer);
    Tracer& operator=(Tracer&& tracer) noexcept;

    int Id() const { return m_id; }
    const std::string& Name() const { return m_name; }
    char* Data() { return m_name.data(); }
};

void Tracer::ResetStats()
{
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
}

Tracer::Tracer()
{
    m_id = ++count;
    m_name = std::format("obj_{}", m_id);
    ++default_ctor;
    ++alive;
}

Tracer::Tracer(const std::string& name)
{
    m_id = ++count;
    m_name = std::format("{}_{}", name, m_id);
    ++str_ctor;
    ++alive;
}

Tracer::Tracer(const Tracer& tracer)
{
    m_id = ++count;
    m_name = tracer.m_name;
    ++copy_ctor;
    ++alive;
}

Tracer::Tracer(Tracer&& tracer) noexcept
{
    m_id = ++count;
    m_name = std::move(tracer.m_name);
    ++move_ctor;
    ++alive;
}

Tracer::~Tracer()
{
    ++dtor;
    --alive;
}

Tracer& Tracer::operator=(const Tracer& tracer)
{
    if (this == &tracer)
        return *this;
        
    m_name = tracer.m_name;
    ++copy_assign;

    return *this;
}

Tracer& Tracer::operator=(Tracer&& tracer) noexcept
{
    if (this == &tracer)
        return *this;

    m_name = std::move(tracer.m_name);
    ++move_assign;

    return *this;
}