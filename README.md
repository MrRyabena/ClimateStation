![ClimateStation_logo](logos/PNG/CS_inscr-mint.png)

---

[<img src="https://github.com/MrRyabena/SmartHomeSystem/blob/main/SHSlogos/PNG/SHS_inscr-light_mint.png" height="20"/>](https://github.com/MrRyabena/SmartHomeSystem)
[![Static Badge](https://img.shields.io/badge/Telegram-dev%20blog-blue)](https://t.me/SmartHomeSystem_dev)

---

<img src="schemes/images/CS_front_1.jpg" alt="ClimateStation_photo" height="150"/>
<img src="schemes/images/CS_front_4.jpg" alt="ClimateStation_photo" height="150"/>
<img src="schemes/images/CS_back_1.jpg" alt="ClimateStation_photo" height="150"/>
<img src="schemes/images/CS_front_off_1.jpg" alt="ClimateStation_photo" height="150">
<img src="schemes/images/CS_sensor_2.jpg" alt="ClimateStation_photo" height="150"/>

---

# ClimateStation by SmartHomeSystem

> [!NOTE]
> Проект является одним из устройств SmartHomeSystem. Внутри кода используется ядро и библиотека основного проекта — **_[SmartHomeSystem](https://github.com/MrRyabena/SmartHomeSystem)_**.</br>

## Versions

<details>
<summary>v1.0.0 — development beta-version.</summary>


</details>

<details>
<summary>v1.1.0 — <b><code>[current]</code></b>


</details>

## Components

[See list of components](/schemes/components/components_list.md).

## About

**_ClimateStation_** — метеостанция в специально разработанном для 3D-печати корпусе с сенсорным дисплеем. Собирает информацию с внутренних и внешних датчиков об атмосферном давлении, уровне CO2 (углекислого газа) в помещении, влажности и температуре воздуха. Станция умеет составлять прогноз погоды, подсказывать когда необходимо проветрить помещение и выводить показания с датчиков и графики их изменений. Сенсорный экран позволяет изменять настройки, переключать режимы работы и смотреть показания датчиков в реальном времени. Также устройство может обеспечивать обратную связь в системах климат-контроля **_SmartHomeSystem_**.

### Возможности

- Измерения:
  - Temperature in/out
  - Humidity in/out
  - Pressure
  - CO2 concentration
- Сенсорный дисплей:
  - Визуализация показателей в реальном времени
  - Расчёт и отображение тренда изменения величины (возрастает/убывает/не изменяется)
  - Переключение режимов и управление настройками
- Подсветка:
  - Визуальный контроль качества воздуха или изменения погодных условий
- Сбор и сохранение статистики
  - Вывод графиков за выбранные промежутки времени

## PCB
Для сборки устройства разработана печатная палата.

[![schematic_ClimateStation_v1.1.0.svg](schemes/PCB/schematic_ClimateStation_v1.1.0.svg)](schemes/PCB/schematic_ClimateStation_v1.1.0.svg)
[![schemes/PCB/PCB_TopSide.svg](schemes/PCB/PCB_TopSide.svg)](schemes/PCB/PCB_TopSide.svg)
[![schemes/PCB/PBC_BottomSide.svg](schemes/PCB/PBC_BottomSide.svg)](schemes/PCB/PBC_BottomSide.svg)

## Упаковка

Картонная [коробка](https://www.ozon.ru/product/kartonnaya-korobka-20h12h12-sm-korobka-dlya-upakovki-bizhuterii-i-yuvelirnyh-izdeliy-gofrokorob-384109582/) 200x12x12 mm. Обклеивается символикой из [logos/source/print.docx](logos/source/print.docx).

Внутрь вставляется картонная вставка (для создания разделов):

- Размеры вставки: 105x480
- Загибы: 195 + 115 + 55 + 115

  ![insert-scheme-2D.png](schemes/packaging/insert-scheme-2D.png)
