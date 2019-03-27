m = module(project_name)

m.env["CPPPATH"] +=["E:\\svn\\SoftwareDesign\\APP\\Code_Kanzi\\Car\\Application\\src\\page"]
m.env["CPPPATH"] +=["E:\\svn\\SoftwareDesign\\APP\\Code_Kanzi\\Car\\Application\\src\\controller"]

m.env["CPPPATH"] +=["C:\\KanziWorkspace_3_2_3_414_89232\\Engine\\headers\\system\\windowing_system\\screen\\include\\system\\display"]
m.env["CPPPATH"] +=["E:\\svn\\SoftwareDesign\\APP\\Code_Kanzi\\public\\includes"]
m.env["LIBPATH"] += ["E:\\svn\\SoftwareDesign\\APP\\Code_Kanzi\\public\\lib"]
m.env["LIBS"] += ["pps"]
del m