#pragma once

#include <stddef.h>

struct ImVec2;

namespace imnodes
{
enum ColorStyle
{
    ColorStyle_NodeBackground = 0,
    ColorStyle_NodeBackgroundHovered,
    ColorStyle_NodeBackgroundSelected,
    ColorStyle_NodeOutline,
    ColorStyle_TitleBar,
    ColorStyle_TitleBarHovered,
    ColorStyle_TitleBarSelected,
    ColorStyle_Link,
    ColorStyle_LinkHovered,
    ColorStyle_LinkSelected,
    ColorStyle_Pin,
    ColorStyle_PinHovered,
    ColorStyle_PinOutline,
    ColorStyle_GridBackground,
    ColorStyle_GridLine,
    ColorStyle_Count
};

enum Flags
{
    Flags_None = 0,
    Flags_NodeOutline = 1 << 0,
    Flags_PinOutline = 1 << 1
};

struct Style
{
    // by default, set to Flags_NodeOutline | Flags_PinOutline
    Flags flags;
    // set these mid-frame using Push/PopColorStyle
    unsigned int colors[ColorStyle_Count];
};

struct EditorContext;

EditorContext* EditorContextCreate();
void EditorContextFree(EditorContext*);
void EditorContextSet(EditorContext*);

void Initialize();
void Shutdown();

Style& GetStyle();

void BeginNodeEditor();

void PushColorStyle(ColorStyle item, unsigned int color);

void BeginNode(int id);
void Name(const char* name);

// The attribute ids must be unique with regards to other attribute ids, not
// other nodes and links
void BeginInputAttribute(int id);
void BeginOutputAttribute(int id);
void EndAttribute();

void EndNode();

// The attributes ids used here must match the ids used in BeginAttribute()
void Link(int id, int start_attr, int end_attr);

void PopColorStyle();

void EndNodeEditor();

void SetNodePos(int node_id, const ImVec2& pos);

// new replacements for events
bool IsNodeHovered(int* node_id);
bool IsLinkHovered(int* link_id);
bool IsPinHovered(int* attribute_id);

bool IsNodeSelected(int* node_id);
bool IsLinkSelected(int* link_id);

// Is the user dragging a new link?
bool IsLinkStarted(int* started_at_attr);
// Did the user drop the new link before connecting it to a second attribute?
bool IsLinkDropped();
// Did the user create a new link?
bool IsLinkCreated(int* started_at_attr, int* ended_at_attr);

// Save the editor state to a string. The data is written in the INI format.
// If the editor is left out, then the function will save the currently set
// editor's state.
const char* SaveCurrentEditorStateToMemory(size_t* data_size = NULL);
const char* SaveEditorStateToMemory(
    const EditorContext* editor,
    size_t* data_size = NULL);

void LoadCurrentEditorStateFromMemory(const char* data, size_t data_size);
void LoadEditorStateFromMemory(
    EditorContext* editor,
    const char* data,
    size_t data_size);

void SaveCurrentEditorStateToDisk(const char* file_name);
void SaveEditorStateToDisk(const EditorContext* editor, const char* file_name);

void LoadCurrentEditorStateFromDisk(const char* file_name);
void LoadEditorStateFromDisk(EditorContext* editor, const char* file_name);

} // namespace imnodes
