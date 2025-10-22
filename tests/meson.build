doctest_proj = subproject('doctest')
doctest_dep = doctest_proj.get_variable('doctest_dep')

# Automatically collect all test .cpp files
test_sources = ['test.cpp']

# Build test executable
# doctest provides its own main() if you define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN,
# but it's cleaner to let the subproject handle it via the dependency.
rendercsv_tests = executable('rendercsv_tests',
	test_sources,
	dependencies: doctest_dep,
	include_directories: include_directories('../src'),
	link_args: linkargs,
	install: false
)

# Register test
test('unit-tests', rendercsv_tests)