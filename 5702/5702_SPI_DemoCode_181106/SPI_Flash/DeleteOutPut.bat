@echo off 
setlocal enabledelayedexpansion
title Delete Keil OutPut
color 0A
echo.
echo   ***************************************************************************
echo   ！！！！！！！！！！！务必在工程根目录下打开此文件！！！！！！！！！！！！！
echo   ！！！！！！！！！！！禁止在其他根目录下打开此文件！！！！！！！！！！！！！
echo   ！！！！！！！！！！！禁止在其他根目录下打开此文件！！！！！！！！！！！！！
echo   ！！！！！！！！！！！禁止在其他根目录下打开此文件！！！！！！！！！！！！！
echo   *************************************************************************** 
echo   *                         Edit By Sonix Pricker                           *
echo   *                             %time%                                 *
echo   *                           %date%                               * 
echo   *            功能：清理Keil/SN8C/M2IDE编译后的系统垃圾文件                *
echo   ***************************************************************************
echo                        请选择要进行的操作，然后按回车
echo             		      S.开启清理功能
echo             		      Q.退出
echo   *************************************************************************** 
:userchoice
set choice=
set /p choice=          请选择:
if not "%choice%"=="" set choice=%choice%
if /i "%choice%"=="S" goto clear
if /i "%choice%"=="Q" exit
echo                             选择无效，请重新输入
echo   *************************************************************************** 
echo                        请选择要进行的操作，然后按回车
echo             		      S.开启清理功能
echo             		      Q.退出
goto userchoice
:clear
cls
for %%a in (*.*) do if /i exist "%%a" (
if /i not "%%~xa"==".bat" (
if /i not "%%~xa"==".a51" (
if /i not "%%~xa"==".c" (
if /i not "%%~xa"==".asm" (
if /i not "%%~xa"==".h" (
if /i not "%%~xa"==".hex" (
if /i not "%%~xa"==".txt" (
if /i not "%%~xa"==".uvopt" (
if /i not "%%~xa"==".uvproj" (
if /i not "%%~xa"==".lib" (
if /i not "%%~xa"==".sn8" (
if /i not "%%~xa"==".prj" (
if /i not "%%~xa"==".wsp" (
if /i not "%%~xa"==".cfg" (
if /i not "%%~xa"==".cop" (
if /i not "%%~xa"==".rar" (
if /i not "%%~xa"==".zip" (
if /i not "%%~xa"==".doc" (
if /i not "%%~xa"==".xlsx" (
if /i not "%%~xa"==".xls" (
if /i not "%%~xa"==".lnk" (
if /i not "%%~xa"==".pdf" (
if /i not "%%~xa"==".avi" (
if /i not "%%~xa"==".mp3" (
if /i not "%%~xa"==".mp4" (
if /i not "%%~xa"==".wav" (
if /i not "%%~xa"==".wma" (
if /i not "%%~xa"==".iso" (
if /i not "%%~xa"==".exe" (
if /i not "%%~xa"==".rm" (
if /i not "%%~xa"==".wps" (
if /i not "%%~xa"==".jpg" (
if /i not "%%~xa"==".png" (
if /i not "%%~xa"==".pic" (
if /i not "%%~xa"==".bmp" (
if /i not "%%~xa"==".tif" (
if /i not "%%~xa"==".gif" (
if /i not "%%~xa"==".int" (
if /i not "%%~xa"==".sys" (
if /i not "%%~xa"==".dll" (
if /i not "%%~xa"==".adt" (
if /i not "%%~xa"==".swf" (
if /i not "%%~xa"==".arj" (
if /i not "%%~xa"==".z" (
(del /q "%%a"))))))))))))))))))))))))))))))))))))))))))))))	
																
for /f "tokens=*" %%a in ('dir /a:d /b') do if /i exist "%%a" (		
	if /i "%%a"=="listings" ((cd "%cd%\listings") & (del /q /f *.*) & (cd..))
  	if /i "%%a"=="Objects" ((cd "%cd%\objects") & (for %%i in (*.*) do if /i exist "%%i" (if /i not "%%~xi"==".hex" (del /q /f "%%i"))) & (cd..))	
	if /i "%%a"=="bin" ((cd "%cd%\bin") & (for %%i in (*.*) do if /i exist "%%i" (if /i not "%%~xi"==".sn8" (del /q /f "%%i"))) & (cd..))		
	if /i "%%a"=="obj" ((cd "%cd%\obj") & (for %%i in (*.*) do if /i exist "%%i" (if /i not "%%~xi"==".asm" (del /q /f "%%i"))) & (cd..)))	
exit
::--------------------------------------延时子程序----------------------------------
:delay
@echo off
if "%1"=="" goto :eof
set DelayTime=%1
set TotalTime=0
set NowTime=%time%
::读取起始时间，时间格式为：时:分:秒.毫秒
:delay_continue
set /a minute1=1%NowTime:~3,2%-100
set /a second1=1%NowTime:~-5,2%%NowTime:~-2%0-100000
set NowTime=%time%
set /a minute2=1%NowTime:~3,2%-100
set /a second2=1%NowTime:~-5,2%%NowTime:~-2%0-100000
set /a TotalTime+=(%minute2%-%minute1%+60)%%60*60000+%second2%-%second1%
if %TotalTime% lss %DelayTime% goto delay_continue
goto :eof