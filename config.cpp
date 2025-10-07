module config;

import std;

namespace render_csv
{

    class ConfigImpl
        : public Config
    {
    public:
        ConfigImpl(int argc, char* argv[]) noexcept
        {
            for (int i = 1; i < argc; ++i) {
                auto const arg { std::string_view(argv[i]) };
                if (validateArgument(arg)) {
                    
                }
            }
        }

        bool needTesting() const noexcept override
        {
            return m_needTesting;
        }

        bool needHelp() const noexcept override
        {
            return m_needHelp;
        }

        auto getArgumentValidationLog() const noexcept
            -> ArgumentValidationLog override
        {
            return ArgumentValidationLog(m_argumentValidationLog);
        }

        static auto test() noexcept
            -> int
        {
            return 0;
        }

    private:
        bool m_needTesting  { false };
        bool m_needHelp     { false };

        std::vector<ArgumentValidationEntry> m_argumentValidationLog;

        [[nodiscard]] bool validateArgument(std::string_view arg) const noexcept
        {
            return true;
        }
    };

    auto Config::fromCommandline(int argc, char* argv[])
        -> OwnerPtr
    {
        return OwnerPtr { new ConfigImpl(argc, argv) };
    }

    auto Config::test() noexcept
        -> int
    {
        std::println("\nConfig::test");
        return ConfigImpl::test();
    }

}
