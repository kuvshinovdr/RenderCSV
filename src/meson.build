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

inc = include_directories('.')

# Create main executable
executable('rendercsv', source_files,
  include_directories: inc,
  install: true,
  link_args: linkargs
)
