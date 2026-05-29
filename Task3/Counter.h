#pragma once

namespace ISXCounter
{
struct Counter
{
	int total_files{0};
	int blank_lines{0};
	int comment_lines{0};
	int code_lines{0};

	// METHODS
	void Add(const Counter& other)
	{
		total_files += other.total_files;
		blank_lines += other.blank_lines;
		comment_lines += other.comment_lines;
		code_lines += other.code_lines;
	}
};
}