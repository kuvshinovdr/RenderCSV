export module csv;

export import a_table_reader;

export namespace render_csv
{
    
    class CsvReader
        : public TableReader
    {
    public:

        static auto test() noexcept
            -> int;
    };
    
}