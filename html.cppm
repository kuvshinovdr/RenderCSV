export module html;

export import a_table_writer;

export namespace render_csv
{

    class HtmlWriter
        : public TableWriter
    {
    public:
    
        static auto test() noexcept
            -> int;
    };

}
