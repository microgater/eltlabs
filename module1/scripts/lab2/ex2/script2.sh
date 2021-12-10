#!/bin/bash
# Лабораторная работа №2 (Задача 2)

# Читаем rhsm.log, выбираем [INFO], заменяем на Information: и записываем в файл full.log
grep "\[INFO\]" rhsm.log | sed 's/\[INFO\]/Information:/' > full.log
# Читаем rhsm.log, выбираем [WARNING], заменяем на Warning: и дописываем в конец файла full.log
grep "\[WARNING\]" rhsm.log | sed 's/\[WARNING\]/Warning:/' >>  full.log

# Выводим файл full.log на экран
cat full.log

# Завершаем скрипт
exit 0
