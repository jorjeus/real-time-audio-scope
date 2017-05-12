@setlocal 

@if "%1"=="" (
  @echo ERROR: Argument expected
  @echo ERROR: Please supply the relative folder where the CMake output sits
  @echo ERROR: Exiting..
  @exit /B -1
)

@echo Changing location to "%~f1"..
@cd "%~f1"
@if %ERRORLEVEL% NEQ 0 (
  @rem folder does not exist; exit without error
  @exit /B 0

)
@echo %cd%

call %~dp0IsCMakeOutputFolder.bat IS_CMAKE_FOLDER

@if %IS_CMAKE_FOLDER% EQU 1 (
  @del /s /f /q .\*
  @for /f %%f in ('dir /ad /b .\') do @(
    @rmdir /s /q .\%%f
  )
) else (
  @echo Folder
  @echo   "%~f1"
  @echo either does not look like the output of a CMake out-of-source-tree build or is empty.
  @echo Nothing to clean..
  @exit /B -1
)

