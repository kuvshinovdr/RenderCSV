export module md;

export import a_table_writer;

export namespace render_csv
{

    class MarkdownWriter
        : public TableWriter
    {
    public:
    
        static auto test() noexcept
            -> int;
    };

}
