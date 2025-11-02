/// @file  main.cpp
/// @brief Точка входа.
#include "config.hpp"
#include "csv.hpp"
#include "html.hpp"
#include "md.hpp"
#include "file_group_action.hpp"

#include <stdexcept>
#include <print>

using namespace std::literals;

constexpr auto ProgramInfo { "RenderCSV v.1.0 development"sv };

constexpr auto ProgramHelp 
{ R"!(
CSV to HTML or Markdown conversion utility.
)!"sv };

constexpr auto MessagePassHelpArgument { "No valid arguments passed: use --help argument to get some info."sv };
constexpr auto MessageErrorLogNotEmpty { "Supplied command line arguments contain errors:"sv };
 
auto printErrorLog(render_csv::CommandLineArguments::ErrorLog const& errors)
	-> int
{
	std::println("{}", MessageErrorLogNotEmpty);
	auto errorCount { int{} };

	for (auto& entry : errors) {
		std::println("ERROR({}): {:?} -- {}", errorCount++, entry.argument, entry.error);
		if (!entry.details.empty()) {
			std::println("\t-- {}", entry.details);
		}

		std::println();
	}

	return errorCount;
}


///////////////////////////////////////////////////////////////////////////////
// Точка входа
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
try
{
	using namespace render_csv;

	auto  cliArguments { parseCommandLineArguments(argc, argv) };
	auto& configData   { cliArguments.configData };
	auto& errorLog     { cliArguments.errorLog   };

	if (!errorLog.empty()) {
		return printErrorLog(errorLog);
	}

	if (configData.help) {
		std::println("{}\n\n{}", ProgramInfo, ProgramHelp);
	}

	if (configData.version) {
		std::println("{}", ProgramInfo);
	}
	
	if (configData.fileGroups.empty() && !configData.help && !configData.version) {
		std::println("{}", MessagePassHelpArgument);
		return 1;
	}

	for (auto& fg : configData.fileGroups) {

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