# Лабораторная работа #1

## Данные
Модель представляется в виде набора файлов формата `.stl` 
(всего 5 файлов, на разные части костюма).
![data_demo](../3rdparty/pictures/lab1_dem2.PNG)

## Фильтр
В качестве фильтра применялся `vtkAppendPolyData`, который
объединяет полигональный датасет, состоящий из нескольких
файлов.

![filter_demo1](../3rdparty/pictures/lab1_dem4.PNG)
![filter_demo2](../3rdparty/pictures/lab1_dem5.PNG)

## Виджет
Выбран `vtkImplicitPlaneWidget`, который 
предназначен для интерактивного отсечения полигональных
данных плоскостью.

![widget_demo](../3rdparty/pictures/lab1_dem3.PNG)
