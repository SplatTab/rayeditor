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
    if (condition) return true; // One statement

    if (condition)
    {
        return true;
    }
    else
    {
        return false;
    } // Doesn't count so put brackets

    if (condition) {
        if (condition) return true; // Counts
    } // One brackets
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
src\ Should only contain source code that is is going to be modified and not belonging to a libary!

lib\ opposite of src\ Should only contain source code/compiled libs that relate to other libaries and should be put in a folder for that libary.

include\ Similar goes for include libaries should be put into a folder for that libary.

folders\ Should be categorized based off features/namespaces such as imgui, raylib, editor, docks, utility.

