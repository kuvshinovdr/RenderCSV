import std;
import config;
import csv;
import html;
import md;
import utils;

int main(int argc, char* argv[])
{
	std::println("main");

	using namespace render_csv;
	Config::test();
	CsvReader::test();
	HtmlWriter::test();
	MarkdownWriter::test();
	
	return 0;
}