# Automatically collect all .cpp files in src/
source_files = [
	'config.cpp',
	'csv.cpp',
	'file_to_string.cpp',
	'html.cpp',
	'md.cpp',
	'string_to_file.cpp',
	
	'main.cpp',
]

# Create main executable
executable('rendercsv', source_files,
  include_directories: include_directories('../src'),
  install: true,
  link_args: linkargs
)
