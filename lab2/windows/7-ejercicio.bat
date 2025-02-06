schtasks /create /tn "TallerBatchDaily" /tr "C:\Users\jocra\Desktop\windows\script1.bat" /sc daily /st 10:00:00
schtasks /create /tn "TallerBatchOnStart" /tr "C:\Users\jocra\Desktop\windows\script1.bat" /sc onstart /ru SYSTEM
schtasks /create /tn "TallerBatchOnLogOn" /tr "C:\Users\jocra\Desktop\windows\script1.bat" /sc onlogon /ru SYSTEM

schtasks /query | findstr "TallerBatch"

pause
