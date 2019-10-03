:: -*- coding: cp932-dos -*-
:: vim:fileencoding=cp932:ff=dos
::
:: FIXME: <edit a description of this sctipt>

@echo off
pwsh -ep RemoteSigned -f "%~dpn0.ps1" %*
