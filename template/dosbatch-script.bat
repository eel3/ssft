:: -*- coding: cp932-dos -*-
:: vim:fileencoding=cp932:ff=dos
::
:: FIXME: <edit a description of this sctipt>

@echo off
setlocal

:: FIXME: write a code here.
echo %~nx0
for %%I in (%*) do echo %%~I
