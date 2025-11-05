/// @file  main.cpp
/// @brief Точка входа.
#include "config.hpp"
#include "csv.hpp"
#include "html.hpp"
#include "md.hpp"
#include "file_group_action.hpp"

#include <stdexcept>
#include <print>
#include <ranges>
#include <algorithm>

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
 
void printErrorLogEntry(CommandLineArguments::ErrorLogEntry const& entry, int errorNo)
{
	std::println("{}({}): {:?} -- {}", ErrorMarker, errorNo, entry.argument, entry.error);
	
	if (!entry.details.empty()) {
		std::println("\t-- {}", entry.details);
	}

	std::println();
}

void printErrorLogEntry(FileGroupResult::ErrorLogEntry const& entry, int errorNo)
{
	std::println("{}({}): {}", ErrorMarker, errorNo, entry);
}

auto printErrorLog(auto const& errorLog)
	-> int
{
	for (auto&& [errorCount, entry] : std::views::enumerate(errorLog)) {
		printErrorLogEntry(entry, errorCount);
	}

	return static_cast<int>(errorLog.size());
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
		std::println("{}", MessageErrorLogNotEmpty);
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

auto processFileGroupWithOutput(ConfigData::FileGroup const& fg)
	-> int
{
	auto result { processFileGroup(fg) };
	
	if (auto& errors { result.errorLog }; !errors.empty()) {
		std::println("{}", MessageProcessingErrors);
		return printErrorLog(errors);
	}

	std::println("...{} {}", fg.out, WrittenMarker);
	return 0;
}

auto processFileGroups(ConfigData const& configData)
	-> int
{
	auto errorCount { int{} };

	for (auto& fg : configData.fileGroups) {
		errorCount += processFileGroupWithOutput(fg);
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