#!/bin/bash
# Лабораторная работа №1a (Задача 3)

# Выводим варианты выбора
echo "Выберите пункт:"
echo "1) nano"
echo "2) vi"
echo "3) links"
echo "4) exit"

# Считываем, число введенное пользователем
read
# Выполняем действие, соответствующее числу
case $REPLY in
        1 ) nano;;
        2 ) vi;;
        3 ) links;;
        4 ) exit 0;;
esac

# Завершаем скрипт с кодом 0
exit 0
