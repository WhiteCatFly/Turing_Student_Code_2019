#include "internetworm.h"
#include <string>
#include <queue>

class HtmlParser : public URL {
    private:
        std::queue <URL> _link;
    public:
        HtmlParser();
        HtmlParser(URL x);
        ~HtmlParser();
        std::queue <URL> Origin();
        void Extract();

        //pushlink not supported;
        bool emptylink();
        URL frontlink();
        void poplink();
};