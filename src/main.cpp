/// @file  main.cpp
/// @brief Точка входа.
#include "config.hpp"
#include "csv.hpp"
#include "html.hpp"
#include "md.hpp"

#include <string_view>
#include <stdexcept>
#include <print>

using namespace std::literals;

constexpr auto ProgramInfo { "RenderCSV v.1.0 development"sv };

constexpr auto ProgramHelp 
{ R"!(
CSV to HTML or Markdown conversion utility.
)!"sv };

///////////////////////////////////////////////////////////////////////////////
// Точка входа
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
try
{
	using namespace render_csv;

	auto commandLineArguments = readCommandLineArguments(argc, argv);

	if (commandLineArguments.configData.help) {
		std::println("{}\n\n{}", ProgramInfo, ProgramHelp);
		return 0;
	}

	if (commandLineArguments.configData.version) {
		std::println("{}\n", ProgramInfo);
		return 0;
	}
	
	if (!commandLineArguments.errorLog.empty()) {
		std::println("TODO: report CLI errors\n");
		// TODO
	}

	std::println("TODO: main operation\n");
	// TODO

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