# Тестовое задание для Visual SVN

## Текст задания

Написать консольное приложение, которое получает на вход
бинарный файл ***произвольного*** размера и в качестве результата создаёт
новый файл, в котором содержимое входного файла записано в обратном порядке (побайтно).

Имена входного и выходного файлов передаются через параметры командной строки.

Пояснения к программе:
* Программа может принимать любые файлы и любого размера.
* Для того чтобы "развернуть" байты в файле, они считываются блоками,
а не загружаются все в оперативную память, чтобы была возможность работы
с файлами любых размеров. Программа считывает блоками, а не записывает посимвольно в выходной файл,
для большего быстродействия и меньшего количества обращений к чтению/записи на медленный диск.
* Так как классические fseek и ftell поддерживают только long - пришлось пользоваться
условной компиляцией, чтобы взять 64-битные версии этих функций в Windows и UNIX-подобных системах.