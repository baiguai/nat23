#ifndef FILEIO_H
#define FILEIO_H

#include <filesystem>
#include <string>
#include <fstream>


// ---- Tools ------------------------------------------------------------------
inline bool fileExists(const std::string& path)
{
    std::ifstream in(path);
    return in.good();
}
// -----------------------------------------------------------------------------


// ---- Create Directory -------------------------------------------------------
inline bool createDirectories(const std::string& path)
{
    std::error_code ec;
    std::filesystem::create_directories(path, ec);
    return !ec;
}
// -----------------------------------------------------------------------------

#endif
