#include <string>

// FileNotFoundException exception
class FileNotFoundException
{
public:
    FileNotFoundException(std::string f) : fileName_(f){};
    std::string getFileName() const { return fileName_; }

private:
    std::string fileName_;
};