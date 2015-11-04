# Contribution Guide

Welcome to our contribution guideline. Feel free to explore our documentation page.

## API Docs

The API docs should be written in the header files. It will be automatically generated from the project code
using [Doxygen](http://www.doxygen.org/) docs using [C-like (C/C++) formatting](https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html#cppblock).

Our API docs should start with  `///` for single line or `/**` `*/` for multilines above the function or class.
Alternatively, use `int myVariable; ///< description` for inline description.

Whenever possible, use the correct [semantic command](https://www.stack.nl/~dimitri/doxygen/manual/commands.html) when writing the API docs (e.g `params`, `todo`, `class`). Also use the `@` sign instead of backslash for command (e.g. `@params`).

Please ensure the consistency of the syntax, and also consult with the team when in doubt of a certain format. It is also good to check out at some tips that others mentioned in online forum or Q&A site such as Stackoverflow (e.g. [Tips Doxygen](https://www.stack.nl/~dimitri/doxygen/manual/commands.html)).

## Branch naming

    # Specific Feature or Functionality
    feature/<feature-label>
    
    # Semantic, Confiuration, Formatting, Code Cleanup, etc...
    enhance/<enhancement>
    
    # Bug, Error Fix, Etc...
    fix/<fix-label>

## Code Style

Use forward slash for library include path.

    #include "path/path/module.h"
