#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Counter.h"

namespace ISXCounter
{
	class FileWriter
	{
	public:
		// METHODS
		static void WriteToConsole(const Counter& results, long long duration_ms)
		{
			std::cout << "\n---- Results ----\n";
			std::cout << "Total processed files: " << results.total_files << "\n";
			std::cout << "Blank lines:           " << results.blank_lines << "\n";
			std::cout << "Comment lines:         " << results.comment_lines << "\n";
			std::cout << "Code lines:            " << results.code_lines << "\n";
			std::cout << "Execution time:        " << duration_ms << " ms\n";
			std::cout << "------------------------\n";
		}

		static bool WriteToFile(const std::string& file_name, const Counter& results, long long duration_ms)
		{
			std::ofstream output_file(file_name);
			if (!output_file.is_open())
			{
				return false;
			}

			output_file << "---- Results ----\n";
			output_file << "Total processed files: " << results.total_files << "\n";
			output_file << "Blank lines:           " << results.blank_lines << "\n";
			output_file << "Comment lines:         " << results.comment_lines << "\n";
			output_file << "Code lines:            " << results.code_lines << "\n";
			output_file << "Execution time:        " << duration_ms << " ms\n";
			output_file << "------------------------\n";

			output_file.close();
			return true;
		}
	};
}