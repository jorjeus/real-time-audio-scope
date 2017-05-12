@setlocal

@set /A CMAKE_ARTIFACT_COUNT=0

@rem expecting a 'CMakeFiles' folder
@for /f %%d in ('dir /ad /b .\') do @(
  @if "%%d"=="CMakeFiles" (
    @set /A CMAKE_ARTIFACT_COUNT=CMAKE_ARTIFACT_COUNT+1
  )
)

@rem also expecting a 'CMakeCache.txt' file
@for /f %%f in ('dir /a-d /b .\') do @(
  @if "%%f"=="CMakeCache.txt" (
    @set /A CMAKE_ARTIFACT_COUNT=CMAKE_ARTIFACT_COUNT+1
  )
)

@set /A RET=0
@if %CMAKE_ARTIFACT_COUNT%==2 (
  @set /A RET=1
)

@rem return a value to the calling script via a supplied argument
@endlocal&@set /A %~1=%RET%
