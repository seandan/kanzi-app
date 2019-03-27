m = module(project_name)

if build_from_sources:
    m.depends += ["kanzi_v8", "kanzi_components"]
    m.env["CPPPATH"] +=[os.path.join(engine_root, "sources", "kanzi_v8", "src")]
else:
    m.used_libraries += ["kanzi_v8", "kanzi_components"]
    m.env["CPPPATH"] +=[os.path.join(engine_root, "headers", "kanzi_v8", "include")]
    
m.env["CPPPATH"] +=[os.path.join(engine_root, "libraries", "common", "v8", "include")]

m.used_libraries += ["v8"]

del m