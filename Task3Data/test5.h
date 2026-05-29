//
// Created by Roman on 5/29/2026.
//

#include "test3.h"
#include <filesystem>
#include <chrono>
#include <iostream>
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
}


