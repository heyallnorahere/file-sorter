@echo off
vendor\premake\premake5 vs2019
cmd /c "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild file-sorter.sln -p:Configuration=Release
echo "Done building!"
pause