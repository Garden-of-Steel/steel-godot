#include "icon3d_gizmo_plugin.h"

#include "core/io/resource_loader.h"
#include "core/object/script_language.h"

Icon3DGizmoPlugin::Icon3DGizmoPlugin() {
}

bool Icon3DGizmoPlugin::has_gizmo(Node3D *p_spatial) {
    Ref<Script> s = p_spatial->get_script();
    return s.is_valid() && !s->get_class_icon3d_path().is_empty();
}

String Icon3DGizmoPlugin::get_gizmo_name() const {
    return "Icon3D";
}

void Icon3DGizmoPlugin::redraw(EditorNode3DGizmo *p_gizmo) {
    p_gizmo->clear();

    Node3D *n = p_gizmo->get_node_3d();
    Ref<Script> s = n->get_script();

    if (s.is_null()) {
        return;
    }

    const String path = s->get_class_icon3d_path();

    if (path.is_empty()) {
        return;
    }

    if (!materials.has(path)) {
        Ref<Texture2D> tex = ResourceLoader::load(path);
        create_icon_material(path, tex);
    }

    Ref<Material> icon = get_material(path, p_gizmo);

    if (icon.is_valid()) {
        p_gizmo->add_unscaled_billboard(icon, 0.05);
    }
}