#include "render_view.hpp"

using namespace roblox_engine::graphics;

uintptr_t render_view_t::get()
{
    std::filesystem::path latest_file_path = flog_reader->get_log_info();
    if (std::filesystem::exists(latest_file_path))
    {
        std::ifstream file(latest_file_path);

        if (file.is_open())
        {
            std::vector<std::string> lines;
            std::string line;

            while (std::getline(file, line))
                lines.push_back(line);

            file.close();

            for (auto iter = lines.rbegin(); iter != lines.rend(); ++iter)
            {
                std::string message = *iter;
                if (message.find("SurfaceController[_:1]::initialize view") != std::string::npos)
                {
                    message.erase(message.begin(), message.end() - 17);

                    const auto chars_to_remove = ")";
                    for (auto i = 0u; i < strlen(chars_to_remove); ++i)
                        message.erase(remove(message.begin(), message.end(), chars_to_remove[i]), message.end());

                    ptrdiff_t ptr_ret;
#pragma warning(push)
#pragma warning(disable : 6031)
                    sscanf(message.c_str(), "%tx", &ptr_ret); // Only hex supported, %td for decimal.
#pragma warning(pop)
                    return static_cast<uintptr_t>(ptr_ret);
                }
            }
        }
    }
}