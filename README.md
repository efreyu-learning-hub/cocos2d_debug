# cocos2dx-debug

**cocos2dx-debug** is an interactive **ImGui-based debug inspector** for **cocos2d-x** projects.

It is designed primarily as an **educational tool**, making it easier for beginners to understand how scenes, nodes, and transformations work in a real game engine environment.

---

## Requirements

- cocos2d-x (CMake-based project)
- C++17 or newer

---

## How to integrate into your cocos2d-x project

### 1. Add the repository as a submodule

From your project root:
```bash
git submodule add git@github.com:efreyu-learning-hub/cocos2d_debug.git Classes/cocos2d_debug
```
### 2. Register the module in CMakeLists.txt
In your main CMakeLists.txt, after declaring source lists:
```cmake
set(GAME_SOURCE)
set(GAME_HEADER)
```
add:
```cmake
add_subdirectory(Classes/cocos2d_debug) # add debug draw module
```
### 3. Link the debug module to your app target
Find this line:
```cmake
target_link_libraries(${APP_NAME} cocos2d)
```
and replace it with:
```cmake
initDebugModule()
target_link_libraries(${APP_NAME} cocos2d ${GENERIC_LIB})
```
### 4. Initialize the debug layer on application startup
In AppDelegate::applicationDidFinishLaunching()

before creating the first scene:
```cpp
#ifdef IMGUI_ENABLED
    debugModule::ImGuiDebugLayer::initializeLayer();
#endif
```
This creates a singleton debug layer that:
- lives for the entire application lifetime
- automatically reattaches when scenes change
- always stays on top of the scene graph

#### Make sure you added -DCMAKE_OSX_ARCHITECTURES=x86_64 and -DDEBUG=1 to your cmake command line.
- -DCMAKE_OSX_ARCHITECTURES=x86_64 required to enable 64bit build even if you are using Apple Silicon.
- -DDEBUG=1 required to enable debug build that enables debug overlay.

```bash
cd cocos2dsample
cmake . -B build -DCMAKE_OSX_ARCHITECTURES=x86_64 -DDEBUG=1
```

### Intended audience
- 👶 Beginners learning cocos2d-x
- 🎓 Students studying game development
- 🛠️ Tooling and editor-style projects
- 🧪 Debugging complex scene graphs

### Notes
- This project uses ImGui internal APIs — update ImGui with care
- Intended strictly for debugging and educational purposes
- Contributions and suggestions are welcome 🙂

### Credits:
- https://github.com/Xrysnow/cocos2d-x-imgui fork