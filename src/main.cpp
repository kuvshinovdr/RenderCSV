/// @file  main.cpp
/// @brief Точка входа.
#include "config.hpp"
#include "csv.hpp"
#include "html.hpp"
#include "md.hpp"
#include "file_group_action.hpp"

#include <stdexcept>
#include <print>

using namespace render_csv;

constexpr auto ProgramInfo { "RenderCSV v.1.0 development"sv };

constexpr auto ProgramHelp 
{ R"!(
CSV to HTML or Markdown conversion utility.
)!"sv };

constexpr auto ErrorMarker             { "ERROR"sv };
constexpr auto WrittenMarker           { "WRITTEN"sv };
constexpr auto MessagePassHelpArgument { "No valid arguments passed: use --help argument to get some info."sv };
constexpr auto MessageErrorLogNotEmpty { "Supplied command line arguments contain errors:"sv };
constexpr auto MessageProcessingErrors { "Errors occured while processing files:"sv };
constexpr auto MessageStdException     { "Internal error: unhandled exception"sv };
constexpr auto MessageUnknownException { "Internal error: unknown unhandled exception"sv };
 
auto printErrorLog(CommandLineArguments::ErrorLog const& errors)
	-> int
{
	std::println("{}", MessageErrorLogNotEmpty);
	auto errorCount { int{} };

	for (auto& entry : errors) {
		std::println("{}({}): {:?} -- {}", ErrorMarker, errorCount++, entry.argument, entry.error);
		if (!entry.details.empty()) {
			std::println("\t-- {}", entry.details);
		}

		std::println();
	}

	return errorCount;
}

auto printErrorLog(FileGroupResult::ErrorLog const& errors)
	-> int
{
	std::println("{}", MessageProcessingErrors);
	auto errorCount { int{} };

	for (auto& entry : errors) {
		std::println("{}({}): {}", ErrorMarker, errorCount++, entry);
	}

	return errorCount;
}

[[nodiscard]] bool hasNothingToDo(ConfigData const& configData)
{
	return configData.fileGroups.empty() && !configData.help && !configData.version;
}

[[nodiscard]] bool processCasesWithNoFileGroupOperations(CommandLineArguments const& cliArguments)
{
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

	if (hasNothingToDo(configData)) {
		std::println("{}", MessagePassHelpArgument);
		return false;
	}

	return true;
}

auto processFileGroups(ConfigData const& configData)
	-> int
{
	auto errorCount { int{} };

	for (auto& fg : configData.fileGroups) {
		auto  result { processFileGroup(fg) };
		auto& errors { result.errorLog      };
		if (!errors.empty()) {
			errorCount += printErrorLog(errors);
		} else {
			std::println("...{} {}", fg.out, WrittenMarker);
		}
	}

	return errorCount;
}

///////////////////////////////////////////////////////////////////////////////
// Точка входа
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
try
{
	auto cliArguments { parseCommandLineArguments(argc, argv) };
	
	if (processCasesWithNoFileGroupOperations(cliArguments)) {
		return processFileGroups(cliArguments.configData);
	}

	return 1;
}
catch (std::exception const& e)
{
	std::println("{} ({})", MessageStdException, e.what());
	return 1;
}
catch (...)
{
	std::println("{}", MessageUnknownException);
	return 1;
}