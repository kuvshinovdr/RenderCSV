export module utils;

import std;

export namespace render_csv
{

	using FilePath =
		std::filesystem::path;

	using StringView = 
		std::string_view;

	using String =
		std::string;

	using FileToStringResult =
		std::expected<String, std::error_code>;

	[[nodiscard]] auto fileToString(FilePath const& filename) noexcept
		-> FileToStringResult;

	using StringToFileResult =
		std::expected<void, std::error_code>;
	
	auto stringToFile(FilePath const& filename, StringView data) noexcept
		-> StringToFileResult;

}