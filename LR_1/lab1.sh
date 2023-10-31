#!/bin/bash

echo "<-----=====Общие данные=====----->"
echo "Дата и время:  " $(date +"%d-%m-%Y") $(date +"%H:%M:%S")
echo "Имя учётной записи:  " $(whoami)
echo "Доменное имя ПК:  " $(hostname)
echo "<-----=====Процессор=====----->"
echo $(lscpu | grep 'Имя модели')
echo $(lscpu | grep 'Архитектура')
echo $(lscpu | grep 'CPU МГц')
echo $(lscpu | grep 'Ядер на сокет')
echo $(lscpu | grep 'Потоков на ядро')
echo "<-----=====Оперативная память=====----->"
echo -n "Всего: " && (cat /proc/meminfo | grep 'MemTotal' | awk '{print $2}');
echo -n "Свободно: " && (cat /proc/meminfo | grep 'MemFree' | awk '{print $2}');
echo "<-----=====Жесткий диск=====----->"
echo -n "sda2 всего - Mb: " && df -m |grep "/dev/sda2" | awk '{print $2}';
echo -n "sda2 доступно - Mb: " && df -m |grep "/dev/sda2" | awk '{print $4}';
echo -n "sda3 всего - Mb: " && df -m |grep "/dev/sda3" | awk '{print $2}';
echo -n "sda3 доступно - Mb: " && df -m |grep "/dev/sda3" | awk '{print $4}';
echo -n "Swap всего - Mb: " && free -m |grep "Память" | awk '{print $2}';
echo -n "Swap доступно - Mb: " && free -m |grep "Память" | awk '{print $4}';
echo "<-----=====Сетевые интерфейсы=====----->"

names=`ifconfig | cut -d ' ' -f1 | tr ':' '\n'|awk NF`
name1=`echo $names |xargs| cut -d " " -f1`
name2=`echo $names |xargs| cut -d " " -f2`

mac1=`ifconfig |grep ether|xargs| cut -d " " -f2`
mac2=`ifconfig |grep ether|xargs| cut -d " " -f2`

ip1=`ifconfig |grep "enp0s3" -A2 |grep inet -w|xargs|cut -d " " -f2`;
ip2=`ifconfig |grep "lo" -A2 |grep inet -w|xargs|cut -d " " -f2`;

speed=`speedtest-cli |grep "Download"| awk '{print $2 " Mb/s"}'`;

echo "# Имя_сети MAC IP SPEED">./tmp.txt
echo "1 $name1 $mac1 $ip1 $speed">>./tmp.txt
echo "2 $name2 - $ip2 -">>./tmp.txt
column -t ./tmp.txt;

rm tmp.txt;
