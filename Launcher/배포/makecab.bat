cabarc.exe N launcher.cab launcher.ocx launcher.inf 
signcode -v revcert.pvk -spc revcert.spc launcher.cab -n "레브 게임 Launcher" -t http://timestamp.verisign.com/scripts/timstamp.dll
setreg -q 1 TRUE
chktrust launcher.cab