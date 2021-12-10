#!/bin/bash
# Диалоговый интерфейс для скриптов

# Используемая команда (dialog/Xdialog)
DIALOG=${DIALOG=dialog}

choice=`$DIALOG --stdout --clear --title "Список действий" \
        --menu "Выберите действие" 13 50 6 \
        "1" "Удалить файл" \
	"2" "Восстановить файл" \
	"3" "Произвести бэкап файлов" \
	"4" "Произвести восстановление файлов" \
	"5" "Архивировать файл в .gz" \
	"6" "Разархивировать файл .gz"`

case $? in
0)
	case $choice in
		1) FILE=`$DIALOG --stdout --clear --title "Выберите файл для удаления" --fselect ./ 10 60`
		clear -x
		./remftrash.sh $FILE;;

		2) filename=`$DIALOG --stdout --clear --title "Ввод данных" --clear \
			--inputbox "Введите имя файла для восстановления:" 8 50`
		clear -x
		./unftrash.sh $filename;;

		3) clear -x
		 ./makebackup.sh;;

		4) clear -x
		./restorebackup.sh;;

		5) FILE=`$DIALOG --stdout --clear --title "Выберите файл для архивации" --fselect ./ 10 60`
		clear -x
		gzip $FILE;;
		
		6) FILE=`$DIALOG --stdout --clear --title "Выберите файл для рвзархивации" --fselect ./ 10 60`
                clear -x
                gunzip $FILE;:
	esac;;
	
	# Если была выбрана кнопка отмена
	1) clear -x
	echo "Действие отменено.";;

	# Если была нажата клавиша ESC
	255) clear -x
	echo "Отмена.";;
esac

# Завершаем скрипт
exit 0
