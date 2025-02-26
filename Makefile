style:
	git ls-files '*.cpp' '*.hpp' | xargs clang-format -i

build:
	cmake --build build

test:
	cmake --build build && ctest --test-dir build/rsq_library/tests/ -V
