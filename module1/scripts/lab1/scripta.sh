#!/bin/bash
# Лабораторная работа 1 (Задача 1)

# Выводим информацию о переданных в скрипт параметрах
echo "Название файла сценария: $0"
echo "Первый параметр: $1"
echo "Второй параметр: $2"

if [[ "$1" == "$2" ]]
# Если обе переданные строки равны, выводим сообщение на экран
then
	echo "Строки равны"
# В противном случае
else
	echo "Строки не равны"
fi

# Заканчиваем скрипт с кодом 0
exit 0
