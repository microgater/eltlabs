#!/bin/bash
# Лабораторная работа №3 (Задача 3)

# Ищем предыдущую папку с бэкапом
lastBackup=$(ls ~ | grep ^Backup- | sort -rn | head -1 | cut -d "-" -f 2,3,4)

if [[ -z "$lastBackup" ]]; then
	lastBackup="1970-01-02"
fi

# Получаем текущую дату
currentDate=$(date +%Y-%m-%d)

# Посчитаем сколько прошло секунд с того времени
let days=($(date -d $currentDate +%s)-$(date -d $lastBackup +%s))/24/60/20

# Если число дней превышает 7 или бэкапа не существует, то создаем новый бэкап
if [[ days -gt 7 ]]
then
	mkdir ~/Backup-$currentDate
	cp ~/listtask/* ~/Backup-$currentDate/
	echo "Был создан новый каталог с бэкапом: Backup-$currentDate" >> ~/backup-report
	echo "Были скопированы файлы:\n $(ls ~/listtask)" >> ~/backup-report
# Если время с момента последнего бэкапа не превышает 7 дней
else
	cd ~/Backup-$lastBackup

	echo "В каталог бэкапа Backup-$lastBackup были внесены изменения $currentDate"
	echo "Были добавлены новые файлы:"

	# Получаем список файлов в ~/listtask
	fileList="$(ls ~/listtask)"
	for filename in $fileList
	do
		# Если такой файл уже существует в папке бэкапа
		if [[ -f "$filename" ]]
		then
			# Если его версия изменилась, то переименовываем старый файл в версионную копию
			if [[ $(ls -l ~/listtask/$filename | cut -d ' ' -f5) -ne $(ls -l $filename | cut -d ' ' -f5) ]]
			then
				mv $filename $filename.$currentDate
			fi
		else
			echo $filename
		fi
		# Копируем файл в папку бэкапа
		cp -r ~/listtask/$filename ./
	done

	echo "Были добавлены новые версии файлов, старые версии которых теперь называются так:"
	ls | grep -oE ".*\.$currentDate"
fi

# Завершаем скрипт
exit 0
