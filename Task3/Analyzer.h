#pragma once

#include "FileReader.h"
#include "Counter.h"
#include <filesystem>
#include <string>
#include <fstream>

namespace ISXCounter
{
class Analyzer
{
public:
	// METHODS
	static Counter AnalyzeFile(const std::filesystem::path& file_path)
	{
		Counter result;
		result.total_files = 1;

		std::ifstream file(file_path);
		if (!file.is_open())
		{
			return result;
		}

		std::string line;
		bool in_multiline_comment = false;

		while (std::getline(file, line))
		{
			size_t start_pos = line.find_first_not_of(" \t\r\n");

			if (start_pos == std::string::npos)
			{
				if (in_multiline_comment)
				{
					result.comment_lines++;
				}
				else
				{
					result.blank_lines++;
				}
				continue;
			}

			std::string trimmed = line.substr(start_pos);

			if (in_multiline_comment)
			{
				result.comment_lines++;
				if (trimmed.find("*/") != std::string::npos)
				{
					in_multiline_comment = false;
				}
			}
			else
			{
				if (trimmed.substr(0, 2) == "//")
				{
					result.comment_lines++;
				}
				else if (trimmed.substr(0, 2) == "/*")
				{
					result.comment_lines++;
					if (trimmed.find("*/") == std::string::npos)
					{
						in_multiline_comment = true;
					}
				}
				else
				{
					result.code_lines++;
				}
			}
		}

		return result;
	}
};
}