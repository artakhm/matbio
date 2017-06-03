# Компьютерная симуляция модели стационарного биологического сообщества Ульфа Дикмана.
### Этапы
1. Ознакомление с кодом симуляций Ульфа Дикмана.
2. Изучение кода симуляций Галкина Егора, запуски его кода.
3. Изучение возможных алгоритмов симуляции на научных семинарах.
4. Написание собественной программы.

### Реализация
Программа реализована на языке C++ стандарта 2011 года.
#### Описание алгоритма
Алгоритм симулирует одновидовую биологическую модель на дискретизированной координатной плоскости. В каждой ячейке сетки может находиться произвольное число особей. Шаг алгоритма заключается в пересчете матрицы вероятности рождения нового вида в каждой из ячеек и возможной смерти каждой отдельной особи. Ядро рождения для каждой ячейки сетки выбрано затухающим согласно нормальному закону с максимумом в ней самой.
Для оптимизации вычислений, при падении вероятности рождения в 100 раз (с удалением от рождающего вида), вероятность обнуляется. То есть алгоритм рассматривает только некоторую окрестность каждой ячейки, а не обсчитывает всю сетку.

### Возможное добавление функционала
 * Возможность выбора границы области (отражающая, убивающая)
 * Рандомизированная инициализация сетки
 * Оптимизировать смерть видов в одной ячейке с помощью теории вероятностей
 
