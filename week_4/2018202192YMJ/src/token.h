#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

class Token
{
private:
    std::string m_contents;
public:
    enum Type
    {
        TAG, TEXT
    };
private:
    Type m_type;
public:
    Token() = default;
    Token(const std::string &contents, Type type);
    inline bool is_tag() const
    {
        return m_type == TAG;
    }
    inline bool is_text() const
    {
        return m_type == TEXT;
    }
    inline operator std::string() const
    {
        return m_contents;
    }
    friend std::ostream & operator <<(std::ostream &os, const Token &token);
};

#endif