#!/bin/bash
# Лабораторная работа №3 (Задача 4)

lastBackup=$(ls ~ | grep ^Backup- | sort -rn | head -1 | cut -d "-" -f 2,3,4)

cd ~/Backup-$lastBackup

# Получаем список файлов в каталоге бэкапа
fileList="$(ls)"

# Перебираем файлы
for filename in $fileList
do
	# Составляем список старых версионных копий
	fileSkip=$(echo $filename | grep -oE ".*\.[0-9]{4}-[0-9]{2}-[0-9]{2}" )
	
	# Копируем только последнюю версию
	if [ "$filename" != "$fileSkip" ]
	then
		cp -r $filename ~/listtask/
	fi
done

# Завершаем скрипт
exit 0
