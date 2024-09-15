@echo off
:: Sprawdzenie, czy yt-dlp jest dostępny
where yt-dlp >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo Nie znaleziono yt-dlp. Upewnij sie, ze jest zainstalowane i w PATH.
    pause
    exit /b
)

:: Definiowanie plików i zmiennych
set "inputFile=download.txt"
set "archiveFile=log.txt"
set "audioFormat=mp3"
set "outputFolder=yt"

:: Sprawdzenie, czy plik pobierania istnieje
if not exist "%inputFile%" (
    echo Plik %inputFile% nie istnieje.
    pause
    exit /b
)

:: Sprawdzenie, czy plik archiwum istnieje
if not exist "%archiveFile%" (
    echo Tworzenie nowego pliku archiwum %archiveFile%.
    type nul > "%archiveFile%"
)

:: Sprawdzenie, czy folder yt istnieje, jeśli nie, tworzymy go
if not exist "%outputFolder%" (
    echo Tworzenie folderu %outputFolder%.
    mkdir "%outputFolder%"
)

:: Uruchomienie yt-dlp z zapisem do folderu yt w formacie mp3
yt-dlp -a "%inputFile%" --download-archive "%archiveFile%" -P "%outputFolder%" -x --audio-format "%audioFormat%" 2> error.log

:: Sprawdzenie, czy yt-dlp zakończyło się sukcesem
if %ERRORLEVEL% neq 0 (
    echo Wystapil blad podczas pobierania. Sprawdz error.log.
    pause
    exit /b
)

echo Pobieranie zakonczone sukcesem! Pliki zapisane w folderze %outputFolder% w formacie %audioFormat%.
pause
