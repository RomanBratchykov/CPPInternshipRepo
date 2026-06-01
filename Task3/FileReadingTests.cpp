#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include "Analyzer.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Counter.h"

using namespace ISXCounter;

namespace {
std::filesystem::path Task3DataDir() {
    return std::filesystem::path("D:\\CPPInternshipRepo\\Task3Data");
}

std::filesystem::path Task3File(const char* name) {
    return Task3DataDir() / name;
}

std::string ReadFileToString(const std::filesystem::path& path) {
    std::ifstream input(path);
    std::string content;
    std::string line;
    while (std::getline(input, line)) {
        content += line;
        content += "\n";
    }
    return content;
}
}

TEST(FileReadingTests, AnalyzeEmptyFile) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test1.h"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 0);
    EXPECT_EQ(stats.comment_lines, 0);
    EXPECT_EQ(stats.code_lines, 0);
}

TEST(FileReadingTests, AnalyzeCommentOnlyFile) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test2.cpp"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 2);
    EXPECT_EQ(stats.comment_lines, 5);
    EXPECT_EQ(stats.code_lines, 0);
}

TEST(FileReadingTests, AnalyzeSimpleSourceFile) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test3.cpp"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 1);
    EXPECT_EQ(stats.comment_lines, 3);
    EXPECT_EQ(stats.code_lines, 1);
}

TEST(FileReadingTests, AnalyzeHeaderWithGuards) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test3.h"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 6);
    EXPECT_EQ(stats.comment_lines, 3);
    EXPECT_EQ(stats.code_lines, 6);
}

TEST(FileReadingTests, AnalyzeCFile) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test4.c"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 0);
    EXPECT_EQ(stats.comment_lines, 5);
    EXPECT_EQ(stats.code_lines, 1);
}

TEST(FileReadingTests, AnalyzeComplexHeader) {
    Counter stats = Analyzer::AnalyzeFile(Task3File("test5.h"));
    EXPECT_EQ(stats.total_files, 1);
    EXPECT_EQ(stats.blank_lines, 4);
    EXPECT_EQ(stats.comment_lines, 3);
    EXPECT_EQ(stats.code_lines, 16);
}

TEST(FileReadingTests, ProcessDirectoryAggregatesAllFiles) {
    Counter stats = FileReader::ProcessDirectory(Task3DataDir());
    EXPECT_EQ(stats.total_files, 6);
    EXPECT_EQ(stats.blank_lines, 13);
    EXPECT_EQ(stats.comment_lines, 19);
    EXPECT_EQ(stats.code_lines, 24);
}

TEST(FileReadingTests, WriteReportToTask3Data) {
    Counter stats;
    stats.total_files = 6;
    stats.blank_lines = 16;
    stats.comment_lines = 19;
    stats.code_lines = 24;

    const std::filesystem::path report_path = Task3DataDir() / "analysis_report.txt";
    ASSERT_TRUE(FileWriter::WriteToFile(report_path.string(), stats, 123));

    const std::string content = ReadFileToString(report_path);
    EXPECT_NE(content.find("Total processed files: 6"), std::string::npos);
    EXPECT_NE(content.find("Blank lines:           16"), std::string::npos);
    EXPECT_NE(content.find("Comment lines:         19"), std::string::npos);
    EXPECT_NE(content.find("Code lines:            24"), std::string::npos);
    EXPECT_NE(content.find("Execution time:        123 ms"), std::string::npos);
}
