export module config;

import std;
import utils;

export namespace render_csv
{

    class Config
    {
    public:
        virtual ~Config() = default;

        [[nodiscard]] virtual bool needTesting() const noexcept = 0;
        [[nodiscard]] virtual bool needHelp() const noexcept = 0;

        struct ArgumentValidationEntry
        {
            StringView argument;
            StringView error;
            StringView details;
        };

        using ArgumentValidationLog
            = std::span<ArgumentValidationEntry const>;

        [[nodiscard]] virtual auto getArgumentValidationLog() const noexcept
            -> ArgumentValidationLog = 0;
        
        using OwnerPtr =
            std::unique_ptr<Config>;

        [[nodiscard]] static auto fromCommandline(int argc, char* argv[])
            -> OwnerPtr;

        static auto test() noexcept
            -> int;
    };

}