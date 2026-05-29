#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include "FileReader.h"
#include "FileWriter.h"
#include "Counter.h"

namespace ISXCounter
{
	class FileReadOrchestrator
	{
	public:
		// METHODS
		void Run()
		{
			std::string target_path;
			std::cout << "Enter project root folder path: ";
			std::getline(std::cin, target_path);

			std::filesystem::path root_path(target_path);
			if (!std::filesystem::exists(root_path) || !std::filesystem::is_directory(root_path))
			{
				std::cerr << "Error: Provided path is invalid or not a directory." << std::endl;
				return;
			}

			auto start_time = std::chrono::high_resolution_clock::now();

			Counter final_stats = ISXCounter::FileReader::ProcessDirectory(root_path);

			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

			FileWriter::WriteToConsole(final_stats, duration);
			std::filesystem::path output_dir("D:\\CPPInternshipRepo\\Task3Result");

			if (!std::filesystem::exists(output_dir))
			{
				std::filesystem::create_directories(output_dir);
			}
			const std::filesystem::path report_name = output_dir/ "analysis_report.txt";
			if (FileWriter::WriteToFile(report_name.string(), final_stats, duration))
			{
				std::cout << "Results have been successfully saved to '" << report_name << "'.\n";
			}
			else
			{
				std::cerr << "Error: Could not save results to file.\n";
			}
		}
	};
}