import struct
import matplotlib.pyplot as plt

file_path = "../data/csd_IP_day_3.shsf"

def read_data(file_path):
    co2_values = []
    temp_values = []

    with open(file_path, 'rb') as file:
        while True:
            # Читаем 8 байт (4 байта CO2 и 4 байта температуры)
            data = file.read(8)
            if not data or len(data) < 8: break  # Конец файла

            # Распаковываем данные
            co2_value, temp_value = struct.unpack('II', data)
            # print(co2_value)
            co2_values.append(co2_value)
            temp_values.append(temp_value)

    return co2_values, temp_values

def plot_data(co2_values, temp_values):
    plt.figure(figsize=(12, 6))

    # Создаем два подграфика
    plt.subplot(2, 1, 1)
    plt.plot(co2_values, label='CO2 Value', color='green')
    plt.title('CO2 Levels Over Time')
    plt.xlabel('Time (minutes)')
    plt.ylabel('CO2 Value (ppm)')
    plt.legend()

    plt.subplot(2, 1, 2)
    plt.plot(temp_values, label='Temperature Value', color='red')
    plt.title('Temperature Levels Over Time')
    plt.xlabel('Time (minutes)')
    plt.ylabel('Temperature (°C)')
    plt.legend()

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    co2_values, temp_values = read_data(file_path)
    plot_data(co2_values, temp_values)


