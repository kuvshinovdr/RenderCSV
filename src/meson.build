# Sources
sources = [
    'config.cpp',
    'csv.cpp',
    'file_to_string.cpp',
    'html.cpp',
    'md.cpp',
    'string_to_file.cpp',
]

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('rendercsv',
    source_files + files(['main.cpp']),
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
