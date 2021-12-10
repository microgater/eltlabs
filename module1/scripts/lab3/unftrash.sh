#!/bin/bash
# Лабораторная работа №3 (Задача 2)

# Устанавливаем счетчик
count=1
# Ищем путь полное название удаленного файла
path=$(grep "$1$" trash.log | sed -n ${count}p | cut -d ' ' -f3)

# Пока строка не станет пустой
while [ -n "$path" ]
do
	# Узнаем название файла в папке .trash из trash.log
	name=$(grep "$1$" trash.log | sed -n ${count}p | cut -d ' ' -f1)
	echo "Вы хотите восстановить файл $path? (y/n)"
	# Считываем ввод пользователя и выполняем выбранное им действие
	read
	case $REPLY in
		y ) 	# Создаем жесткую ссылку
			ln ~/.trash/$name $path
			# Удаляем из trash.log соответсвующую восстановленному файлу запись
			sed -in "/${name} - /d" trash.log
			# Удаляем файл
			rm ~/.trash/$name;;

		n )	# Увеличиваем счетчик для перехода к следующему файлу
			let count++;;
	esac
	# Ищем путь полное название удаленного файла
	path=$(grep "$1$" trash.log | sed -n ${count}p | cut -d ' ' -f3)
done

# Завершаем скрипт
exit 0
