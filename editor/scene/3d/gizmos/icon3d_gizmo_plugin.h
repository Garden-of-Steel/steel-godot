#pragma once
#include "editor/scene/3d/node_3d_editor_gizmos.h"

class Icon3DGizmoPlugin : public EditorNode3DGizmoPlugin {
    GDCLASS(Icon3DGizmoPlugin, EditorNode3DGizmoPlugin);

public:
    bool has_gizmo(Node3D *p_spatial) override;
    String get_gizmo_name() const override;
    void redraw(EditorNode3DGizmo *p_gizmo) override;
    Icon3DGizmoPlugin();
};