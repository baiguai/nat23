#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fmt/format.h>
#include "fileio.h"

namespace history
{
    inline void createHistoryDirectories()
    {
        createDirectories("data/history");
        createDirectories("data/logs");
    }

    inline auto timeStamp()
    {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto local = zoned_time{current_zone(), now}.get_local_time();
        auto secs = floor<seconds>(local);
        return fmt::format("{:%Y%m%d-%H:%M:%S}", secs);
    }

    inline auto debugLogFileName()
    {
        auto now = std::chrono::system_clock::now();
        return fmt::format("data/logs/{:%Y%m%d}_debuglog.txt", now);
    }

    inline auto historyFileName()
    {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto local = zoned_time{current_zone(), now}.get_local_time();
        return fmt::format("data/history/{:%Y%m%d}_log.txt", local);
    }


    // Debug logs are only written if the build is NOT a release build.
    inline void debuglog(const std::string& log_msg)
    {
        #ifndef NDEBUG

        auto file_path = debugLogFileName();

        std::ofstream out(file_path, std::ios::app);
        if (!out.good())
        {
            return;
        }
        out << log_msg << "\n";

        #endif
    }

    inline void writeHistory(const std::string& roll)
    {
        auto file_path = historyFileName();

        std::ofstream out(file_path, std::ios::app);
        if (!out.good())
        {
            return;
        }
        out << timeStamp() << "\n--------------------------------------------------------------------------------\n";
        out << roll << "\n\n";
    }

    inline std::string readHistory()
    {
        std::ifstream in(historyFileName());
        if (!in.good())
        {
            return "Error";
        }

        std::stringstream buffer;
        buffer << in.rdbuf();
        return buffer.str();
    }



    // Methods the user calls
    inline void clearHistory()
    {
        system("rm -rf data/history/*");
    }
}

#endif
