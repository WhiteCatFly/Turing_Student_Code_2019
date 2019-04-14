#ifndef ATTRIBUTE_H_INCLUDED
#define ATTRIBUTE_H_INCLUDED

class Attribute
{
private:
    std::string m_name;
    std::string m_value;
public:
    Attribute() = default;
    Attribute(const std::string &name, const std::string &value);
    inline void append_value(const std::string &value)
    {
        m_value += " " + value;
    }
    inline std::string name() const
    {
        return m_name;
    }
    inline std::string value() const
    {
        return m_value;
    }
    void remove_suf(const std::string &suf);
    friend std::ostream & operator <<(std::ostream &os, const Attribute &attribute);
};

#endif