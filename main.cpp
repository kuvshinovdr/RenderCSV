import std;
import config;
import csv;
import html;
import md;
import a_utils;

using namespace std::literals;

constexpr auto ProgramInfo { "RenderCSV v.0.1"sv };

constexpr auto ProgramHelp 
{ R"!(
CSV to HTML or Markdown conversion utility.
)!"sv };

int main(int argc, char* argv[])
try
{
	using namespace render_csv;

	auto config { Config::fromCommandline(argc, argv) };
	if (!config) {
		throw std::runtime_error("failed to create Config instance");
	}

	if (config->needTesting()) {
		Config::test();
		CsvReader::test();
		HtmlWriter::test();
		MarkdownWriter::test();
	}

	if (config->needHelp()) {
		std::println("{}\n\n{}", ProgramInfo, ProgramHelp);
	}
	
	return 0;
}
catch (std::exception const& e)
{
	std::println("Internal error: unhandled exception ({})", e.what());
	return 1;
}
catch (...)
{
	std::println("Internal error: unknown unhandled exception");
	return 1;
}