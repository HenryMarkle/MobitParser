# Mobit Parser

A simple library for parsing Adobe Director's Lingo scripts.

## Installation

Include it in your CMakeLists.txt:

```

add_subdirectory(path/to/lib)

...

target_link_libraries(yourApp PRIVATE MobitParser)

```

## Usage

```

std::string script("[ 1, \"Hello\", color(200, 200, 200), [ #tp: \"box\", #repeat: 1 ] ]");

auto tokens = MobitParser::tokenize(script);

auto nodes = parse(tokens);

// traverse node tree ..

```
