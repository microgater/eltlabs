#!/bin/bash
# Лабораторная работа №2 (Задача 3)

# Читаем все файлы и выбираем email-ы, записываем их в файл
grep -oshr "[[:alnum:]+\.\_\-]\+@[[:alnum:]+\.\_\-]\+" /etc | tr "\n" "," > emails.lst

# Завершаем скрипт
exit 0
