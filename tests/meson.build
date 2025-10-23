# Dependencies
doctest_proj = subproject('doctest')
doctest_dep = doctest_proj.get_variable('doctest_dep')

# Test sources
tests = [
    'test_config.cpp',
    'test_csv.cpp',
    'test_md.cpp',
    'test_html.cpp',
]

test_sources = files(tests)

# Build test executable
# doctest provides its own main() if you define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN,
# but it's cleaner to let the subproject handle it via the dependency.
rendercsv_tests = executable('rendercsv_tests',
    source_files + test_sources + files(['test_main.cpp']),
    dependencies:        doctest_dep,
    include_directories: inc,
    link_args:           linkargs,
    install:             false
)

# Register test
test('unit-tests', rendercsv_tests)