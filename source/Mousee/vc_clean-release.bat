@echo off
REM echo.
REM IF "%~1"=="" echo 请拖工程文件至：&echo.&echo   %~0 &echo.&echo 图标上 &goto END

call "%VS90COMNTOOLS%vsvars32.bat"
vcbuild /clean Mousee.vcproj Release

:END
echo.
pause