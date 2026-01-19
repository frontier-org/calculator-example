:: Copyright (c) 2026 The Frontier Framework Authors
:: SPDX-License-Identifier: Apache-2.0 OR MIT

@echo off
setlocal enabledelayedexpansion
set "CLASS_NAME=%~n1"
set "USER_ARGS="
shift

:loop
if "%~1"=="" goto run
set "USER_ARGS=!USER_ARGS! %1"
shift
goto loop

:run
java -cp ".frontier/target/dev_cache" !CLASS_NAME! !USER_ARGS!
endlocal