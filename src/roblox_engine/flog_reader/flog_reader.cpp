#include "flog_reader.hpp"

using namespace roblox_engine;

std::filesystem::path flog_reader_t::get_log_info()
{
    PWSTR app_data = 0;
    char destination[MAX_PATH];

    if (SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, 0, &app_data) == S_OK)
        wcstombs(destination, app_data, MAX_PATH);
    else
        return "";

    std::string log_location = "\\Roblox\\logs";
    std::string logs = std::string(destination) + log_location;
    if (!std::filesystem::exists(logs) || !std::filesystem::is_directory(logs))
        return "";

    std::filesystem::file_time_type latest_time;
    std::filesystem::path latest_file_path;

    for (const auto& entry : std::filesystem::directory_iterator(logs))
    {
        if (std::filesystem::is_regular_file(entry.path()))
        {
            auto last_write_time = std::filesystem::last_write_time(entry.path());
            if (last_write_time > latest_time)
            {
                latest_time = last_write_time;
                latest_file_path = entry.path();
            }
        }
    }
    return latest_file_path;
}