@echo off
REM echo.
REM IF "%~1"=="" echo ���Ϲ����ļ�����&echo.&echo   %~0 &echo.&echo ͼ���� &goto END

call "%VS90COMNTOOLS%vsvars32.bat"
vcbuild Mousee.vcproj Release

:END
echo.
pause