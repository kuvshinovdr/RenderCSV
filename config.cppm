export module config;

export namespace render_csv
{

    class Config
    {
    public:
        virtual ~Config() = default;
        
        static auto test() noexcept
            -> int;
    };

}