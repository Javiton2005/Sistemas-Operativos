schtasks /create /tn "TallerBatchDaily" /tr "%cd%\script1.bat" /sc daily /st 10:00:00
schtasks /create /tn "TallerBatchOnStart" /tr "%cd%\script1.bat" /sc onstart /ru SYSTEM
schtasks /create /tn "TallerBatchOnLogOn" /tr "%cd%\script1.bat" /sc onlogon /ru SYSTEM

schtasks /query | findstr "TallerBatch"

pause
