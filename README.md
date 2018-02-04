# Deferred lighting
## Запуск на Ubuntu 16.04
### Зависимости:
sudo apt-get install libglew-dev

sudo apt-get install libglfw3-dev

sudo apt-get install libassimp-dev

### Загрузка кода программы
git clone https://github.com/angelikamukhina/ComputerGraphicsCourse.git

cd ComputerGraphicsCourse

git fetch --all

git checkout NPR

cd NPR

### Сборка и запуск
cmake .

make

./main
