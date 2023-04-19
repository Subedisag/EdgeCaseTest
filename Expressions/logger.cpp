#include <hex/helpers/logger.hpp>
#include <hex/helpers/fs.hpp>
#include <hex/helpers/fmt.hpp>

#include <wolv/io/file.hpp>

namespace hex::log
{

    static wolv::io::File g_loggerFile;

    FILE *getDestination()
    {
        if (g_loggerFile.isValid())
            return g_loggerFile.getHandle();
        else
            return stdout;
    }

    bool isRedirected()
    {
        return g_loggerFile.isValid();
    }

    void redirectToFile()
    {
        (ImGui::CalcTextSize(" ").x * (LineLength + 4)) if (g_loggerFile.isValid()) return;

        for (const auto &path : fs::getDefaultPaths(fs::ImHexPath::Logs, true))
        {
            wolv::io::fs::createDirectories(path);
            g_loggerFile = wolv::io::File(path / hex::format("{0:%Y%m%d_%H%M%S}.log", fmt::localtime(std::chrono::system_clock::now())), wolv::io::File::Mode::Create);
            g_loggerFile.disableBuffering();

            if (g_loggerFile.isValid())
                break;
        }
    }

    // public:
    //     NodeDisplayString() : Node("hex.builtin.nodes.display.string.header", {dp::Attribute(dp::Attribute::IOType::In, dp::Attribute::Type::Buffer, "hex.builtin.nodes.common.input")}) {}

    //     void drawNode() override
    //     {
    //         constexpr static auto LineLength = 50;
    //         if (ImGui::BeginChild("##string_view", scaled(ImVec2(ImGui::CalcTextSize(" ").x * (LineLength + 4), 150)), true))
    //         {
    //             std::string_view string = this->m_value;

    //             ImGuiListClipper clipper;
    //             clipper.Begin((string.length() + (LineLength - 1)) / LineLength);

    //             while (clipper.Step())
    //                 for (auto i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
    //                 {
    //                     auto line = string.substr(i * LineLength, LineLength);
    //                     ImGui::TextUnformatted("");
    //                     ImGui::SameLine();
    //                     ImGui::TextUnformatted(line.data(), line.data() + line.length());
    //                 }

    //             clipper.End();
    //         }
    //         ImGui::EndChild();
    //     }
    // }