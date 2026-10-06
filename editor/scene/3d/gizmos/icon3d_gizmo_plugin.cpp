/**************************************************************************/
/*  icon3d_gizmo_plugin.cpp                                               */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

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
