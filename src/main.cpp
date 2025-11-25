/// @file  main.cpp
/// @brief Точка входа.
#include "config.hpp"
#include "file_group_action.hpp"

#include <stdexcept>
#include <print>
#include <ranges>
#include <algorithm>

using namespace render_csv;

// Краткая информация о программе (выводится по --version).
constexpr auto ProgramInfo { "RenderCSV v.1.0 development\nhttps://github.com/kuvshinovdr/RenderCSV/"sv };

// Справочная информация (выводится по --help).
constexpr auto ProgramHelp 
{ R"!(
CSV to HTML or Markdown conversion utility.

Auxiliary parameters
--------------------

--help    : show this message;
--version : brief version information.

Output mode settings
--------------------

--md        : generate Markdown (GFM by default);
--md=gfm    : select GFM (Github Flavored Markdown) explicitly;

--html      : generate HTMLv5, same as --html=full;
--html=part : only HTML tables code without the document body;
--html=full : full HTML document;
--html=full-styled : full HTML document with embedded CSS;

Output file mode
----------------

--overwrite : overwrite the output file if it exists;
--append    : append the output file with the result to be generated;
--prepend   : prepend the output file with the result to be generated;

If none of these keys is passed and the output file exists then
an error is reported and the output file is left intact.

Data
----

May form several groups.

-c *caption* or --caption *caption* : set the table caption;
-i *input* or   --in *input*        : set the input CSV-file path.

--many : pass this to inform the utility there are several input files;
         if this parameter is absent then each input file is to be written into
         a separate output file with the same name but .md or .html extension.

-o *output* or  --out *output*  : optional output file path;
                                  should be passed after the corresponding
                                  input file.

-h *header* or  --head *header* : the path to a file, which contents are to be
                                  inserted before the first output result.

-m *middle* or  --mid *middle*  : the path to a file, which contents are to be
                                  inserted to separate two outputs results.

-f *footer* or  --foot *footer* : the path to a file, which contents are to be
                                  inserted after the last output result.

--css *file* : the path to a CSS-file to be referenced or embedded (HTML mode).
)!"sv };

// Вспомогательные текстовые константы.
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
