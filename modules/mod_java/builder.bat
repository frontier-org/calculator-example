:: Copyright (c) 2026 The Frontier Framework Authors
:: SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception OR MIT

@echo off
setlocal

set "SOURCE_FILE=%~1"
set "TARGET_JAR=%~2"
set "CLASS_NAME=%~n1"
set "TEMP_DIR=%~dp2"

if not exist "%TEMP_DIR%" mkdir "%TEMP_DIR%"

javac "%SOURCE_FILE%" -d "%TEMP_DIR%."
jar cfe "%TARGET_JAR%" "%CLASS_NAME%" -C "%TEMP_DIR%." "."

del /Q "%TEMP_DIR%*.class"

endlocal