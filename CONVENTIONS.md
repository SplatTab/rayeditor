# Convetions

## Code Conventions
Code element | Convention | Example
--- | :---: | ---
Variables/Params/Pointers | *camelCase | `const char *projectDir;`
Functions | TitleCase | `Log::Info()`, `Project::SetProjectDirectory(const char *projectPath)`
Defines | ALL_CAPS | `#define EDITOR_VERSION`
Enum | TitleCase {ALL_CAPS} | `enum TraceLogLevel {LOG_INFO}`
Structs/Struct Members | TitleCase {camelCase} | `struct LogItem {int logType}`
Float Values | Always x.xf | `float editorVersion = 0.01f`


## Vscode Extensions
I personally use these extensions and I recommend you do too as they help with following our coding conventions and make others lifes easier

["redlin.remove-tabs-on-save"](https://marketplace.visualstudio.com/items?itemName=redlin.remove-tabs-on-save),

["shardulm94.trailing-spaces"](https://marketplace.visualstudio.com/items?itemName=shardulm94.trailing-spaces),

["ms-vscode.cpptools-extension-pack"](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)


## Indentation
1. Use 4 Spaces personally I prefer tabs but they make others lives harder but with fancy text editors this shouldn't really change much for you.
1. Use brackets in C# Fashion unless it is a one statement.
1. Avoid crazy space.
```cpp
int main()
{ // Note the brackets
    // 4 Spaces!!

    if (condition) return true;

    if (condition) return true;
    else return false;

    if (condition)
    {
        if (condition) return true;
    }

    if (condition)
    {
        // Some code
        // Some code
        // Some code
    }
    else
    {
        // One code
    }
}
// Avoid trailing space:
                                                                                                                                                                
```

## Project Structure
### File Naming:
File Type | Convention | Example
--- | :---: | ---
Header Files | ALL_LOWER_CASE | `rayeditor.hpp`, `raylib.h`
C/C++ Files | TitleCase | `ConsoleDock.cpp`(Only exception main.cpp)
Folders | ALL_LOWER_CASE | `src\`
### Folders:
New folders should be made when necessary. Ex: Namespaces, Libaries, Modules, Inherited Classes.

src\ -> Contains all the source code for the project.

lib\ -> Contains all the libraries for the project.

include\ -> Contains all the headers for the project.

data\ -> Contains all the data for the compiled application. Ex: General Icons(resources/icons), App Logo(resources/logo), Templates(templates), Helper Files(include/, libs/), etc.

example\ -> Example working project.