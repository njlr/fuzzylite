cxx_library(
  name = 'fuzzylite',
  header_namespace = 'fl',
  exported_headers = subdir_glob([
    ('fuzzylite/fl', '**/*.h'),
  ]),
  srcs = glob([
    'fuzzylite/src/**/*.cpp',
  ], excludes = [
    'fuzzylite/src/main.cpp',
  ]),
  compiler_flags = [
    '-std=c++11',
  ],
  visibility = [
    'PUBLIC',
  ],
)
