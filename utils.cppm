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

}

export namespace render_csv::utils
{

	using FileToStringResult =
		std::expected<String, std::error_code>;

	/// @brief Прочитать заданный файл в память целиком как двоичные данные и вернуть как объект String. 
	[[nodiscard]] auto fileToString(FilePath const& filename) noexcept
		-> FileToStringResult;

	using StringToFileResult =
		std::expected<void, std::error_code>;

	enum class FileUpdateMode
	{
		Rewrite,
		Append,
	};
	
	/// @brief Записать данные StringView в заданный файл как двоичные данные.
	auto stringToFile(FilePath const& filename, 
						StringView      data, 
						FileUpdateMode  mode = FileUpdateMode::Rewrite
						) noexcept -> StringToFileResult;

}
