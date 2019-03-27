# Copyright 2008-2016 by Rightware. All rights reserved.
import os
import sys

# --------------------------------------------------------------------------- #
# Utility functions
# --------------------------------------------------------------------------- #

def hasSubDirectoryWithName(directory, name):
    for subdir in os.walk(directory).next()[1]:
        if subdir == name:
            return True
    return False
    
def getRelativePathToDirectory(directoryName):
    scan_dir = os.getcwd()
    while os.path.exists(scan_dir):
        (head,tail) = os.path.split(scan_dir)
        if hasSubDirectoryWithName(head, directoryName):
            return os.path.relpath(os.path.join(head, directoryName))
        scan_dir = head
        if len(scan_dir) <= len(directoryName):
            break
    return None
    
def getEngineRootDirectory():
    #When working in KanziWorkspace 
    pathToEngine = getRelativePathToDirectory("Engine")
    if pathToEngine:
        if os.path.exists(os.path.join(pathToEngine, "version.txt")):
            return pathToEngine
    #When working in Internal projects
    pathToKanzi = getRelativePathToDirectory("Kanzi")
    if pathToKanzi:
        pathToEngine = os.path.join(pathToKanzi, "Engine")
        if os.path.exists(os.path.join(pathToEngine, "version.txt")):
            return pathToEngine
            
    return None

def getEngineBuildScriptPath():   
    buildScriptPath = os.path.join(engine_root, "scripts", "build.py")
    if os.path.exists(buildScriptPath):
        return buildScriptPath
    else:
        return None
    
# --------------------------------------------------------------------------- #
# Entry point
# --------------------------------------------------------------------------- #

global engine_root
global project_root
global project_name
global platform_name
global output_root
global default_gl_profile
global supported_gl_profiles

try:
    platform_name
except:
    print("No platform_name defined in SConstruct file.")


try:
    engine_root
except:
    # If engine_root is not set in SConstruct, try to resolve location in parent folders
    engine_root = getEngineRootDirectory()
    if engine_root is None:
        print(os.path.join("Engine", "version.txt") + " not found in parent directories of: " + os.path.abspath(os.getcwd())) 
        sys.exit("ERROR: Could not set engine_root.")

buildScript = getEngineBuildScriptPath()
if buildScript is None:
    print("Main build script not found in: " + os.path.abspath(buildScriptPath))
    sys.exit("ERROR: Could not locate build.py.")

execfile(buildScript)
