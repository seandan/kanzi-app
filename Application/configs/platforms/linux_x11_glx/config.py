if "linux-x86_64" in platform_attributes:
    platform = "linux-x86_64"
else:
    platform = "linux-x86"

m = module(project_name)
m.env["CPPPATH"] +=[os.path.join(engine_root, "libraries", "platforms", platform, "v8", "include")]
m.env["LIBPATH"] += [os.path.join(engine_root, "libraries", "platforms", platform, "v8", "lib")]
m.env["LIBS"] += ["v8"]
del m