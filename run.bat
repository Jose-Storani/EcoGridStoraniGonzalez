@echo off
cd /d "%~dp0"
bin\Debug\EcoGrid.exe
echo.
echo ============================================
echo  Codigo de salida: %errorlevel%
echo ============================================
cmd /k
